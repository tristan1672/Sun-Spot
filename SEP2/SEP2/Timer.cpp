#include "Timer.hpp"
#include <string>

float GetTime() {
	return e_deltaTime = AEFrameRateControllerGetFrameTime();
}

float LevelTime() {
	e_levelTime += e_deltaTime;
	return e_levelTime;
}

void DisplayTime() {
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	char tempStr[30];
	snprintf(tempStr, sizeof tempStr, "%10.2f", e_levelTime);
	AEGfxPrint(e_fontID, tempStr, 0.5f, 0.86f ,1.0f, 1.0f, 1.0f, 1.0f);
}