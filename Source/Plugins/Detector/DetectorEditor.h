#ifndef ALY_H
#define ALY_H

// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include <EditorHeaders.h> // used to extend the generic processor editor from juce that deals with UI


// ---------------------------- SYSTEM INCLUDES TO HELP WITH ANY NECESSARY FUNCTION AND PROCESSING --------------------
#include <stdio.h> // used for printf, fprintf, fread...


// -------------------------------------- EXTRA LIBRARY INCLUDES TO HELP WITH THE PROCESSING --------------------------


// ----------------------------------------------------- LOCAL INCLUDES -----------------------------------------------
#include "Detector.h" // used to have access to the created plugin type to export as a shared library.
#include "DetectorUI.h" // used to hold the UI objects and layout

// ----------------------------------------------------- USED NAMESPACES ----------------------------------------------
using namespace Plugin; // Juce namespace with the plugin's definitions on how to create them.


// ---------------------------------- DEFINITIONS TO HELP BETTER ORGANIZE THE CODE ------------------------------------

// --------------------------------------------------- USED NAMESPACES ------------------------------------------------
using namespace std;

// ---------------- PLUGIN UI CLASS. Extends the GenericEditor and a liesteners to interac with the user --------------
class DetectorEditor : public GenericEditor
{

public:
	DetectorEditor();

	// *** Default constructor *** //
	// Used to define how this class will be build.
	//---------------------------------------------------PARAM-------------------------------------------------------------
	// Parent Node				 -> is the plugin that is located on the left of this plugin in the graph node editor.
	// UseDefaultPrameterEditors -> specify if the parameters used in this plugin will be load with default configurations.
	//---------------------------------------------------RETURN------------------------------------------------------------
	// Returns an instance of the Plugin Interface.
	//---------------------------------------------------------------------------------------------------------------------
	DetectorEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);

	void updateSettings() override;

	// *** Default destructor *** //
	// Used to deallocate all data that were allocated in the computer's memory.
	virtual ~DetectorEditor();

	void resized() override;

	DetectorUI pluginUI;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorEditor);
};

#endif
