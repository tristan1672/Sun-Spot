/*****************************************************************
  *  \file Timer.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  System component.
  *  - GetTime
  *		Get and sets delta time(Called in main)
  *
  *  - LevelTime
  *		Updates and return level time
  *
  *  - DisplayTime
  *		Display time on screen
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include "Timer.hpp"

 /*****************************************************************
  * \brief
  *		Get and sets delta time(Called in main)
 ****************************************************************/
void GetTime() {
	e_deltaTime = AEFrameRateControllerGetFrameTime();
	if(e_deltaTime > 0.01667f)
		e_deltaTime = 0.01667f;
}

/*****************************************************************
 * \brief
 *		Updates level time
****************************************************************/
void LevelTime() {
	e_levelTime += e_deltaTime;
}

/*****************************************************************
 * \brief
 *		Display time on screen
 * 
 * \param pos_x
 *		X position of where time to be printed
 * 
 * \param pos_y
 *		Y position of where time to be printed
****************************************************************/
void DisplayTime(float pos_x, float pos_y) {
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	char tempStr[6];
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
		AEGfxPrint(e_fontID, tempStr, pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);
	} 
	else { // Print seconds
		snprintf(tempStr, sizeof tempStr, "   %02d", static_cast<int>(second));
		AEGfxPrint(e_fontID, tempStr, pos_x, pos_y, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	// Prints miliseconds in a smaller font size
	snprintf(tempStr, sizeof tempStr, ".%02.0f", miliseconds);
	AEGfxPrint(e_fontID, tempStr, pos_x + 0.2f, pos_y, 0.7f, 1.0f, 1.0f, 1.0f);
}