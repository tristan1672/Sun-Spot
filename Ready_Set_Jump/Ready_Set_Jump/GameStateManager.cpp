// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "GameStateManager.hpp"
#include "Ultilities.hpp"
#include "Level.hpp"
#include "MainMenu.hpp"
#include "SaveManager.hpp"
#include "SplashScreen.hpp"
#include "Credits.hpp"
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
	e_fontID = AEGfxCreateFont("Assets/Font/kongtext.ttf", FONT_SIZE);
	std::cout << "GSM:Initialize\n";
	Save::ReadFile();
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
		break;

	default:
		break;
	}

}