// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.h"
#include "Ultilities.h"
#include "Input.h"
// ---------------------------------------------------------------------------

extern frogPos frog;
extern mousePos mouse;


// ----------------------------------------------------------------------------
// This function makes the player jump on spacebar press
// It is called whenever spacebar is being triggered
// ----------------------------------------------------------------------------
void Input_Handle_Space() 
{
	std::cout << "Input:Handle Spacebar Triggered\n";

	frog.velY = e_jumpForce;
	frog.velX = e_jumpForce;
	frog.Y += frog.velY * AEFrameRateControllerGetFrameTime();
	frog.X += frog.velX * AEFrameRateControllerGetFrameTime();
	frog.onFloor = false;
	
}

// ----------------------------------------------------------------------------
// This function decreases the jump velocity if mouse click is held 
// It is called whenever mouse click is held and player is on the ground
// ----------------------------------------------------------------------------
void Input_Handle_HoldCheck()
{	
	std::cout << "Input:Mouse Click Held\n";

	// Holding too long will make it jump shorter (Aiming)
	if (e_jumpForce > 100) {
		std::cout << e_jumpForce << "\n";
		e_jumpForce -= 200 * AEFrameRateControllerGetFrameTime();
	}
}

// ----------------------------------------------------------------------------
// This function makes tge player jump on mouse click release 
// It is called whenever mouse click released and player is on the ground
// ----------------------------------------------------------------------------
void Input_Handle_Jump() {

	std::cout << "Input:Mouse Click Released\n";

	vector nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
	frog.velY = e_jumpForce * nDirection.Y;
	frog.velX = e_jumpForce * nDirection.X;
	frog.Y += frog.velY * AEFrameRateControllerGetFrameTime();
	frog.X += frog.velX * AEFrameRateControllerGetFrameTime();
	frog.onFloor = false;
	e_jumpForce = 200;

}