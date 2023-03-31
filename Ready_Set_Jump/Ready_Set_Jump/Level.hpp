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

void PlatformAnimationUpdate(void);