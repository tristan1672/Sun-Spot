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
extern GameObject jumpArrow;
// ----------------------------------------------------------------------------
// This function updates the initial mouse click position
// ----------------------------------------------------------------------------
void Input_Update_Mouse_Pos() {
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
}

// ----------------------------------------------------------------------------
// This Function initiates the aim mode
// ----------------------------------------------------------------------------
void Input_Handle_HoldCheck()
{

	// Holding too long will initiate aim mode
	if (currHoldTime < maxHoldTime) {
		currHoldTime += e_deltaTime;
	}
	AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
	Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ReleaseX) - WINDOW_WIDTH / 2.f + Player.position.x, -(static_cast<float>(mouse.ReleaseY) - WINDOW_HEIGHT / 2.f) + Player.position.y };
	Vector2D nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
	float angle = atan2f(-nDirection.x, nDirection.y);
	if (currHoldTime >= maxHoldTime) {
		jumpArrow.position = { Player.position.x,Player.position.y };
		nDirection = normalDirection(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		angle = atan2f(-nDirection.x, -nDirection.y);
		currHoldDistance = Distance(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		if (currHoldDistance > maxHoldDistance) {
			currHoldDistance = maxHoldDistance;
		}
		if (currHoldDistance < minHoldDistance) {
			currHoldDistance = minHoldDistance;
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
	
	if (currHoldTime >= maxHoldTime) {
		Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ReleaseX) - WINDOW_WIDTH / 2.f + Player.position.x, -(static_cast<float>(mouse.ReleaseY) - WINDOW_HEIGHT / 2.f) + Player.position.y };
		Player.direction = normalDirection(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
		Player.e_jumpForce = Distance(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y) * 2;
		if (Player.e_jumpForce > max_jumpForce) {
			Player.e_jumpForce = max_jumpForce;
		}
		if (Player.e_jumpForce < min_jumpForce) {
			Player.e_jumpForce = min_jumpForce;
		}
		Player.e_jumpForce *= Player.e_jumpForceMod;
		Player.velocity.y += static_cast<float>(Player.e_jumpForce * -Player.direction.y);
		Player.velocity.x += static_cast<float>(Player.e_jumpForce * Player.direction.x);
	}
	else
	{
		Player.direction = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
		Player.e_jumpForce = Distance(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY) * 1.5;
		if (Player.e_jumpForce > max_jumpForce) {
			Player.e_jumpForce = max_jumpForce;
		}
		if (Player.e_jumpForce < min_jumpForce) {
			Player.e_jumpForce = min_jumpForce;
		}
		Player.e_jumpForce *= Player.e_jumpForceMod;
		Player.velocity.y += static_cast<float>(Player.e_jumpForce * Player.direction.y);
		Player.velocity.x += static_cast<float>(Player.e_jumpForce * Player.direction.x);
	}
	Player.position.y += static_cast<float>(Player.velocity.y * e_deltaTime);
	Player.position.x += static_cast<float>(Player.velocity.x * e_deltaTime);
	Player.jumpReady = false;
	currHoldTime = 0.f;
	Player.e_jumpForceMod = originalJumpForceMod;
#if DEBUG
	std::cout << "Jump Force: " << e_jumpForce << "\n";
#endif

}