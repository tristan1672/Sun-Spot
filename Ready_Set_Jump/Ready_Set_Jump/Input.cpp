/**
  *  \file Input.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\\digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  This is the input action that the player need to take to move the character in game, the main movment is to use flicking of mosue to sling shot 
  *  player characters to their destinations
  * 
  * -Input_Handle_HoldCheck()
  *		Checks if left mouse button is held for a certain time frame, if past that time, a guide arrow will show up
  * -Input_Handle_Jump()
  *		
  *
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
*/
// ---------------------------------------------------------------------------
// includes
#include <iostream>

#include "AEEngine.h"
#include "PreCompiledHeader.hpp"
#include "Utilities.hpp"
#include "Input.hpp"
#include "Cam.hpp"
#include "GameObjClasses.hpp"
// ---------------------------------------------------------------------------


extern mousePos mouse;
extern DynamicObj Player;
extern GameObject jumpArrow;
extern CameraPos cam;

// ----------------------------------------------------------------------------
// This Function initiates the aim mode
// ----------------------------------------------------------------------------
void Input_Handle_HoldCheck()
{

	// Holding too long will initiate aim mode
	if (currHoldTime < MAX_HOLD_TIME) {
		currHoldTime += e_deltaTime;
	}
	AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
	// converts mouse position to world space
	Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ReleaseX) - HALVE_WINDOW_WIDTH + cam.X, -(static_cast<float>(mouse.ReleaseY) - HALVE_WINDOW_HEIGHT) + cam.Y };
	//normalize direction between player and mouse
	Vector2D nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
	// sets the angle of arrow
	float angle = atan2f(-nDirection.x, nDirection.y);
	if (currHoldTime >= MAX_HOLD_TIME) {// shows arrow if hold time is more than MAX_HOLD_TIME
		//sets arrow pos to player
		jumpArrow.position = { Player.position.x,Player.position.y };
		// sets the direction based on player pos and mouse pos
		nDirection = normalDirection(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		// sets the angle of arrow
		angle = atan2f(-nDirection.x, nDirection.y);
		// gets the distance between player and mouse
		currHoldDistance = Distance(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		// clamps the jumpforce
		if (currHoldDistance > MAX_HOLD_DISTANCE) {
			currHoldDistance = MAX_HOLD_DISTANCE;
		}
		if (currHoldDistance < MIN_HOLD_DISTANCE) {
			currHoldDistance = MIN_HOLD_DISTANCE;
		}
		currHoldDistance *= Player.e_jumpForceMod;
		jumpArrow.SetScale({ jumpArrow.GetScale().x,currHoldDistance });
		jumpArrow.SetRotation(angle);
	}
}

// ----------------------------------------------------------------------------
// This function makes tge player jump on mouse click release 
// It is called whenever mouse click released and player is on the ground
// ----------------------------------------------------------------------------
void Input_Handle_Jump() {
	
	if (currHoldTime >= MAX_HOLD_TIME) {
		// converts mouse position to world space
		Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ReleaseX) - HALVE_WINDOW_WIDTH + cam.X, -(static_cast<float>(mouse.ReleaseY) - HALVE_WINDOW_HEIGHT) + cam.Y };
		// normalize direction between player and mouse
		Player.direction = normalDirection(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		// scale the player's jump force base on how far the player drag their mouse away from player charatcer
		Player.e_jumpForce = Distance(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y) * 3;
		// clamps the jumpforce
		if (Player.e_jumpForce > MAX_JUMP_FORCE) {
			Player.e_jumpForce = MAX_JUMP_FORCE;
		}
		if (Player.e_jumpForce < MIN_JUMP_FORCE) {
			Player.e_jumpForce = MIN_JUMP_FORCE;
		}
		// scales player jump force based on its modification
		Player.e_jumpForce *= Player.e_jumpForceMod;

		Player.velocity.y += static_cast<float>(Player.e_jumpForce * Player.direction.y);
		Player.velocity.x += static_cast<float>(Player.e_jumpForce * Player.direction.x);
		// makes sure the player will not be able to jump towrds the wall
		if (Player.GetColFlag() & COLLISION_RIGHT && Player.velocity.x > 0) {
			Player.velocity.y -= static_cast<float>(Player.e_jumpForce * Player.direction.y);
		}
		if (Player.GetColFlag() & COLLISION_LEFT && Player.velocity.x < 0)  {
			Player.velocity.y -= static_cast<float>(Player.e_jumpForce * Player.direction.y);
		}
	}
	else
	{
		// normalize direction between mouse click and mouse release
		Player.direction = normalDirection(mouse.ClickX,- mouse.ClickY, mouse.ReleaseX,- mouse.ReleaseY);
		// scale the player's jump force base on how far the player drag their mouse away from player charatcer
		Player.e_jumpForce = Distance(mouse.ClickX,- mouse.ClickY, mouse.ReleaseX,- mouse.ReleaseY) * 3;
		// clamps the jumpforce
		if (Player.e_jumpForce > MAX_JUMP_FORCE) {
			Player.e_jumpForce = MAX_JUMP_FORCE;
		}
		if (Player.e_jumpForce < MIN_JUMP_FORCE) {
			Player.e_jumpForce = MIN_JUMP_FORCE;
		}
		// scales player jump force based on its modification
		Player.e_jumpForce *= Player.e_jumpForceMod;
		Player.velocity.y += static_cast<float>(Player.e_jumpForce * Player.direction.y);
		Player.velocity.x += static_cast<float>(Player.e_jumpForce * Player.direction.x);
		// makes sure the player will not be able to jump towrds the wall
		if (Player.GetColFlag() & COLLISION_RIGHT && Player.velocity.x > 0) {
			Player.velocity.y -= static_cast<float>(Player.e_jumpForce * Player.direction.y);
		}
		if (Player.GetColFlag() & COLLISION_LEFT && Player.velocity.x < 0) {
			Player.velocity.y -= static_cast<float>(Player.e_jumpForce * Player.direction.y);
		}
	}
	Player.position.y += static_cast<float>(Player.velocity.y * e_deltaTime);
	Player.position.x += static_cast<float>(Player.velocity.x * e_deltaTime);
	Player.jumpReady = false;// makes sure players dont jump again mid air
	currHoldTime = 0.f;
	Player.e_jumpForceMod = ORIGINAL_JUMP_FORCE_MOD;
#if DEBUG
	std::cout << "Jump Force: " << ORIGINAL_JUMP_FORCE_MOD << "\n";
#endif

}