// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include <PluginInfo.h>	// used to get information about how the shared library should be made.

// ------------------------------- PLUGIN MAIN FILE -------------------------------------------------------------------
#include "MovementDetector.h"

// THIS FILE IS USED ONLY TO HELP DEFINE THE TYPE AND OTHER INFORMATIONS NECESSARY TO CONSTRUCT THE PLUGIN, THUS AVOIDING THE 
// NECESSITY IN CREATING OR HANDLING THE OpenEphysLib.cpp

static const char* plugin_in_the_editor	= "Movement Detector"; // Tells the JUCE application the name of this shared library.
static const int plugin_apiVersion		= PLUGIN_API_VER; // Tells the JUCE application which version of functions it should use.
static const int plugin_libVersion		= 1; // Tells the JUCE application the version of this shared library.
static const int plugin_numPlugins		= 1; // Tells the JUCE application the number of plugins being defined in this library.
			
// ---- Types accepted here ----
//	PLUGIN_TYPE_PROCESSOR
//	PLUGIN_TYPE_RECORD_ENGINE
//	PLUGIN_TYPE_FILE_SOURCE
//	PLUGIN_TYPE_DATA_THREAD
//	NOT_A_PLUGIN_TYPE
static const Plugin::PluginType plugin_configType = Plugin::PLUGIN_TYPE_PROCESSOR; // Tells the JUCE the type of this plugin.

// ---- Types accepted here ----
//	SourceProcessor
//	FilterProcessor
//	SinkProcessor
//	UtilityProcessor
//	InvalidProcessor
static const Plugin::ProcessorType plugin_processorType = Plugin::FilterProcessor;	// Tells the JUCE the functionality of this plugin.
static GenericProcessor* pluginMainClass(){ return new MovementDetector(); };	// Tells the JUCE the class that contains the implemented processor, plugin, interface.


