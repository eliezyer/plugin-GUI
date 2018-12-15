#ifndef PLUGIN_DETECTOR_H
#define PLUGIN_DETECTOR_H

// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include <ProcessorHeaders.h> // used to extend the generic processor from juce

// ---------------------------- SYSTEM INCLUDES TO HELP WITH ANY NECESSARY FUNCTION AND PROCESSING --------------------
#include <stdio.h>    // used for printf, fprintf, fread...
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <vector>
#include <time.h>

// -------------------------------------- EXTRA LIBRARY INCLUDES TO HELP WITH THE PROCESSING --------------------------

// ----------------------------------------------------- LOCAL INCLUDES -----------------------------------------------
#include "DetectorEditor.h" // used to have access to the created UI header

// ----------------------------------------------------- USED NAMESPACES ----------------------------------------------
using namespace std;

// ---------------------------------- DEFINITIONS TO HELP BETTER ORGANIZE THE CODE ------------------------------------

// --------------------------------------------------- USED NAMESPACES ------------------------------------------------

// ---------------- PLUGIN UI CLASS. Extends the GenericEditor and a liesteners to interac with the user --------------
class DetectorEditor;
class Detector : public GenericProcessor
{
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Detector);

public:
	Detector();
	~Detector();
	void process(AudioSampleBuffer& continuousBuffer) override;
	void handleEvent(const EventChannel* channelInfo, const MidiMessage& event, int sampleNum) override;
	AudioProcessorEditor* createEditor() override;
	void getDefaultEventInfo(Array<DefaultEventInfo>& events, int subProcessorIdx = 0) const override;
	void createEventChannels() override;
	void updateSettings() override;

	// calibration function
	void calibrate();
	void detectRipples(vector<double>& rms_buffer);
	void sendTTLEvent(int rms_index);
	double calculateRMS(const float* buffer, int index);

	// utilized channel to check for high frequencies
	int outputChannel;
	int channel;
	int rms_size;

	// rms statistics
	vector<double> calibration_rms;
	double mean;
	double standardDeviation;
	
	// detection threshold
	double threshold;
	double threshold_amp;

	// store processing time in seconds
	double start_time;
	double current_time;
	double calibration_time;

	// calibrating flag
	bool is_calibrating;

	// Event count
	bool detected;
	bool detection_enabled;	
	unsigned int rms_samples_sinceDetection;
	unsigned int rms_refraction_count;

	// event handle variables
	bool is_plugin_enabled;
	char* messageString;
	int messageSize;

	// ttl event channel
	EventChannel *_ttl_eventChannel;

	// Editor
	DetectorEditor* detectorEditor;
};

#endif
