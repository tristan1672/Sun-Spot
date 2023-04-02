/*****************************************************************
  *  \file System.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  System component.
  *  - System_Initialize
  *		This function initialize the system
  *
  *  - System_Exit
  *		This function exit the system
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include <iostream>
#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "System.hpp"

/*****************************************************************
 * \brief
 *		This function initialize the system
****************************************************************/
void System_Initialize()
{
#if DEBUG
	std::cout << "System:Initialize\n";
#endif
	// Changing the window title
	AESysSetWindowTitle("Ready?Set.Jump!");

	// reset the system modules
	AESysReset();
}

/*****************************************************************
 * \brief
 *		This function exit the system
****************************************************************/
void System_Exit()
{
#if DEBUG
	std::cout << "System:Exit\n";
#endif
	AESysExit();
}
