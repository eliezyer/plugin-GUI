#include "MovementDetectorEditor.h"
#include "InterfaceHelper.h"

//--------------------------------------------------------------------------------------------------------------
MovementDetectorEditor::MovementDetectorEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors = true) 
: GenericEditor(parentNode, useDefaultParameterEditors)
{
	// ------------------------------------- CONFIGURING GROUPS OF ELEMENTS ------------------------------------
	user_interface.toBack();
	//pluginUI.toBack();
	//pluginUIB.toBack();

	// ---------------------------- ADDING GROUPS OS ELEMENTS TO THE PLUGIN'S UI -------------------------------
	addAndMakeVisible(&user_interface);
	//addAndMakeVisible(&canvas);

	// ---------------------------- CONFIGURE WIDTH OF THIS PLUGIN ---------------------------------------------
	const int pluginWidth = 360;
	setDesiredWidth(pluginWidth);
}
//--------------------------------------------------------------------------------------------------------------
MovementDetectorEditor::~MovementDetectorEditor()
{
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetectorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
}
//--------------------------------------------------------------------------------------------------------------
void MovementDetectorEditor::resized(){
	GenericEditor::resized();

	const int xPosInitial = 0;
	const int yPosIntiial = 0;

	const int width  = 600;
	const int height = 200;

	// Set the position and bounds of this group of elements inside the plugin UI
	user_interface.setBounds(xPosInitial, yPosIntiial, width, height);
	//pluginUI.setBounds(xPosInitial, yPosIntiial, width, height);
	//canvas.setBounds(canvasX, TOP_MARGIN, canvas_width, canvas_height);
}
