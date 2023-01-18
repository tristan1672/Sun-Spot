// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.h"
#include "Ultilities.h"
#include "System.h"
#include "GameStateManager.h"
#include "Input.h"
// ---------------------------------------------------------------------------

frogPos frog;
mousePos mouse;
vector Direction;

// ----------------------------------------------------------------------------
// This function is the main function that runs the program
// It is called once at the start of the program
// ----------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //Initialize the system
    AESysInit(hInstance, nCmdShow, 1270, 720, 1, 60, true, NULL); // trynna shift into System_Initialize()
    System_Initialize(); 


    //Initialize the gamestate manager
    GSM_Initialize(GS_LEVEL1);

    while (current != GS_QUIT)
    {
        if (current != GS_RESTART) {
            GSM_Update(); //Initialize the gamestate function pointers
            e_fpLoad(); // Loads gamestate
        }
        else {
            next = previous; // set next gamestate to previous gamestate
            current = previous; // set current gamestate to previous gamestate
        }

        e_fpInitialize(); // Initialize gamestate

        //The game loop
        while (next == current)
        {   
            // If on floor, movement allowed
            // Spacebar
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

            e_fpUpdate(); // Update current gamestate
            e_fpDraw(); // Render current gamestate
        }

        e_fpFree(); // Free current gamestate

        if (next != GS_RESTART) {
            e_fpUnload(); //Unloads current gamestate
        }

        previous = current;
        current = next;

    }

    //Systems Exit (terminate)
    System_Exit();
    return 0;
}
