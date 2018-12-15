#include "MovementDetector.h"
//--------------------------------------------------------------------------------------------------------------
MovementDetector::MovementDetector()
	: GenericProcessor("MovementDetector")
{
	setProcessorType(PROCESSOR_TYPE_FILTER);

	// Configure Message to send inside events
	createEventChannels();

	// Initi accelerometer calibration vals
	average_x_up = 1.7;
	average_x_down = 1.4;

	average_y_up = 1.7;
	average_y_down = 1.4;

	average_z_up = 1.7;
	average_z_down = 1.4;

	time_stamp_real = 0;
}
//--------------------------------------------------------------------------------------------------------------
MovementDetector::~MovementDetector()
{
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetector::createEventChannels()
{
	eventChannelArray.clear();

	// Configuring event channel
	int num_of_text_channels = 8;
	_eventChannel = new EventChannel(EventChannel::TEXT, num_of_text_channels, sizeof(char) * 100, CoreServices::getGlobalSampleRate(), this);
	_eventChannel->setIdentifier("move_detected.event");

	int num_of_ttl_channels = 8;
	_ttl_eventChannel = new EventChannel(EventChannel::TTL, num_of_ttl_channels, sizeof(uint8), CoreServices::getGlobalSampleRate(), this);
	_ttl_eventChannel->setIdentifier("accelerometer_TTL_threshold.event");

	// set array
	eventChannelArray.add(_eventChannel);
	eventChannelArray.add(_ttl_eventChannel);
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetector::updateSettings()
{
	eventChannelArray.clear();

	//if (_eventChannel != 0x0)
	//	delete _eventChannel;

	//if (_ttl_eventChannel != 0x0)
	//	delete _ttl_eventChannel;

	// Configuring event channel
	int num_of_text_channels = 8;
	_eventChannel = new EventChannel(EventChannel::TEXT, num_of_text_channels, sizeof(char) * 100, CoreServices::getGlobalSampleRate(), this);
	_eventChannel->setIdentifier("move_detected.event");

	int num_of_ttl_channels = 8;
	_ttl_eventChannel = new EventChannel(EventChannel::TTL, num_of_ttl_channels, sizeof(uint8), CoreServices::getGlobalSampleRate(), this);
	_ttl_eventChannel->setIdentifier("accelerometer_TTL_threshold.event");

	// set array
	eventChannelArray.add(_eventChannel);
	eventChannelArray.add(_ttl_eventChannel);
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetector::getDefaultEventInfo(Array<DefaultEventInfo> &events, int subProcessorIdx) const
{
	DefaultEventInfo infoMoveDetected;
	infoMoveDetected.identifier = "move_detected.event";
	infoMoveDetected.nChannels = 8;
	infoMoveDetected.sampleRate = CoreServices::getGlobalSampleRate();
	infoMoveDetected.type = EventChannel::TEXT;
	infoMoveDetected.length = sizeof(char) * 100;
	events.add(infoMoveDetected);

	DefaultEventInfo ttl;
	ttl.identifier = "accelerometer_TTL_threshold.event";
	ttl.nChannels = 8;
	ttl.sampleRate = CoreServices::getGlobalSampleRate();
	ttl.type = EventChannel::TTL;
	ttl.length = sizeof(uint8);
	events.add(ttl);
}
//--------------------------------------------------------------------------------------------------------------
AudioProcessorEditor *MovementDetector::createEditor()
{
	accelEditor = new MovementDetectorEditor(this, true);
	editor = (GenericEditor *)accelEditor;
	return editor;
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetector::calibrateAccelerometer(AudioSampleBuffer &buffer, MovementDetectorUI &UI)
{
	int totalAmountOfChannels = buffer.getNumChannels();
	int samples = buffer.getNumSamples();

	// Calibrate accel diff according to a gravity vector
	if (UI.f_calibrateX_up)
	{
		const float *x_ptr = buffer.getReadPointer(X_ACCEL_CHANNEL);
		double average = 0.0;

		for (int sample = 0; sample < samples; sample++)
			average += x_ptr[sample];

		average = average / (double)samples;

		// set up average for these samples
		average_x_up = average;

		// set calibration to false, due to the fact that the accel was calibrated
		UI.f_calibrateX_up = false;
	}

	// Calibrate accel diff according to a gravity vector
	if (UI.f_calibrateX_down)
	{
		const float *x_ptr = buffer.getReadPointer(X_ACCEL_CHANNEL);
		double average = 0.0;

		for (int sample = 0; sample < samples; sample++)
			average += x_ptr[sample];

		average = average / (double)samples;

		// set up average for these samples
		average_x_down = average;

		// set calibration to false, due to the fact that the accel was calibrated
		UI.f_calibrateX_down = false;
	}

	// Calibrate accel diff according to a gravity vector
	if (UI.f_calibrateY_up)
	{
		const float *y_ptr = buffer.getReadPointer(Y_ACCEL_CHANNEL);
		double average = 0.0;

		for (int sample = 0; sample < samples; sample++)
			average += y_ptr[sample];

		average = average / (double)samples;

		// set up average for these samples
		average_y_up = average;

		// set calibration to false, due to the fact that the accel was calibrated
		UI.f_calibrateY_up = false;
	}

	// Calibrate accel diff according to a gravity vector
	if (UI.f_calibrateY_down)
	{
		const float *y_ptr = buffer.getReadPointer(Y_ACCEL_CHANNEL);
		double average = 0.0;

		for (int sample = 0; sample < samples; sample++)
			average += y_ptr[sample];

		average = average / (double)samples;

		// set up average for these samples
		average_y_down = average;

		// set calibration to false, due to the fact that the accel was calibrated
		UI.f_calibrateY_down = false;
	}

	// Calibrate accel diff according to a gravity vector
	if (UI.f_calibrateZ_up)
	{
		const float *z_ptr = buffer.getReadPointer(Z_ACCEL_CHANNEL);
		double average = 0.0;

		for (int sample = 0; sample < samples; sample++)
			average += z_ptr[sample];

		average = average / (double)samples;

		// set up average for these samples
		average_z_up = average;

		// set calibration to false, due to the fact that the accel was calibrated
		UI.f_calibrateZ_up = false;
	}

	// Calibrate accel diff according to a gravity vector
	if (UI.f_calibrateZ_down)
	{
		const float *z_ptr = buffer.getReadPointer(Z_ACCEL_CHANNEL);
		double average = 0.0;

		for (int sample = 0; sample < samples; sample++)
			average += z_ptr[sample];

		average = average / (double)samples;

		// set up average for these samples
		average_z_down = average;

		// set calibration to false, due to the fact that the accel was calibrated
		UI.f_calibrateZ_down = false;
	}
}

void MovementDetector::fullDetector(AudioSampleBuffer &buffer)
{
	int totalAmountOfChannels = buffer.getNumChannels();
	int samples = buffer.getNumSamples();

	// Get accelerometer raw data
	const float *x_ptr = buffer.getReadPointer(X_ACCEL_CHANNEL);
	const float *y_ptr = buffer.getReadPointer(Y_ACCEL_CHANNEL);
	const float *z_ptr = buffer.getReadPointer(Z_ACCEL_CHANNEL);

	// Get instance of the plugin's UI to set its values and activate its LEDS
	MovementDetectorUI *UI = &accelEditor->user_interface;

	// perform calibration logic
	calibrateAccelerometer(buffer, *UI);

	// treat accelerometer data (TODO)
	x_sensitivity = (average_x_up - average_x_down) / 2.0;
	x_zero_g_bias = (average_x_up + average_x_down) / 2.0;

	y_sensitivity = (average_y_up - average_y_down) / 2.0;
	y_zero_g_bias = (average_y_up + average_y_down) / 2.0;

	z_sensitivity = (average_z_up - average_z_down) / 2.0;
	z_zero_g_bias = (average_z_up + average_z_down) / 2.0;

	// Process each sample of the raw accelerometer data
	int totalSamples = buffer.getNumSamples();
	for (int sample = 0; sample < totalSamples; sample++)
	{
		// set detected boolean to off and check if there is any value worth cheking
		bool detected_X = false;
		bool detected_Y = false;
		bool detected_Z = false;

		// Calculating accelerations in all axis
		double ax = (x_ptr[sample] - x_zero_g_bias) / x_sensitivity;
		double ay = (y_ptr[sample] - y_zero_g_bias) / y_sensitivity;
		double az = (z_ptr[sample] - z_zero_g_bias) / z_sensitivity;

		// reset all UI leds
		//UI->resetDetectionLeds();

		// Display val
		/*string s_ax = "x: " + to_string(ax);
		string s_ay = "y: " + to_string(ay);
		string s_az = "z: " + to_string(az);

		UI->x_data->setText(s_ax, NotificationType::dontSendNotification);
		UI->y_data->setText(s_ay, NotificationType::dontSendNotification);
		UI->z_data->setText(s_az, NotificationType::dontSendNotification);*/

		// process accelerometer data here
		if (ax > UI->get_thresh_x())
		{
			//UI->turnXLedOn();
			detected_X = true;
		}

		if (ay > UI->get_thresh_y())
		{
			//UI->turnYLedOn();
			detected_Y = true;
		}

		if (az > UI->get_thresh_z())
		{
			//UI->turnZLedOn();
			detected_Z = true;
		}

		// if detected send event
		string msg = "";
		if (detected_X || detected_Y || detected_Z)
		{
			msg = "movement_detected";
		}
		else
		{
			msg = "movement_not_detected";
		}

		// Creating the Event
		TextEventPtr ptr = TextEvent::createTextEvent(eventChannelArray[0], getTimestamp(X_ACCEL_CHANNEL) + sample, msg.c_str(), X_ACCEL_CHANNEL);

		// Sending the movement detection event to JUCE
		addEvent(eventChannelArray[0], ptr, sample);

		// Sending TTL event to JUCE to track the detection according to the sample being checked
		uint8 ttlData;
		uint8 output_event_channel_X = X_ACCEL_CHANNEL;
		if (detected_X)
		{
			ttlData = 1 << output_event_channel_X;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(eventChannelArray[1], getTimestamp(X_ACCEL_CHANNEL) + sample, &ttlData, sizeof(uint8), output_event_channel_X);
			addEvent(eventChannelArray[1], ttl, sample);
		}
		else
		{
			ttlData = 0 << output_event_channel_X;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(eventChannelArray[1], getTimestamp(X_ACCEL_CHANNEL) + sample, &ttlData, sizeof(uint8), output_event_channel_X);
		}

		uint8 output_event_channel_Y = Y_ACCEL_CHANNEL;
		if (detected_Y)
		{
			ttlData = 1 << output_event_channel_Y;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(eventChannelArray[1], getTimestamp(Y_ACCEL_CHANNEL) + sample, &ttlData, sizeof(uint8), output_event_channel_Y);
			addEvent(eventChannelArray[1], ttl, sample);
		}
		else
		{
			ttlData = 0 << output_event_channel_Y;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(eventChannelArray[1], getTimestamp(Y_ACCEL_CHANNEL) + sample, &ttlData, sizeof(uint8), output_event_channel_Y);
		}

		uint8 output_event_channel_Z = Z_ACCEL_CHANNEL;
		if (detected_Z)
		{
			ttlData = 1 << output_event_channel_Z;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(eventChannelArray[1], getTimestamp(Z_ACCEL_CHANNEL) + sample, &ttlData, sizeof(uint8), output_event_channel_Z);
			addEvent(eventChannelArray[1], ttl, sample);
		}
		else
		{
			ttlData = 0 << output_event_channel_Z;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(eventChannelArray[1], getTimestamp(Z_ACCEL_CHANNEL) + sample, &ttlData, sizeof(uint8), output_event_channel_Z);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetector::testDetector(AudioSampleBuffer &buffer)
{
	int totalAmountOfChannels = buffer.getNumChannels();
	int samples = buffer.getNumSamples();

	// Get accelerometer raw data
	const float *x_ptr = buffer.getReadPointer(ACCEL_CHANNEL);

	// Get instance of the plugin's UI to set its values and activate its LEDS
	MovementDetectorUI *UI = &accelEditor->user_interface;

	// detection counter
	unsigned int counter = 0;
	bool enable_to_emmit = true;

	// Process each sample of the raw accelerometer data
	int totalSamples = buffer.getNumSamples();
	for (int sample = 0; sample < totalSamples; sample++)
	{
		// set detected boolean to off and check if there is any value worth cheking
		bool detected = false;

		// Calculating accelerations in all axis
		double ax = x_ptr[sample];

		// timestamp for this sample
		uint64 _timestamp = getTimestamp(ACCEL_CHANNEL) + sample;

		// process accelerometer data here
		if (ax > UI->get_thresh_x())
		{
			//UI->turnXLedOn();
			detected = true;
		}

		// Sending TTL event to JUCE to track the detection according to the sample being checked
		if (detected)
		{
			string msg = "movement_detected";

			// Creating the Event
			uint8 output_text_event_channel = 1;
			TextEventPtr ptr = TextEvent::createTextEvent(_eventChannel, _timestamp, msg.c_str(), output_text_event_channel);

			// Sending the movement detection event to JUCE
			addEvent(_eventChannel, ptr, sample);

			uint8 ttlData;
			uint8 output_event_channel = 3;
			ttlData = 1 << output_event_channel;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(_ttl_eventChannel, _timestamp, &ttlData, sizeof(uint8), output_event_channel);
			addEvent(_ttl_eventChannel, ttl, sample);

			// can emmit only once after one detection to prevent performance dropdowns
			//enable_to_emmit = false;
		}
		/*else
		{
			string msg = "movement_ended";

			// Creating the Event
			uint8 output_text_event_channel = 2;
			TextEventPtr ptr = TextEvent::createTextEvent(_eventChannel, _timestamp, msg.c_str(), output_text_event_channel);

			addEvent(_eventChannel, ptr, sample);

			uint8 ttlData;
			uint8 output_event_channel = 4;
			ttlData = 0 << output_event_channel;
			TTLEventPtr ttl = TTLEvent::createTTLEvent(_ttl_eventChannel, _timestamp, &ttlData, sizeof(uint8), output_event_channel);
			addEvent(_ttl_eventChannel, ttl, sample);
		}*/

		time_stamp_real += 1;
	}
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetector::process(AudioSampleBuffer &buffer)
{
	//fullDetector(buffer);
	// Check if any event ocurred and tells this plugin to call the handleEventsFunction()
	checkForEvents();
	testDetector(buffer);
}
