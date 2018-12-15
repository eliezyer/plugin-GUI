#ifndef INTERFACE_HELPER_H
#define INTERFACE_HELPER_H

// ------------------------------- MANDATORY INCLUDE TO EXTEND THE PLUGIN INTERFACES FROM JUCE ------------------------
#include "MovementDetectorUI.h"

// ---------------------------- SYSTEM INCLUDES TO HELP WITH ANY NECESSARY FUNCTION AND PROCESSING --------------------

// -------------------------------------- EXTRA LIBRARY INCLUDES TO HELP WITH THE PROCESSING --------------------------

// ----------------------------------------------------- LOCAL INCLUDES -----------------------------------------------

// ----------------------------------------------------- USED NAMESPACES ----------------------------------------------

// ---------------------------------- DEFINITIONS TO HELP BETTER ORGANIZE THE CODE ------------------------------------

// --------------------------------------------------- USED NAMESPACES ------------------------------------------------

// ---------------- PLUGIN UI CLASS. Extends the GenericEditor and a liesteners to interac with the user --------------

#define SPACING 0
#define TOP_MARGIN 30
#define THREE_ELEMENT_SQUARED_SIZE 50

int getNext_X(Component* reference);
int getNext_Y(Component* reference);

#endif