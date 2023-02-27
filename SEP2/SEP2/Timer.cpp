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


// ----------------------------------------------------------------------------
// Get and returns delta time
// ----------------------------------------------------------------------------
float GetTime() {
	return e_deltaTime = AEFrameRateControllerGetFrameTime();
}

// ----------------------------------------------------------------------------
// Updates and return level time
// ----------------------------------------------------------------------------
float LevelTime() {
	e_levelTime += e_deltaTime;
	return e_levelTime;
}

// ----------------------------------------------------------------------------
// Display time on screen
// ----------------------------------------------------------------------------
void DisplayTime() {
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	char tempStr[30];
	int minute = static_cast<int>(e_levelTime / 60.0f);
	float second = e_levelTime, miliseconds = e_levelTime * 100;

	while (miliseconds > 100.0f) {
		miliseconds -= 100;
	}

	while (second > 60.0f) {
		second -= 60.0f;
	}

	if (minute > 0) { // Print minute and seconds
		snprintf(tempStr, sizeof tempStr, "%2d:%02d", minute, static_cast<int>(second));
		AEGfxPrint(e_fontID, tempStr, 0.58f, 0.86f, 1.0f, 1.0f, 1.0f, 1.0f);
	} 
	else { // Print seconds
		snprintf(tempStr, sizeof tempStr, "   %02d", static_cast<int>(second));
		AEGfxPrint(e_fontID, tempStr, 0.58f, 0.86f, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	// Prints miliseconds in a smaller font size
	snprintf(tempStr, sizeof tempStr, ".%02.0f", miliseconds);
	AEGfxPrint(e_fontID, tempStr, 0.82f, 0.86f, 0.7f, 1.0f, 1.0f, 1.0f);
}