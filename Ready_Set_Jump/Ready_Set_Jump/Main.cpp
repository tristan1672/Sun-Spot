/*****************************************************************
  *  \file Timer.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  * Main function that runs the program.
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include <iostream>
#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "System.hpp"
#include "GameStateManager.hpp"
#include "Input.hpp"
#include "Timer.hpp"

s8 e_fontID, e_creditFontID;

// ----------------------------------------------------------------------------
// This function is the main function that runs the program
// It is called once at the start of the program
// ----------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    #if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    //Initialize the system
    // The param after WINDOW_HEIGHT to 0 if dw console
    AESysInit(hInstance, nCmdShow, WINDOW_WIDTH, WINDOW_HEIGHT, 1, 60, true, NULL);
    System_Initialize(); 
    
    e_fontID = AEGfxCreateFont("Assets/Font/kongtext.ttf", FONT_SIZE);
    e_creditFontID = AEGfxCreateFont("Assets/Font/Connection-arMJ.otf", CREDIT_FONT_SIZE);

    //Initialize the gamestate manager
    GSM_Initialize(GS_SPLASH);

    while (e_current_state != GS_QUIT)
    {
        if (e_current_state != GS_RESTART) {
            GSM_Update(); //Initialize the gamestate function pointers
            e_fpLoad(); // Loads gamestate
        }
        else {
            e_next_state = e_previous_state; // set next gamestate to previous gamestate
            e_current_state = e_previous_state; // set current gamestate to previous gamestate
        }

        e_fpInitialize(); // Initialize gamestate

        //The game loop
        while (e_next_state == e_current_state)
        {   
            AESysFrameStart();
            AEInputUpdate();

            GetTime(); // Gets delta time
            e_fpUpdate(); // Update current gamestate
            e_fpDraw(); // Render current gamestate

            AESysFrameEnd();

            if ((AESysDoesWindowExist() == false))
                e_next_state = GS_QUIT;
        }

        e_fpFree(); // Free current gamestate

        if (e_next_state != GS_RESTART) {
            e_fpUnload(); //Unloads current gamestate
        }

        e_previous_state = e_current_state;
        e_current_state = e_next_state;

    }

    //Systems Exit (terminate)
    System_Exit();

    return 0;
}
