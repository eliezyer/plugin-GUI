#ifndef PLUGIN_ALY_H
#define PLUGIN_ALY_H

// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include <ProcessorHeaders.h> // used to extend the generic processor from juce

// ---------------------------- SYSTEM INCLUDES TO HELP WITH ANY NECESSARY FUNCTION AND PROCESSING --------------------
#include <stdio.h>    // used for printf, fprintf, fread...
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

// -------------------------------------- EXTRA LIBRARY INCLUDES TO HELP WITH THE PROCESSING --------------------------

// ----------------------------------------------------- LOCAL INCLUDES -----------------------------------------------
#include "MovementDetectorEditor.h" // used to have access to the created UI header

// ----------------------------------------------------- USED NAMESPACES ----------------------------------------------

// ---------------------------------- DEFINITIONS TO HELP BETTER ORGANIZE THE CODE ------------------------------------

// --------------------------------------------------- USED NAMESPACES ------------------------------------------------

#define ACCEL_CHANNEL 1
#define X_ACCEL_CHANNEL 0//33
#define Y_ACCEL_CHANNEL 1//34
#define Z_ACCEL_CHANNEL 2//35

class MovementDetectorEditor;
class MovementDetectorUI;

// ---------------- PLUGIN UI CLASS. Extends the GenericEditor and a liesteners to interac with the user --------------
class MovementDetector : public GenericProcessor
{
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MovementDetector);

public:
	MovementDetector();
	~MovementDetector();
	void testDetector(AudioSampleBuffer& buffer);
	void fullDetector(AudioSampleBuffer& buffer);
	void process(AudioSampleBuffer& continuousBuffer) override;

	MovementDetectorEditor* accelEditor;
	
	AudioProcessorEditor* createEditor() override;
	void getDefaultEventInfo(Array<DefaultEventInfo>& events, int subProcessorIdx = 0) const override;
	void createEventChannels() override;
	void updateSettings() override;

	void calibrateAccelerometer(AudioSampleBuffer& buffer, MovementDetectorUI& UI);

	double average_x_up = 0.0;
	double average_x_down = 0.0;
	double x_sensitivity = 0.0;
	double x_zero_g_bias = 0.0;

	double average_y_up = 0.0;
	double average_y_down = 0.0;
	double y_sensitivity = 0.0;
	double y_zero_g_bias = 0.0;

	double average_z_up = 0.0;
	double average_z_down = 0.0;
	double z_sensitivity = 0.0;
	double z_zero_g_bias = 0.0;

	// event channels
	EventChannel *_eventChannel;
	EventChannel *_ttl_eventChannel;

	// base buffer index
	uint64_t time_stamp_real;
};

#endif
