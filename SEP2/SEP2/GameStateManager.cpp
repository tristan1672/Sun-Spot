// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.h"
#include "GameStateManager.h"
#include "Ultilities.h"
#include "Level1.h"
// ---------------------------------------------------------------------------


int current = 0, previous = 0, next = 0;

FP e_fpLoad = nullptr, e_fpInitialize = nullptr, e_fpUpdate = nullptr, e_fpDraw = nullptr, e_fpFree = nullptr, e_fpUnload = nullptr;


//
float e_gravity{ 150.0f }, e_jumpForce(200.0f);

extern frogPos frog;
extern mousePos mouse;
extern vector Direction;


// ----------------------------------------------------------------------------
// This function initialize the gamestate manager
// It is called once at the before the start of the game loop 
// ----------------------------------------------------------------------------
void GSM_Initialize(int startingState)
{
	current = previous = next = startingState;

	std::cout << "GSM:Initialize\n";

	Direction.X = 0;
	Direction.Y = 0;

	frog.X = 0;
	frog.Y = 0;
	frog.velX = 0;
	frog.velY = 0;
	frog.onFloor = true;

	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;


}

// ----------------------------------------------------------------------------
// This function initialize gamestate function pointers
// It is called once at the start of the game loop
// ----------------------------------------------------------------------------
void GSM_Update()
{
	std::cout << "GSM:Update\n";

	// Informing the system about the loop's start
	AESysFrameStart();

	// Handling Input
	AEInputUpdate();

	switch (next)
	{
	case GS_LEVEL1:
		e_fpLoad = Level1_Load;
		e_fpInitialize = Level1_Initialize;
		e_fpUpdate = Level1_Update;
		e_fpDraw = Level1_Draw;
		e_fpFree = Level1_Free;
		e_fpUnload = Level1_Unload;
		break;

	case GS_RESTART:
		break;

	case GS_QUIT:
		break;

	default:
		break;
	}

}