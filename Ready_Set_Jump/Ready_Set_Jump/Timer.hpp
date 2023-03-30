#pragma once
#include "Utilities.hpp"

// Get and sets delta time(Called in main)
void GetTime();

// Updates and return level time
float LevelTime();

// Display time on screen
void DisplayTime(float pos_x, float pos_y);