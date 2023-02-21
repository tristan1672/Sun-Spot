#include "Timer.hpp"

float GetTime() {
	return e_deltaTime = AEFrameRateControllerGetFrameTime();
}

float LevelTime() {
	e_levelTime += e_deltaTime;
	return e_levelTime;
}

