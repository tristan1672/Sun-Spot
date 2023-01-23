// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "Ultilities.hpp"
#include "Input.hpp"
#include "GameObjClasses.hpp"
// ---------------------------------------------------------------------------


extern mousePos mouse;
extern DynamicObj Player;

// ----------------------------------------------------------------------------
// This function decreases the jump velocity if mouse click is held 
// It is called whenever mouse click is held and player is on the ground
// ----------------------------------------------------------------------------
void Input_Handle_HoldCheck()
{	

	// Holding too long will make it jump shorter (Aiming)
	if (e_jumpForce > 100) {
		//std::cout << e_jumpForce << "\n";
		e_jumpForce -= static_cast<float>(200 * AEFrameRateControllerGetFrameTime());
	}
	if (e_jumpForce <= 100) {
		e_jumpForce = 100;
	}
}

// ----------------------------------------------------------------------------
// This function makes tge player jump on mouse click release 
// It is called whenever mouse click released and player is on the ground
// ----------------------------------------------------------------------------
void Input_Handle_Jump() {

	//std::cout << "Input:Mouse Click Released\n";

	Vector2D nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
	Player.velocity.y = static_cast<float>(e_jumpForce * nDirection.y);
	Player.velocity.x = static_cast<float>(e_jumpForce * nDirection.x);
	Player.position.y += static_cast<float>(Player.velocity.y * AEFrameRateControllerGetFrameTime());
	Player.position.x += static_cast<float>(Player.velocity.x * AEFrameRateControllerGetFrameTime());
	Player.collideBotton = false;
	e_jumpForce = 200;

}