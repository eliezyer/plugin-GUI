#ifndef PLUGIN_ALY_UI_H
#define PLUGIN_ALY_UI_H

// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include <JuceHeader.h> // used to extend the JUCE listeners to operate the buttons and other components.

// ---------------------------- SYSTEM INCLUDES TO HELP WITH ANY NECESSARY FUNCTION AND PROCESSING --------------------

// -------------------------------------- EXTRA LIBRARY INCLUDES TO HELP WITH THE PROCESSING --------------------------

// ----------------------------------------------------- LOCAL INCLUDES -----------------------------------------------
#include "InterfaceHelper.h"

// ----------------------------------------------------- USED NAMESPACES ----------------------------------------------

// ---------------------------------- DEFINITIONS TO HELP BETTER ORGANIZE THE CODE ------------------------------------

// --------------------------------------------------- USED NAMESPACES ------------------------------------------------

// ---------------- PLUGIN UI CLASS. Extends the GenericEditor and a liesteners to interac with the user --------------

class DetectorUI : public Component,
	public ButtonListener,
	public SliderListener,
	public ComboBoxListener
{
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorUI);

public: 
	LookAndFeel_V2*				defaultLookAndFeel;
	ComboBox*                   channelSelection;
	ComboBox*                   outChannelSelection;
	Slider*						thresholdAmplitude;	
	Slider*						refractoryRMSSamples;
	Slider*						RMSSamples;

    // labels
    Label*                       input_channel_label;
	Label*                       out_channel_label;
    Label*                       thresholdAmp_label;
    Label*                       refractoryRMSSamples_label;
	Label*                       RMSSamples_label;

	// facade
	int channelCount;
	int channel;
	int outChannel;
	unsigned int threshold_amp;
	unsigned int rms_refraction_count;
	unsigned int rms_samples;
	DetectorUI();

	void updateChannel(int channelCount);
	void updateSettings();
	void resized() override;
	void paint(Graphics& g) override;
	void buttonClicked(Button* buttonClicked) override;
	void sliderValueChanged(Slider* sliderChanged) override;
	void comboBoxChanged(ComboBox* comboBoxChanged) override;
};

#endif
