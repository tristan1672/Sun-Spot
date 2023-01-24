// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "GameStateManager.hpp"
#include "Ultilities.hpp"
#include "Level1.hpp"
// ---------------------------------------------------------------------------


int current = 0, previous = 0, next = 0;

FP e_fpLoad = nullptr, e_fpInitialize = nullptr, e_fpUpdate = nullptr, e_fpDraw = nullptr, e_fpFree = nullptr, e_fpUnload = nullptr;


// ----------------------------------------------------------------------------
// This function initialize the gamestate manager
// It is called once at the before the start of the game loop 
// ----------------------------------------------------------------------------
void GSM_Initialize(int startingState)
{
	current = previous = next = startingState;

	std::cout << "GSM:Initialize\n";
}

// ----------------------------------------------------------------------------
// This function initialize gamestate function pointers
// It is called once at the start of the game loop
// ----------------------------------------------------------------------------
void GSM_Update()
{
	std::cout << "GSM:Update\n";

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