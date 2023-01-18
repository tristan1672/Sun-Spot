// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.h"
#include "System.h"
// ---------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// This function initialize the system
// It should be called once before the start of the game loop
// ----------------------------------------------------------------------------
void System_Initialize()
{
	std::cout << "System:Initialize\n";

	// Changing the window title
	AESysSetWindowTitle("Froggy!");

	// reset the system modules
	AESysReset();
}

// ----------------------------------------------------------------------------
// This function initialize the system
// It should be called once at the end of the programe
// ----------------------------------------------------------------------------
void System_Exit()
{
	std::cout << "System:Exit\n";
	AESysExit();
}
