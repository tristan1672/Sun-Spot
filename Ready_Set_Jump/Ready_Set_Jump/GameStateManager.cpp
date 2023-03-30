/*
  *  \file GameStateManager.cpp
  *  \author      : Peh Zong Lin Adrian
  *  \par DP Email: p.zonglinadrian\@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *  Game State Manager
  *  - Fuction Pointers to differnt scene fuctions
  *
*/

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes
#include "GameStateManager.hpp"
// --------------------------------------------------------------------------- // End of includes


int e_current_state = 0, e_previous_state = 0, e_next_state = 0;

FP e_fpLoad = nullptr, e_fpInitialize = nullptr, e_fpUpdate = nullptr, e_fpDraw = nullptr, e_fpFree = nullptr, e_fpUnload = nullptr;

// ----------------------------------------------------------------------------
// This function initialize the gamestate manager
// It is called once at the before the start of the game loop 
// ----------------------------------------------------------------------------
void GSM_Initialize(int startingState)
{
	std::cout << "GSM:Initialize\n";

	e_current_state = e_previous_state = e_next_state = startingState;
	Save::ReadFile();
}

// ----------------------------------------------------------------------------
// This function initialize gamestate function pointers
// It is called once at the start of the game loop
// ----------------------------------------------------------------------------
void GSM_Update()
{
	std::cout << "GSM:Update\n";

	switch (e_next_state)
	{
	case GS_SPLASH:
		e_fpLoad = SplashScreen_Load;
		e_fpInitialize = SplashScreen_Initialize;
		e_fpUpdate = SplashScreen_Update;
		e_fpDraw = SplashScreen_Draw;
		e_fpFree = SplashScreen_Free;
		e_fpUnload = SplashScreen_Unload;
		break;
	case GS_MAINMENU:
		e_fpLoad = Menu_Load;
		e_fpInitialize = Menu_Initialize;
		e_fpUpdate = Menu_Update;
		e_fpDraw = Menu_Draw;
		e_fpFree = Menu_Free;
		e_fpUnload = Menu_Unload;
		break;
	case GS_CREDITS:
		e_fpLoad = Credits_Load;
		e_fpInitialize = Credits_Initialize;
		e_fpUpdate = Credits_Update;
		e_fpDraw = Credits_Draw;
		e_fpFree = Credits_Free;
		e_fpUnload = Credits_Unload;
		break;
	case GS_LEVEL:
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
		AEGfxDestroyFont(e_creditFontID);
		break;

	default:
		break;
	}

}