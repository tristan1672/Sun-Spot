#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Input.hpp"
#include "AEEngine.h"
#include "GameObjClasses.hpp"
#include "PreCompiledHeader.hpp"
#include "Ultilities.hpp"
#include "UI.hpp"

extern DynamicObj Player;
extern Platform** platform;
extern GameObject jumpArrow;
extern std::string fileToLoad;

void Level_Load();

void Level_Initialize();

void Level_Update();

void Level_Draw();

void Level_Free();

void Level_Unload();

int ImportMapDataFromFile(char* FileName);