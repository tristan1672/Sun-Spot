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

#define GROUND_LEVEL 20

 frogPos frog;
 mousePos mouse;
 vector Direction;

int gGameRunning = 1;
bool flick = false;

// Pointer to Mesh
AEGfxVertexList* groundMesh = nullptr;

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
	frog.Y = 30.0f;
	frog.velX = 0.0f;
	frog.velY = 0.0f;
	frog.onFloor = true;

	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	// Saving the mesh (list of triangles) in pMesh
	groundMesh = AEGfxMeshEnd();

	MakeMesh();
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level1_Update()
{
	if (!frog.onFloor) {
		frog.velY += static_cast<float>(e_gravity * AEFrameRateControllerGetFrameTime());
		frog.Y += static_cast<float>(frog.velY * AEFrameRateControllerGetFrameTime());
		frog.X += static_cast<float>(frog.velX * AEFrameRateControllerGetFrameTime());
	}


	//if (frog.Y > GROUND_LEVEL) {
	//	frog.velY += static_cast<float>(e_gravity * AEFrameRateControllerGetFrameTime());
	//	frog.Y += static_cast<float>(frog.velY * AEFrameRateControllerGetFrameTime());
	//	frog.X += static_cast<float>(frog.velX * AEFrameRateControllerGetFrameTime());
	//}
	//if (frog.Y <= GROUND_LEVEL && !frog.onFloor) {
	//	frog.velY = 0.0f;
	//	frog.velX = 0.0f;
	//	frog.Y = GROUND_LEVEL;
	//	frog.onFloor = true;
	//}

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

	collisionCheck(frog.X, frog.Y);

}

// ----------------------------------------------------------------------------
// This function sends data that needs to be drawn to the graphic engine
// It is called after update to show animation/movement
// ----------------------------------------------------------------------------
void Level1_Draw()
{

	// Set the background to black.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	// Tell the engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set the tint to white, so that the sprite can 
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	// Set the texture to pTex
	//AEGfxTextureSet(pTex, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33 rotate = { 0 };
	AEMtx33 translate = { 0 };
	AEMtx33 transform = { 0 };

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (s_levelGrid[i][j] == '1') {

				AEMtx33Scale(&scale, gridWidth, gridHeight);
				AEMtx33Rot(&rotate, 0);
				AEMtx33Trans(&translate, gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * (WINDOW_WIDTH / GRID_SIZE), -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * (WINDOW_HEIGHT / GRID_SIZE));
				AEMtx33Concat(&transform, &rotate, &scale);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(groundMesh, AE_GFX_MDM_TRIANGLES);
			}
		}
	}

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

void collisionCheck(float frogX, float frogY) {

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

	// Need find current location in grid 1st
	// Then check the surrounding for collision

	// Checking current location
	double width = -(WINDOW_WIDTH / 2.0f);
	double height = WINDOW_HEIGHT / 2.0f;
	int xCoord = 0, yCoord = 0;

	// Getting X coord in grid
	while (1) {
		if (frogX > width) {
			width += gridWidth;
			xCoord++;
		}
		else {
			xCoord -= 1;
			break;
		}
	}

	// Getting Y coord in grid
	while (1) {
		if (frogY < height) {
			height -= gridHeight;
			yCoord++;
		}
		else {
			yCoord -= 1;
			break;
		}
	}

	//std::cout << "Width Grid: " << xCoord + 1 << "\n";
	//std::cout << "Height Grid: " << yCoord + 1 << "\n";

	// Working seperately, not together
	bool leftHit = false, rightHit = false, topHit = false, btmHit = false;

	// Left & Right Collision Detecttion
	if (frogX > (xCoord*gridWidth - WINDOW_WIDTH/2.0f) && s_levelGrid[yCoord][xCoord] == '1') {
		// If on the left halve of a block
		if (frogX < (xCoord*gridWidth - WINDOW_WIDTH/2.0f + gridWidth/2.0f) ) {
			//frog.X -= 5;
			//frog.X = xCoord * gridWidth - WINDOW_WIDTH/2.0f;
			leftHit = true;

		}
		// If on the right halve of a block
		else if (frogX > (xCoord * gridWidth - WINDOW_WIDTH/2.0f + gridWidth/2.0f) ) {
			//frog.X += 5;
			//frog.X = (xCoord+1) * gridWidth - WINDOW_WIDTH/2.0f;
			rightHit = true;
		}
	}
	
	/*
	// Up & Down Collision Detecttion
	if (frogY < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight) && s_levelGrid[yCoord][xCoord] == '1') {
		// If on the top of the block (Platform below you)
		if (frog.Y > (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			frog.onFloor = true;
			//frog.Y = WINDOW_HEIGHT / 2.0f - yCoord * gridHeight;
			//frog.Y += 5;
			topHit = true;
		}
		// If on the btm of the block (Platform above you)
		else if (frog.Y < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			//frog.Y = WINDOW_HEIGHT / 2.0f - (yCoord+1) * gridHeight;
			//frog.Y -= 5;
			btmHit = true;
		}
	}
	*/

	if (frogY < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight) && s_levelGrid[yCoord][xCoord] == '1') {
		// If on the top of the block (Platform below you)
		if (frog.Y > (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			frog.onFloor = true;
			//frog.Y = WINDOW_HEIGHT / 2.0f - yCoord * gridHeight;
			//frog.Y += 5;
			topHit = true;
		}
		// If on the btm of the block (Platform above you)
		else if (frog.Y < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			//frog.Y = WINDOW_HEIGHT / 2.0f - (yCoord+1) * gridHeight;
			//frog.Y -= 5;
			btmHit = true;
		}
	}
	

	if (rightHit == true) {
		frog.X += static_cast<float>(frog.velX * AEFrameRateControllerGetFrameTime());
		frog.velX = 0;
		std::cout << "Hit Right 50% of block\n";
	}
	if (leftHit == true) {
		frog.X -= static_cast<float>(frog.velX * AEFrameRateControllerGetFrameTime());
		frog.velX = 0;
		std::cout << "Hit Left 50% of block \n";
	}

	if (topHit == true) {
		frog.Y -= static_cast<float>(frog.velY * AEFrameRateControllerGetFrameTime());
		std::cout << "Hit Top of block\n";
		//frog.velY = 0;
	}

	if (btmHit == true) {
		frog.Y -= static_cast<float>(frog.velY * AEFrameRateControllerGetFrameTime());
		std::cout << "Hit Btm of block\n";
		//frog.velY = 0;
	}




}