#include "MovementDetectorUI.h"

MovementDetectorUI::MovementDetectorUI(){
    // Set the style of the GUI
	defaultLookAndFeel = new LookAndFeel_V2();
	setLookAndFeel(defaultLookAndFeel);

    // --------------------------- BUTTON CREATION ---------------------------
	calibrateX_up = new TextButton("XU"); // Create the object and set its name
	calibrateX_up->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom); // Set the style of the corners of this button
	//calibrateAccel->setColour(TextButton::buttonColourId, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
    calibrateX_up->setColour(TextButton::buttonNormal, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
	//textButton->setColour(TextButton::buttonOnColourId, Colour(0x363d47)); // Set colour according to its position inside the button, the position is represented by the ID
	calibrateX_up->addListener(this); // Adding a listener for this button, in this case it is this class
	addAndMakeVisible(calibrateX_up); // Adding the button into this component and turning it visible

	calibrateX_down = new TextButton("XD"); // Create the object and set its name
	calibrateX_down->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom); // Set the style of the corners of this button
	//calibrateAccel->setColour(TextButton::buttonColourId, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
    calibrateX_down->setColour(TextButton::buttonNormal, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
	//textButton->setColour(TextButton::buttonOnColourId, Colour(0x363d47)); // Set colour according to its position inside the button, the position is represented by the ID
	calibrateX_down->addListener(this); // Adding a listener for this button, in this case it is this class
	addAndMakeVisible(calibrateX_down); // Adding the button into this component and turning it visible

    calibrateY_up = new TextButton("YU"); // Create the object and set its name
	calibrateY_up->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom); // Set the style of the corners of this button
	//calibrateAccel->setColour(TextButton::buttonColourId, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
    calibrateY_up->setColour(TextButton::buttonNormal, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
	//textButton->setColour(TextButton::buttonOnColourId, Colour(0x363d47)); // Set colour according to its position inside the button, the position is represented by the ID
	calibrateY_up->addListener(this); // Adding a listener for this button, in this case it is this class
	addAndMakeVisible(calibrateY_up); // Adding the button into this component and turning it visible

	calibrateY_down = new TextButton("YD"); // Create the object and set its name
	calibrateY_down->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom); // Set the style of the corners of this button
	//calibrateAccel->setColour(TextButton::buttonColourId, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
    calibrateY_down->setColour(TextButton::buttonNormal, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
	//textButton->setColour(TextButton::buttonOnColourId, Colour(0x363d47)); // Set colour according to its position inside the button, the position is represented by the ID
	calibrateY_down->addListener(this); // Adding a listener for this button, in this case it is this class
	addAndMakeVisible(calibrateY_down); // Adding the button into this component and turning it visible

    calibrateZ_up = new TextButton("ZU"); // Create the object and set its name
	calibrateZ_up->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom); // Set the style of the corners of this button
	//calibrateAccel->setColour(TextButton::buttonColourId, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
    calibrateZ_up->setColour(TextButton::buttonNormal, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
	//textButton->setColour(TextButton::buttonOnColourId, Colour(0x363d47)); // Set colour according to its position inside the button, the position is represented by the ID
	calibrateZ_up->addListener(this); // Adding a listener for this button, in this case it is this class
	addAndMakeVisible(calibrateZ_up); // Adding the button into this component and turning it visible

	calibrateZ_down = new TextButton("ZD"); // Create the object and set its name
	calibrateZ_down->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom); // Set the style of the corners of this button
	//calibrateAccel->setColour(TextButton::buttonColourId, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
    calibrateZ_down->setColour(TextButton::buttonNormal, Colour::fromRGBA(61, 78, 69, 255)); // Set colour according to its position inside the button, the position is represented by the ID
	//textButton->setColour(TextButton::buttonOnColourId, Colour(0x363d47)); // Set colour according to its position inside the button, the position is represented by the ID
	calibrateZ_down->addListener(this); // Adding a listener for this button, in this case it is this class
	addAndMakeVisible(calibrateZ_down); // Adding the button into this component and turning it visible

    // --------------------------- SLIDER CREATION ---------------------------
	rotoSlider_x = new Slider("Threshold X"); // Create the object and set its name
	rotoSlider_x->setRange(0, 100, 0); // Set the minium value, the max value and the increment interval
	rotoSlider_x->setSliderStyle(Slider::Rotary); // Set the style of the styler, horizontal or vertical
	rotoSlider_x->setTextBoxIsEditable(false); // Set the visual style of the slider
	rotoSlider_x->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20); // Set the visual style of the slider
	rotoSlider_x->setTextValueSuffix(" "); // Set the sufix of the value shown at the left of the slider
	rotoSlider_x->addListener(this); // Adding a listener, the class that will handle this slider
	addAndMakeVisible(rotoSlider_x); // Adding the slider into this component for it to be visible

    rotoSlider_y = new Slider("Threshold Y"); // Create the object and set its name
	rotoSlider_y->setRange(0, 100, 0); // Set the minium value, the max value and the increment interval
	rotoSlider_y->setSliderStyle(Slider::Rotary); // Set the style of the styler, horizontal or vertical
	rotoSlider_y->setTextBoxIsEditable(false); // Set the visual style of the slider
	rotoSlider_y->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20); // Set the visual style of the slider
	rotoSlider_y->setTextValueSuffix(" "); // Set the sufix of the value shown at the left of the slider
	rotoSlider_y->addListener(this); // Adding a listener, the class that will handle this slider
	addAndMakeVisible(rotoSlider_y); // Adding the slider into this component for it to be visible

    rotoSlider_z = new Slider("Threshold Z"); // Create the object and set its name
	rotoSlider_z->setRange(0, 100, 0); // Set the minium value, the max value and the increment interval
	rotoSlider_z->setSliderStyle(Slider::Rotary); // Set the style of the styler, horizontal or vertical
	rotoSlider_z->setTextBoxIsEditable(false); // Set the visual style of the slider
	rotoSlider_z->setTextBoxStyle(Slider::TextBoxRight, false, 80, 20); // Set the visual style of the slider
	rotoSlider_z->setTextValueSuffix(" "); // Set the sufix of the value shown at the left of the slider
	rotoSlider_z->addListener(this); // Adding a listener, the class that will handle this slider
	addAndMakeVisible(rotoSlider_z); // Adding the slider into this component for it to be visible]

    // --------------------------- LABEL CREATION ----------------------------
	x_label = new Label("label", TRANS("Threshold X")); // Create the object and set its name
	x_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	x_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	x_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	x_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(x_label); // Addint the label to the component and turning it visible

	y_label = new Label("label", TRANS("Threshold Y")); // Create the object and set its name
	y_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	y_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	y_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	y_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(y_label); // Addint the label to the component and turning it visible

	z_label = new Label("label", TRANS("Threshold Z")); // Create the object and set its name
	z_label->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	z_label->setJustificationType(Justification::centredLeft); // Set the justification of the label
	z_label->setEditable(false, false, false); // Set if this label can be editable by the user or not
	z_label->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(z_label); // Addint the label to the component and turning it visible

	/*x_data = new Label("label", TRANS("x: ")); // Create the object and set its name
	x_data->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	x_data->setJustificationType(Justification::centredLeft); // Set the justification of the label
	x_data->setEditable(false, false, false); // Set if this label can be editable by the user or not
	x_data->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(x_data); // Addint the label to the component and turning it visible

	y_data = new Label("label", TRANS("y: ")); // Create the object and set its name
	y_data->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	y_data->setJustificationType(Justification::centredLeft); // Set the justification of the label
	y_data->setEditable(false, false, false); // Set if this label can be editable by the user or not
	y_data->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(y_data); // Addint the label to the component and turning it visible

	z_data = new Label("label", TRANS("z: ")); // Create the object and set its name
	z_data->setFont(Font(15.10f, Font::plain)); // Set the font size and style
	z_data->setJustificationType(Justification::centredLeft); // Set the justification of the label
	z_data->setEditable(false, false, false); // Set if this label can be editable by the user or not
	z_data->setColour(TextEditor::textColourId, Colours::black); // Set the label colour
	addAndMakeVisible(z_data); // Addint the label to the component and turning it visible*/

    // --------------------------- TOGGLE CREATION ---------------------------
    detected = Colour::fromRGBA(255, 255, 0, 255);
    nothing  = Colour::fromRGBA(61, 78, 69, 255);

    /*detectedLedX = new ToggleButton("x accel");
    detectedLedX->setColour(TextButton::buttonColourId, nothing);
    detectedLedX->setEnabled(false);
    addAndMakeVisible(detectedLedX);

    detectedLedY = new ToggleButton("y accel");
    detectedLedY->setColour(TextButton::buttonColourId, nothing);
    detectedLedY->setEnabled(false);
    addAndMakeVisible(detectedLedY);

    detectedLedZ = new ToggleButton("z accel");
    detectedLedZ->setColour(TextButton::buttonColourId, nothing);
    detectedLedZ->setEnabled(false);
    addAndMakeVisible(detectedLedZ);*/
    
    // initi variables
    thresh_x = 0.0;
    thresh_y = 0.0;
    thresh_z = 0.0;
}

void MovementDetectorUI::resized(){
    // Set the limits of the UI_canvas
	setBounds(0, 0, getWidth(), getHeight());

	// Set the limits, size, and location of each component for them to be visible

	// Set the position, width and heigh of the elements - x, y, width, height
	int topMargin   = 25;
	int leftMargin	= 5;
 
    // ------------- FIRST ROW --------------------
 
    calibrateX_up->setBounds(
    leftMargin, 
    topMargin, 
    50, 
    20);

    calibrateX_down->setBounds(
    getNext_X(calibrateX_up), 
    topMargin, 
    50, 
    20);

    calibrateY_up->setBounds(
    getNext_X(calibrateX_down), 
    topMargin, 
    50, 
    20);

    calibrateY_down->setBounds(
    getNext_X(calibrateY_up), 
    topMargin, 
    50, 
    20);

    calibrateZ_up->setBounds(
    getNext_X(calibrateY_down), 
    topMargin, 
    50, 
    20);

    calibrateZ_down->setBounds(
    getNext_X(calibrateZ_up), 
    topMargin, 
    50, 
    20);


    // ------------- SECOND ROW -----------------------

    double centerDist = 10;
    x_label->setBounds(leftMargin, getNext_Y(calibrateX_up) + 10, 100, 10);
    y_label->setBounds(getNext_X(x_label) + 10 , getNext_Y(calibrateX_up) + 10, 100, 10);
    z_label->setBounds(getNext_X(y_label) + 10, getNext_Y(calibrateX_up) + 10, 100, 10);

    // ------------- THIRD ROW ------------------------

    rotoSlider_x->setBounds(leftMargin             , getNext_Y(x_label) + 10, 100, 30);
    rotoSlider_y->setBounds(getNext_X(rotoSlider_x) + 10 , getNext_Y(x_label) + 10, 100, 30);
    rotoSlider_z->setBounds(getNext_X(rotoSlider_y) + 10, getNext_Y(x_label) + 10, 100, 30);

    // -------------- FOURTH ROW ----------------------

    /*x_data->setBounds(leftMargin, getNext_Y(rotoSlider_x) + 5, 100, 10);
    y_data->setBounds(getNext_X(x_data) + 10 , getNext_Y(rotoSlider_x) + 5, 100, 10);
    z_data->setBounds(getNext_X(y_data) + 10, getNext_Y(rotoSlider_x) + 5, 100, 10);   

    // ------------- FIFTH ROW ------------------------

    centerDist = 20;
    detectedLedX->setBounds(
        rotoSlider_x->getX() + centerDist, 
        getNext_Y(x_data) + 2, 
        100, 
        20);

    detectedLedY->setBounds(
        rotoSlider_y->getX() + centerDist, 
        getNext_Y(x_data) + 2, 
        100, 
        20);

    detectedLedZ->setBounds(
        rotoSlider_z->getX() + centerDist, 
        getNext_Y(x_data) + 2, 
        100, 
        20);*/

}

void MovementDetectorUI::resetDetectionLeds(){
    //detectedLedX->setColour(TextButton::buttonColourId, nothing);
   // detectedLedY->setColour(TextButton::buttonColourId, nothing);
   // detectedLedZ->setColour(TextButton::buttonColourId, nothing);
}

void MovementDetectorUI::turnXLedOn(){
   // detectedLedX->setColour(TextButton::buttonColourId, detected);
}

void MovementDetectorUI::turnYLedOn(){
   // detectedLedY->setColour(TextButton::buttonColourId, detected);
}

void MovementDetectorUI::turnZLedOn(){
  //  detectedLedZ->setColour(TextButton::buttonColourId, detected);
}

void MovementDetectorUI::buttonClicked(Button* buttonClicked){
    std::string name = buttonClicked->getName().toStdString();

    if(strcmp(name.c_str(), "XU") == 0)
        f_calibrateX_up = true;

    if(strcmp(name.c_str(), "XD") == 0)
        f_calibrateX_down = true;

    if(strcmp(name.c_str(), "YU") == 0)
        f_calibrateY_up = true;

    if(strcmp(name.c_str(), "YD") == 0)
        f_calibrateY_down = true;

    if(strcmp(name.c_str(), "ZU") == 0)
        f_calibrateZ_up = true;

    if(strcmp(name.c_str(), "ZD") == 0)
        f_calibrateZ_down = true;
}

void MovementDetectorUI::sliderValueChanged(Slider* sliderChanged){
    double value = sliderChanged->getValue();
    std::string name = sliderChanged->getName().toStdString();

    if(strcmp(name.c_str(), "Threshold X") == 0)
        thresh_x = value;

    if(strcmp(name.c_str(), "Threshold Y") == 0)
        thresh_y = value;

    if(strcmp(name.c_str(), "Threshold Z") == 0)        
        thresh_z = value;
}

double MovementDetectorUI::get_thresh_x(){
    return thresh_x;
}

double MovementDetectorUI::get_thresh_y(){
    return thresh_y;
}

double MovementDetectorUI::get_thresh_z(){
    return thresh_z;
}