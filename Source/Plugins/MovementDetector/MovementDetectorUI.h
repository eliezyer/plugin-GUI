#ifndef MOVEMENTDETECTORUI_H
#define MOVEMENTDETECTORUI_H

#include <JuceHeader.h>
#include <string>
#include "InterfaceHelper.h"

class MovementDetectorUI : public Component, public ButtonListener, public SliderListener
{
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MovementDetectorUI);

        // UI INTERFACE VARIABLES
        double thresh_x;
        double thresh_y;
        double thresh_z;

    public:
        // appearance
	    LookAndFeel_V2*				defaultLookAndFeel;

        // sliders
        Slider*						rotoSlider_x;
	    Slider*						rotoSlider_y;
    	Slider*						rotoSlider_z;        

        // labels
        Label*                       x_label;
        Label*                       y_label;
        Label*                       z_label;

        // data
    /*    Label*                       x_data;
        Label*                       y_data;
        Label*                       z_data;

        // Leds
        ToggleButton*                detectedLedX;
        ToggleButton*                detectedLedY;
        ToggleButton*                detectedLedZ;*/

        // Button
        Button*                      calibrateX_up;    
        Button*                      calibrateX_down;    

        Button*                      calibrateY_up;    
        Button*                      calibrateY_down;    

        Button*                      calibrateZ_up;    
        Button*                      calibrateZ_down;    

        // control flags
        bool f_calibrateX_up;
        bool f_calibrateX_down;

        bool f_calibrateY_up;
        bool f_calibrateY_down;

        bool f_calibrateZ_up;
        bool f_calibrateZ_down;


        // colors
        Colour detected;    
        Colour nothing;

        double get_thresh_x();
        double get_thresh_y();
        double get_thresh_z();
        void resetDetectionLeds();
        void turnXLedOn();
        void turnYLedOn();
        void turnZLedOn();

        // constructor/builder
        MovementDetectorUI();

        // paint and resize
	    void resized() override;

        // listeners
	    void buttonClicked(Button* buttonClicked) override;
	    void sliderValueChanged(Slider* sliderChanged) override;
};

#endif