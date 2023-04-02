/*****************************************************************
* \file Level.hpp
* \project name : Ready ? Set.Jump!
*\author(s) : Peh Zong Lin Adrian(p.zonglinadrian) (50%)
*             - Bitmap reading and storing
*             - Made majority of the levels
*			  - Texture setting for objects and platforms in bitmap
*             - Reset player if out of play area
*             - Collision check
*             - Object collision update
*			  - Added particles
*             - Audio
*            : Xiao Jun Yu(junyu.xiao)             (30%)
*			  - Loaded textures
*             - Save file
*             - Game physics
*            : Tristan Tham Rui Hong (t.tham)       (20%)
*             - Cam
*             - Win scene
*\brief
* the basic logics to our levels and the game states, loops for our game
* All content © 2023 DigiPen Institute of Technology Singapore.All rights reserved.
* ***************************************************************/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Input.hpp"
#include "AEEngine.h"
#include "GameObjClasses.hpp"
#include "PreCompiledHeader.hpp"
#include "Utilities.hpp"
#include "UI.hpp"
#include "GameStateManager.hpp"
#include "PlatformTexture.hpp"
#include "Particles.hpp"

extern DynamicObj Player;
extern Platform** platform;
extern GameObject jumpArrow;
extern std::string fileToLoad;
extern bool isTutorial;
extern int levelNumber;

void Level_Load();

void Level_Initialize();

void Level_Update();

void Level_Draw();

void Level_Free();

void Level_Unload();

int ImportMapDataFromFile(char* FileName);

void AnimationUpdate(void);