#include "DetectorUI.h"

DetectorUI::DetectorUI(){
	// Set the style of the GUI
	defaultLookAndFeel = new LookAndFeel_V2();
	setLookAndFeel(defaultLookAndFeel);

	// -------------------- TEXT EDITOR FOR MESSAGE HANDLING -----------------
	channelSelection = new ComboBox();

	// manual
	updateChannel(8);
    channelSelection->addListener(this);
	addAndMakeVisible(channelSelection);

	outChannelSelection = new ComboBox();
	outChannelSelection->addItem("1", 1);
	outChannelSelection->addItem("2", 2);
	outChannelSelection->addItem("3", 3);
	outChannelSelection->addItem("4", 4);
	outChannelSelection->addItem("5", 5);
	outChannelSelection->addItem("6", 6);
	outChannelSelection->addItem("7", 7);
	outChannelSelection->addItem("8", 8);
	outChannelSelection->setSelectedId(1);
    outChannelSelection->addListener(this);
	addAndMakeVisible(outChannelSelection);

	thresholdAmplitude = new Slider("Threshold Amp"); // Create the object and set its name
	thresholdAmplitude->setRange(0, 100, 0); // Set the minium value, the max value and the increment interval
	thresholdAmplitude->setSliderStyle(Slider::Rotary); // Set the style of the styler, horizontal or vertical
	thresholdAmplitude->setTextBoxIsEditable(false); // Set the visual style of the slider
	thresholdAmplitude->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20); // Set the visual style of the slider
	thresholdAmplitude->setTextValueSuffix(" "); // Set the sufix of the value shown at the left of the slider
	thresholdAmplitude->addListener(this); // Adding a listener, the class that will handle this slider
	addAndMakeVisible(thresholdAmplitude); // Adding the slider into this component for it to be visible

	refractoryRMSSamples = new Slider("Refractory samples"); // Create the object and set its name
	refractoryRMSSamples->setRange(0, 100, 0); // Set the minium value, the max value and the increment interval
	refractoryRMSSamples->setSliderStyle(Slider::Rotary); // Set the style of the styler, horizontal or vertical
	refractoryRMSSamples->setTextBoxIsEditable(false); // Set the visual style of the slider
	refractoryRMSSamples->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20); // Set the visual style of the slider
	refractoryRMSSamples->setTextValueSuffix(" "); // Set the sufix of the value shown at the left of the slider
	refractoryRMSSamples->addListener(this); // Adding a listener, the class that will handle this slider
	addAndMakeVisible(refractoryRMSSamples); // Adding the slider into this component for it to be visible

	RMSSamples = new Slider("RMS samples"); // Create the object and set its name
	RMSSamples->setRange(0, 100, 0); // Set the minium value, the max value and the increment interval
	RMSSamples->setSliderStyle(Slider::Rotary); // Set the style of the styler, horizontal or vertical
	RMSSamples->setTextBoxIsEditable(false); // Set the visual style of the slider
	RMSSamples->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20); // Set the visual style of the slider
	RMSSamples->setTextValueSuffix(" "); // Set the sufix of the value shown at the left of the slider
	RMSSamples->addListener(this); // Adding a listener, the class that will handle this slider
	addAndMakeVisible(RMSSamples); // Adding the slider into this component for it to be visible

	input_channel_label = new Label("label", TRANS("Input")); // Create the object and set its name
	input_channel_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	input_channel_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	input_channel_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	input_channel_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(input_channel_label); // Addint the label to the component and turning it visible

	
	out_channel_label = new Label("label", TRANS("Output")); // Create the object and set its name
	out_channel_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	out_channel_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	out_channel_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	out_channel_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(out_channel_label); // Addint the label to the component and turning it visible

	thresholdAmp_label = new Label("label", TRANS("T. Amp")); // Create the object and set its name
	thresholdAmp_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	thresholdAmp_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	thresholdAmp_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	thresholdAmp_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(thresholdAmp_label); // Addint the label to the component and turning it visible

	refractoryRMSSamples_label = new Label("label", TRANS("Refract time (ms)")); // Create the object and set its name
	refractoryRMSSamples_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	refractoryRMSSamples_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	refractoryRMSSamples_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	refractoryRMSSamples_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(refractoryRMSSamples_label); // Addint the label to the component and turning it visible

	RMSSamples_label = new Label("label", TRANS("RMS Samples(%)")); // Create the object and set its name
	RMSSamples_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	RMSSamples_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	RMSSamples_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	RMSSamples_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(RMSSamples_label); // Addint the label to the component and turning it visible

	// ---------------- CONFIGURING THE SIZE OF THIS COMPONENT ---------------
	setSize(100, 100);
}

void DetectorUI::paint(Graphics& UI_canvas)
{
	// The background color of the canvas can be cleared
	//g.fillAll(Colour(0xffcfecf5));
}

void DetectorUI::updateChannel(int channelCount){
	channelSelection->clear();
	for(int channel = 1; channel <= channelCount; channel++){
		channelSelection->addItem(String(channel), channel);
	}

	channelSelection->setSelectedId(1);
}

void DetectorUI::resized()
{
	// Set the limits of the UI_canvas
	setBounds(0, 0, getWidth(), getHeight());

	// Set the position, width and heigh of the elements - x, y, width, height
	int topMargin   = 25;
	int leftMargin	= 5;

	// Set the limits, size, and location of each component for them to be visible
	input_channel_label->setBounds(leftMargin, topMargin, 80, 15);
	channelSelection->setBounds(leftMargin, getNext_Y(input_channel_label), 50, 20);
	
	out_channel_label->setBounds(getNext_X(channelSelection), topMargin, 80, 15);
	outChannelSelection->setBounds(getNext_X(channelSelection), getNext_Y(input_channel_label), 50, 20);

	thresholdAmp_label->setBounds(leftMargin, getNext_Y(channelSelection), 80, 15);
	thresholdAmplitude->setBounds(leftMargin, getNext_Y(thresholdAmp_label), 80, 20);

	refractoryRMSSamples_label->setBounds(getNext_X(thresholdAmplitude), getNext_Y(channelSelection), 80, 15);
	refractoryRMSSamples->setBounds(getNext_X(thresholdAmplitude), getNext_Y(refractoryRMSSamples_label), 80, 20);

	RMSSamples_label->setBounds(getNext_X(thresholdAmplitude)+80, getNext_Y(channelSelection), 100, 15);
	RMSSamples->setBounds(getNext_X(thresholdAmplitude)+80, getNext_Y(RMSSamples_label), 80, 20);
	// -------------------------------------- MESSAGES --------------------------------------------------

}

void DetectorUI::buttonClicked(Button* buttonClicked){

}

void DetectorUI::sliderValueChanged(Slider* sliderChanged){
	if(sliderChanged == thresholdAmplitude)
		threshold_amp = (unsigned int)sliderChanged->getValue();

	if(sliderChanged == refractoryRMSSamples)
		rms_refraction_count = (unsigned int)sliderChanged->getValue();

	if (sliderChanged == RMSSamples)
		rms_samples = (unsigned int)sliderChanged->getValue();
}

void DetectorUI::comboBoxChanged(ComboBox* comboBoxChanged){
	if(comboBoxChanged == channelSelection)
		channel = comboBoxChanged->getSelectedId();

	if(comboBoxChanged == outChannelSelection)
		outChannel = comboBoxChanged->getSelectedId();
}