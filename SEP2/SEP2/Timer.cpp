/*
  *  \file Timer.cpp
  *  \author      : Peh Zong Lin Adrian
  *  \par DP Email: p.zonglinadrian\@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *  Timer component.
  *  - Get and returns delta time
  *  - Updates and return level time
  *  - Display time on screen
  *
*/

#include "Timer.hpp"
#include <string>

// Get and returns delta time
float GetTime() {
	return e_deltaTime = AEFrameRateControllerGetFrameTime();
}

// Updates and return level time
float LevelTime() {
	e_levelTime += e_deltaTime;
	return e_levelTime;
}

// Display time on screen
void DisplayTime() {
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	char tempStr[30];
	snprintf(tempStr, sizeof tempStr, "%10.2f", e_levelTime);
	AEGfxPrint(e_fontID, tempStr, 0.5f, 0.86f ,1.0f, 1.0f, 1.0f, 1.0f);
}