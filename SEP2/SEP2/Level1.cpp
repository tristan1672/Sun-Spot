// ---------------------------------------------------------------------------
// includes
#include <iostream>
#include <fstream>
#include <string>

#include "AEEngine.h"
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

// Pointer to Mesh
AEGfxVertexList* pMesh = nullptr;

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
	pMesh = AEGfxMeshEnd();

}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level1_Update()
{
	//std::cout << "Level 1:Update\n";

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
	//std::cout << "Level 1:Draw\n";

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
	AEMtx33Scale(&scale, 10.f, 10.f);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, frog.X, frog.Y);
	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);
	// Actually drawing the mesh 
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);


	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (s_levelGrid[i][j] == '1') {
				AEMtx33Trans(&translate, -(1270.0f / 2.0f) + j * (1270.0f / GRID_SIZE), (720.0f / 2.0f) - i * (720.0f / GRID_SIZE));
				AEMtx33Concat(&transform, &rotate, &scale);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

				std::cout << "Draw grid\n";
			}
		}
	}
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