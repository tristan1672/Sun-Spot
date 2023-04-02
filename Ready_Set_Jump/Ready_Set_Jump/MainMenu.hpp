/*****************************************************************
  *  \file MainMenu.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)
  *
  *  \brief
  * Main Menu Scene
  * All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/

#pragma once
#include "AEEngine.h"
#include "GameObjClasses.hpp"
#include "PreCompiledHeader.hpp"
#include "UI.hpp"
#include "LevelSelect.hpp"
#include "GameStateManager.hpp"
#include "Level.hpp"
#include "SaveManager.hpp"
#include "Credits.hpp"
#include "Particles.hpp"

void Menu_Load();

void Menu_Initialize();

void Menu_Update();

void Menu_Draw();

void Menu_Free();

void Menu_Unload();
