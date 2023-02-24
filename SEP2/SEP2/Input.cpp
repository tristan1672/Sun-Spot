/**
  *  \file Input.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  This is the input action that the player need to take to move the character in game, the main movment is to use flicking of mosue to sling shot 
  * player characters to their destinations
  *
*/
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
	if (currHoldTime < maxHoldTime) {
		currHoldTime += e_deltaTime;
	}
}

// ----------------------------------------------------------------------------
// This function makes tge player jump on mouse click release 
// It is called whenever mouse click released and player is on the ground
// ----------------------------------------------------------------------------
void Input_Handle_Jump() {

	//std::cout << "Input:Mouse Click Released\n";
	Vector2D nDirection{ normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY) };
	Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ReleaseX) - WINDOW_WIDTH / 2.f + Player.position.x, -(static_cast<float>(mouse.ReleaseY) - WINDOW_HEIGHT / 2.f) + Player.position.y };
	Player.velocity.y = static_cast<float>(e_jumpForce * nDirection.y);
	Player.velocity.x = static_cast<float>(e_jumpForce * nDirection.x);
	
	if (currHoldTime >= maxHoldTime) {
		nDirection = normalDirection(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		Player.velocity.y = static_cast<float>(e_jumpForce * -nDirection.y);
		Player.velocity.x = static_cast<float>(e_jumpForce * nDirection.x);
	}

	Player.position.y += static_cast<float>(Player.velocity.y * e_deltaTime);
	Player.position.x += static_cast<float>(Player.velocity.x * e_deltaTime);
	Player.jumpReady = false;
	e_jumpForce = original_jumpForce;
	min_jumpForce = originalMin_jumpForce;
	currHoldTime = 0.f;

}