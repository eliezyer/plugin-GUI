#include "DetectorEditor.h"
#include "InterfaceHelper.h"
//--------------------------------------------------------------------------------------------------------------
DetectorEditor::DetectorEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors = true) : GenericEditor(parentNode, useDefaultParameterEditors)
{
	// ------------------------------------- CONFIGURING GROUPS OF ELEMENTS ------------------------------------
	//pluginUI.toBack();

	// ---------------------------- ADDING GROUPS OS ELEMENTS TO THE PLUGIN'S UI -------------------------------
	addAndMakeVisible(&pluginUI);
	//addAndMakeVisible(&canvas);

	// ---------------------------- CONFIGURE WIDTH OF THIS PLUGIN ---------------------------------------------
	const int pluginWidth = 400;
	setDesiredWidth(pluginWidth);
}
//--------------------------------------------------------------------------------------------------------------
DetectorEditor::~DetectorEditor()
{
}
//--------------------------------------------------------------------------------------------------------------
void DetectorEditor::updateSettings(){
	int channelCount = getProcessor()->getNumInputs();
	pluginUI.updateChannel(channelCount);
}
//--------------------------------------------------------------------------------------------------------------
void DetectorEditor::resized(){
	GenericEditor::resized();

	const int xPosInitial = 0;
	const int yPosIntiial = 0;

	const int width  = 850;
	const int height = 200;

	// Set the position and bounds of this group of elements inside the plugin UI
	pluginUI.setBounds(xPosInitial, yPosIntiial, width, height);
	//canvas.setBounds(850, yPosIntiial, 200, 100);
}