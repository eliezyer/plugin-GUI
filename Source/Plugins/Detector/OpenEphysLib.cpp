// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include <PluginInfo.h>	// used to get information about how the shared library should be made.


// ---------------------------- SYSTEM INCLUDES TO HELP WITH ANY NECESSARY FUNCTION AND PROCESSING --------------------
#include <string> // used for string and related functions.


// -------------------------------------- EXTRA LIBRARY INCLUDES TO HELP WITH THE PROCESSING --------------------------


// ----------------------------------------------------- LOCAL INCLUDES -----------------------------------------------
#include "PluginConfig.h"


// ----------------------------------------------------- USED NAMESPACES ----------------------------------------------
using namespace Plugin; // Juce namespace with the plugin's definitions on how to create them.


// -------------------------------------- JUCE SHARED LIBRARY EXPORT DEFINITION ---------------------------------------
#ifdef WIN32
#include <Windows.h>
#define EXPORT __declspec(dllexport) // Tells to the system which functions can be seen from outside of this code
#else
#define EXPORT __attribute__((visibility("default"))) // Tells to the system which functions can be seen from outside of this code
#endif


// ---------------------------------- DEFINITIONS TO HELP BETTER ORGANIZE THE CODE ------------------------------------
#define NUM_PLUGINS 1 // Number of plugins defined in this library


// *** getLibInfo *** //
// Used to tell to the JUCE application the information about this plugin.
//---------------------------------------------------PARAM-------------------------------------------------------------
// LibraryInfo*	-> it is a reference to the information about this plugin that is used by the JUCE application.
//---------------------------------------------------RETURN------------------------------------------------------------
// Returns nothing.
//---------------------------------------------------------------------------------------------------------------------
extern "C" EXPORT void getLibInfo(Plugin::LibraryInfo* info)
{
	info->apiVersion = plugin_apiVersion;		// Tells the JUCE application which version of functions it should use.
	info->name		 = plugin_in_the_editor;	// Tells the JUCE application the name of this shared library.
	info->libVersion = plugin_libVersion;		// Tells the JUCE application the version of this shared library.
	info->numPlugins = plugin_numPlugins;		// Tells the JUCE application the number of plugins being defined in this library.
}

// *** getPluginInfo *** //
// Used to tell to the JUCE application which plugin is being used inside of this library.
//---------------------------------------------------PARAM-------------------------------------------------------------
// Index -> it is used to tell to the JUCE application which plugin from this library will be used.
// PluginInf* -> it is used to store the information of the plugin defined by the especified index.
//---------------------------------------------------RETURN------------------------------------------------------------
// Returns 0 if the operations succeed and -1 otherwise.
//---------------------------------------------------------------------------------------------------------------------
extern "C" EXPORT int getPluginInfo(int index, Plugin::PluginInfo* info)
{
	switch (index)
	{
	case 0:
		// ---- Types accepted here ----
		//	PLUGIN_TYPE_PROCESSOR
		//	PLUGIN_TYPE_RECORD_ENGINE
		//	PLUGIN_TYPE_FILE_SOURCE
		//	PLUGIN_TYPE_DATA_THREAD
		//	NOT_A_PLUGIN_TYPE
		info->type = plugin_configType; // Tells the JUCE the type of this plugin.
	
		// ---- Types accepted here ----
		//	SourceProcessor
		//	FilterProcessor
		//	SinkProcessor
		//	UtilityProcessor
		//	InvalidProcessor
		info->processor.type	= plugin_processorType;	// Tells the JUCE the functionality of this plugin.
		info->processor.name	= plugin_in_the_editor; // Tells the JUCE the name of this plugin.
		info->processor.creator = pluginMainClass;		// Tells the JUCE the file that contains the implemented processor interface.
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

// *** WINDOWS ONLY FUNCTION *** //
// Used to define that this file will generate a DLL (shared library) that can be used by other programs.
// It also especify the DLL main function call by windows applications.
//---------------------------------------------------PARAM-------------------------------------------------------------
// hDllHandle -> it is a windows HANDLE, an object that windows uses to refence to a file descriptor, that handles threads, processess and files.
// nReason -> used by windows HANDLES.
// Reserved -> used by windows HANDLES.
//---------------------------------------------------RETURN------------------------------------------------------------
// Returns TRUE. It is the same as returning 0 inside of the main() of any common program.
//---------------------------------------------------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain(IN HINSTANCE hDllHandle,
	IN DWORD     nReason,
	IN LPVOID    Reserved)
{
	return TRUE;
}
//---------------------------------------------------------------------------------------------------------------------
#endif
