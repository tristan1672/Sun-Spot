/*****************************************************************
  *  \file GameStateManager.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  File containing functions used by gamestate manager
  * - GSM_Initialize
  *		This function initialize the gamestate manager
  *     It is called once at the before the start of the game loop 
  * 
  *  - GSM_Update
  *		This function initialize gamestate function pointers
  *      It is called once at the start of the game loop
  * 
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include <iostream>
#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "Utilities.hpp"
#include "Level.hpp"
#include "MainMenu.hpp"
#include "SaveManager.hpp"
#include "SplashScreen.hpp"
#include "Credits.hpp"

#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

void GSM_Initialize(int startingState);

void GSM_Update();

#endif // GAME_STATE_MANAGER_HPP