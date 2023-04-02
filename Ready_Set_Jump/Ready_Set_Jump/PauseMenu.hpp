/*****************************************************************
  *  \file PauseMenu.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao) 
  *
  *  \brief
  *  Defination of functions that will make the pause menu draw
  *  -CreatePauseMenu()
  *		creates and allocates memories for pasue menu objs
  * -PauseMenuBehaviour(mousePos mouse)
  *		when resume button was pressed, the game will resume
  *		when main menu is pressed, goes to the main menu
  *		when quit button was pressed, quit the game
  * -DrawPauseMenu()
  *		draws all objects in pause menu
  * -FreePauseMenu()
  *		frees memories allocated
  *
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "Utilities.hpp"

#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

namespace PauseMenu {
	void CreatePauseMenu();
	void PauseMenuBehaviour(mousePos mouse);
	void DrawPauseMenu();
	void FreePauseMenu();
}

#endif // PAUSE_MENU_HPP