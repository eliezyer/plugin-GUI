#include "Detector.h"
#include <stdio.h>
using namespace std;
//--------------------------------------------------------------------------------------------------------------
Detector::Detector()
	: GenericProcessor("Detector")
{
	setProcessorType(PROCESSOR_TYPE_FILTER);

	// Initialize variables
	calibration_time = 5.0;
	rms_samples_sinceDetection = 0;
	mean = 0.0;
	standardDeviation = 0.0;
	is_plugin_enabled = true;
	detection_enabled = true;
//	rms_size = 4;

	// Processing time
	start_time = getTimestamp(channel);

	// Calibratring flag
	is_calibrating = true;

	createEventChannels();
}
//--------------------------------------------------------------------------------------------------------------
Detector::~Detector()
{
}
//--------------------------------------------------------------------------------------------------------------
void Detector::createEventChannels()
{
	int num_of_ttl_channels = 8;
	_ttl_eventChannel = new EventChannel(EventChannel::TTL, num_of_ttl_channels, sizeof(uint8), CoreServices::getGlobalSampleRate(), this);
	_ttl_eventChannel->setIdentifier("TTL_threshold.event");

	// set array
	eventChannelArray.add(_ttl_eventChannel);
}
//--------------------------------------------------------------------------------------------------------------
void Detector::updateSettings()
{
	int num_of_ttl_channels = 8;
	_ttl_eventChannel = new EventChannel(EventChannel::TTL, num_of_ttl_channels, sizeof(uint8), CoreServices::getGlobalSampleRate(), this);
	_ttl_eventChannel->setIdentifier("TTL_threshold.event");

	// set array
	eventChannelArray.add(_ttl_eventChannel);
}
//--------------------------------------------------------------------------------------------------------------
void Detector::getDefaultEventInfo(Array<DefaultEventInfo> &events, int subProcessorIdx) const
{
}
//--------------------------------------------------------------------------------------------------------------
AudioProcessorEditor *Detector::createEditor()
{
	detectorEditor = new DetectorEditor(this, true);
	editor = detectorEditor;
	return editor;
}
//--------------------------------------------------------------------------------------------------------------
void Detector::sendTTLEvent(int rms_index)
{
	// send event only when the animal is not moving
	if (!is_plugin_enabled)
		return;

	// timestamp for this sample
	uint64 _timestamp = getTimestamp(channel) + rms_index * rms_size;

	uint8 ttlData;
	uint8 output_event_channel = outputChannel;
	ttlData = 1 << output_event_channel;
	TTLEventPtr ttl = TTLEvent::createTTLEvent(_ttl_eventChannel, _timestamp, &ttlData, sizeof(uint8), output_event_channel);
	addEvent(_ttl_eventChannel, ttl, rms_index * rms_size);
}
//--------------------------------------------------------------------------------------------------------------
void Detector::detectRipples(vector<double> &rms_buffer)
{
	for (unsigned int rms_sample = 0; rms_sample < rms_buffer.size(); rms_sample++)
	{
		double sample = rms_buffer[rms_sample];

		if (detection_enabled && sample > threshold)
		{
			printf("DETECTED RIPPLE!!!\n");
			sendTTLEvent(rms_sample);
			detected = true;
			detection_enabled = false;
		}

		// count rms samples since last detection
		if (detected)
			rms_samples_sinceDetection += 1;

		// enable detection again
		double auxrT = (rms_refraction_count*getSampleRate())/1000;
		int refractTime = (int) auxrT; // eu fiz isso pq tive problemas tentando dar cast direto no calculo
		double auxlD = rms_samples_sinceDetection;
		int lastDetect = (int) auxlD;

		if (lastDetect > refractTime)
		{
			detected = false;
			detection_enabled = true;
			rms_samples_sinceDetection = 0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
void Detector::calibrate()
{
	if (current_time > calibration_time)
	{
		// set flag to false to end the calibration period
		is_calibrating = false;

		// calculate statistics
		mean = mean / (double)calibration_rms.size();

		// calculate standard deviation
		for (unsigned int rms_sample = 0; rms_sample < calibration_rms.size(); rms_sample++)
			standardDeviation += pow(calibration_rms[rms_sample] - mean, 2.0);
		standardDeviation = sqrt(standardDeviation / ((double)calibration_rms.size() - 1));

		// define threshold
		threshold = mean + threshold_amp * standardDeviation;

		// end calibration debug
		printf("mean: %f std: %f threshold: %f\n", mean, standardDeviation, threshold);
	}
}
//--------------------------------------------------------------------------------------------------------------
double Detector::calculateRMS(const float *buffer, int index)
{
	double sum = 0;
	int cnt = 0;

	while (cnt < rms_size)
	{
		sum += pow(buffer[index + cnt], 2);
		cnt++;
	};

	double rms = sqrt(sum / rms_size);

	return rms;
}
//--------------------------------------------------------------------------------------------------------------
void Detector::process(AudioSampleBuffer &buffer)
{
	// update parameters according to UI
	outputChannel = detectorEditor->pluginUI.outChannel - 1;
	channel = detectorEditor->pluginUI.channel - 1;
	threshold_amp = detectorEditor->pluginUI.threshold_amp;
	rms_refraction_count = detectorEditor->pluginUI.rms_refraction_count;
	int auxSize = (int) ( ( (detectorEditor->pluginUI.rms_samples) / 100) * buffer.getNumSamples() );
	rms_size = auxSize;
	// Check if any event ocurred and tells this plugin to call the handleEventsFunction()
	checkForEvents();

	// Get raw data
	const float *samples = buffer.getReadPointer(channel);

	// RMS buffer
	vector<double> local_rms;

	// Generate RMS buffer
	for (int rms_index = 0; rms_index < buffer.getNumSamples(); rms_index += rms_size)
	{
		if (rms_index + rms_size > buffer.getNumSamples())
			break;

		// RMS calculation
		double _rms = calculateRMS(samples, rms_index);

		// Calculate average between RMSs to determine baseline threshold
		if (is_calibrating)
		{
			// Add variables to be used as a calibration basis
			calibration_rms.push_back(_rms);
			mean += _rms;
		}

		// Set buffer value
		local_rms.push_back(_rms);
	}

	// check if plugin needs to stop calibration and calculate its statistics for threshold estimation
	if (is_calibrating)
		calibrate();
	else
		detectRipples(local_rms);

	// calculate performing time
	current_time += getTimestamp(channel) - start_time;

	// free mem
	local_rms.clear();
}
//--------------------------------------------------------------------------------------------------------------
void Detector::handleEvent(const EventChannel *eventInfo, const MidiMessage &event, int samplePosition)
{
	// handle plugin control events
	is_plugin_enabled = true;

	if (Event::getEventType(event) == EventChannel::TEXT)
	{
		//TTLEventPtr TTLEvent = TTLEvent::deserializeFromMessage(event, eventInfo);
		TextEventPtr textEvent = TextEvent::deserializeFromMessage(event, eventInfo);

		string msg = string((char *)textEvent->getRawDataPointer());

		printf("sample: %Ld message: %s\n", textEvent->getTimestamp(), msg.c_str());

		if (strcmp(msg.c_str(), "movement_detected") == 0)
			is_plugin_enabled = false;

		//AlyssonReceptorEditor* UI = (AlyssonReceptorEditor*)editor.get();

		//msg.append("\r\n");

		//UI->pluginUI.midiMessages->clear();
		//UI->pluginUI.midiMessages->insertTextAtCaret(msg.c_str());
	}
}
//--------------------------------------------------------------------------------------------------------------