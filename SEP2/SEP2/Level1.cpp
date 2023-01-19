// ---------------------------------------------------------------------------
// includes
#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "AEEngine.h"
#include "DrawShape.h"
#include "PreCompiledHeader.h"
#include "Ultilities.h"
#include "Level1.h"
#include "Input.h"
// ---------------------------------------------------------------------------

 frogPos frog;
 mousePos mouse;
 vector Direction;

int gGameRunning = 1;
bool flick = false;
static int s_levelGrid[GRID_SIZE][GRID_SIZE];



// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level1_Load()
{
	std::cout << "Level 1:Load\n";

	std::fstream level1Map("Assets/Script/Level1.txt", std::ios_base::in);

	if (level1Map.is_open()) {
		std::cout << "Level 1 File opened\n";
	}
	else {
		std::cout << "Level 1 File Cannot be opened\n";
		exit(0);
	}

	char character = 0;
	int i = 0, j = 0;
	while (level1Map.get(character)) {

		if (j == GRID_SIZE) {
			j = 0;
			i++;

			if (i == GRID_SIZE) {
				break;
			}
		}

		if (character == '0' || character == '1') {
			s_levelGrid[i][j] = character;
			j++;
		}
		
		//std::cout << character;
		
	}

}

// ----------------------------------------------------------------------------
// This function initialize game object instances
// It is called once at the start of the state
// ----------------------------------------------------------------------------
void Level1_Initialize()
{
	std::cout << "Level 1:Initialize\n";

	Direction.X = 0.0f;
	Direction.Y = 0.0f;

	frog.X = 0.0f;
	frog.Y = 0.0f;
	frog.velX = 0.0f;
	frog.velY = 0.0f;
	frog.onFloor = true;

	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;

	MakeMesh();
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level1_Update()
{

	if (frog.Y > 0.0f) {
		frog.velY += static_cast<float>(e_gravity * AEFrameRateControllerGetFrameTime());
		frog.Y += static_cast<float>(frog.velY * AEFrameRateControllerGetFrameTime());
		frog.X += static_cast<float>(frog.velX * AEFrameRateControllerGetFrameTime());
	}
	if (frog.Y <= 0.0f && !frog.onFloor) {
		frog.velY = 0.0f;
		frog.velX = 0.0f;
		frog.Y = 0.0f;
		frog.onFloor = true;
	}

	if (AEInputCheckTriggered(AEVK_SPACE) && frog.onFloor) {
		Input_Handle_Space(); // Takes in a input
	}
	// Mouse
	if (AEInputCheckTriggered(AEVK_LBUTTON) && frog.onFloor) {
		AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
	}
	if (AEInputCheckCurr(AEVK_LBUTTON) && frog.onFloor) {
		Input_Handle_HoldCheck();
	}
	if (AEInputCheckReleased(AEVK_LBUTTON) && frog.onFloor) {
		AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
		Input_Handle_Jump();
	}


}

// ----------------------------------------------------------------------------
// This function sends data that needs to be drawn to the graphic engine
// It is called after update to show animation/movement
// ----------------------------------------------------------------------------
void Level1_Draw()
{

	// Set the background to black.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	DrawRect({ frog.X,frog.Y });
}

// ----------------------------------------------------------------------------
// This function frees objects instances
// It is called after to prepare the state to be unloaded or initialized again
// ----------------------------------------------------------------------------
void Level1_Free()
{
	std::cout << "Level 1:Free\n";
}

// ----------------------------------------------------------------------------
// This function dumps all loaded during Level1_Load()
// It is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{
	std::cout << "Level 1:Unload\n";
}