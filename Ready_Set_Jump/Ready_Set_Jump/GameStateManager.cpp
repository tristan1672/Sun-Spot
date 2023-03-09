// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "GameStateManager.hpp"
#include "Ultilities.hpp"
#include "Level.hpp"
// ---------------------------------------------------------------------------


int current = 0, previous = 0, next = 0;

FP e_fpLoad = nullptr, e_fpInitialize = nullptr, e_fpUpdate = nullptr, e_fpDraw = nullptr, e_fpFree = nullptr, e_fpUnload = nullptr;

s8 e_fontID;

// ----------------------------------------------------------------------------
// This function initialize the gamestate manager
// It is called once at the before the start of the game loop 
// ----------------------------------------------------------------------------
void GSM_Initialize(int startingState)
{
	current = previous = next = startingState;
	e_fontID = AEGfxCreateFont("Assets/Font/kongtext.ttf", 30);
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
		e_fpLoad = Level_Load;
		e_fpInitialize = Level_Initialize;
		e_fpUpdate = Level_Update;
		e_fpDraw = Level_Draw;
		e_fpFree = Level_Free;
		e_fpUnload = Level_Unload;
		break;

	case GS_RESTART:
		break;

	case GS_QUIT:
		// Frees font before closing executable
		AEGfxDestroyFont(e_fontID);
		break;

	default:
		break;
	}

}