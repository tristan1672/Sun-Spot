/*
  *  \file Physics.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\\digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  Defination file, for  DynamicObj::PhysicsUpdate() in GameObjClass.hpp
  *
  *  -PhysicsUpdate()
  *		Part of DynamicObj, updates the physics of DynamicObjs based on which platforms they are interacting with
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
*/
#include "Physics.hpp"
void DynamicObj::PhysicsUpdate() {
	/*
	Description for each playform type

	NORMAL_BLOCK: No special property, makes the player stop moving regardless of collision flag
	ICE_BLOCK: Slides the player with minimal loss of energy
	STICKY_BLOCK: Slows down player with bottom collision, slows down fall with left or right collision, player will be able to jump while on the sides
	SLIME_BLOCK: bounces player, will redirect player up if player collides with sides
	*/
	if (collisionFlag & COLLISION_TOP) { // checks if the obj collides the top
		velocity.y -= velocity.y; // inverts the y velocity
	}
	if (collisionFlag & COLLISION_BOTTOM) {// checks if the obj collides on the bottom
		//checks if the the center of the player is closer to left or right
		if (position.x < (platform[static_cast<int>(btmY)][static_cast<int>(X1)].position.x + (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetScale().x / 2.f))) { // checks which side of the grid the player is cooupying more

			switch (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetPlatformType())
			{
			case NORMAL_BLOCK:// normal surface
				velocity.y -= velocity.y;
				friction = NORMAL_FRICTION;
				shake = true;
				break;
			case ICE_BLOCK: // ice physics
				velocity.y -= velocity.y;
				friction = ICE_FRICTION;
				jumpReady = true;
				break;
			case STICKY_BLOCK:// sticky physics
				velocity.y -= velocity.y;
				friction = FULL_STOP_FRICTION;
				e_jumpForceMod = 0.7f;
				shake = true;
				break;
			case SLIME_BLOCK:// bouncy physics
				if (abs(velocity.y) <= 2) velocity.y = 0;
				velocity.y = -(velocity.y * 0.9f);
				friction = SLIME_FRICTION;
				jumpReady = true;
				break;
			default:
				break;
			}
		}
		else if (position.x > (platform[static_cast<int>(btmY)][static_cast<int>(X1)].position.x - (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetScale().x / 2.f))) {
			switch (platform[static_cast<int>(btmY)][static_cast<int>(X2)].GetPlatformType())
			{
			case NORMAL_BLOCK:// normal surface
				velocity.y -= velocity.y;
				friction = NORMAL_FRICTION;
				if (abs(velocity.x) < 2.f) {
					velocity.x = 0;
				}
				jumpReady = true;
				break;
			case ICE_BLOCK:// ice physics
				velocity.y -= velocity.y;
				friction = ICE_FRICTION;
				jumpReady = true;
				break;
			case STICKY_BLOCK:// sticky physics
				velocity.y -= velocity.y;
				friction = FULL_STOP_FRICTION;
				e_jumpForceMod = 0.7f;
				break;
			case SLIME_BLOCK:// bouncy physics
				if (abs(velocity.y) <= 2) velocity.y = 0;
				velocity.y = -(velocity.y * 0.7f);
				friction = SLIME_FRICTION;
				break;
			default:
				break;
			}
		}
		if (!velocity.x) {
			jumpReady = true;
		}
	}
	if (collisionFlag & COLLISION_RIGHT) {// checks if the obj collides on the right
		if (position.y < (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].position.y + (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
			position.y >(platform[static_cast<int>(Y1)][static_cast<int>(rightX)].position.y - (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetScale().y / 2.f))) {
			switch (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetPlatformType())
			{
			case STICKY_BLOCK:// sticky physics
				dragCoeff = STICK_DRAG;
				friction = FULL_STOP_FRICTION;
				jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					velocity.x = -velocity.x;
					velocity.y = static_cast<float>((e_jumpForce / 0.8) * direction.y);
				}
				break;
			default:
				dragCoeff = NORMAL_DRAG;
				friction = FULL_STOP_FRICTION;
				break;
			}
		}
		 else if (platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType() < GOAL) {
			switch (platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType())
			{
			case STICKY_BLOCK:// sticky physics
				dragCoeff = STICK_DRAG;
				friction = FULL_STOP_FRICTION;
				jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					velocity.x = -velocity.x;
					velocity.y = static_cast<float>((e_jumpForce / 0.8) * direction.y);
				}
				break;
			default:
				dragCoeff = NORMAL_DRAG;
				friction = FULL_STOP_FRICTION;
				break;
			}
		}
	}
	if (collisionFlag & COLLISION_LEFT) {// checks if the obj collides on the left
		if (position.y < (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].position.y + (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
			position.y >(platform[static_cast<int>(Y1)][static_cast<int>(leftX)].position.y - (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetScale().y / 2.f))) {
			switch (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetPlatformType())
			{

			case STICKY_BLOCK:// sticky physics
				dragCoeff = STICK_DRAG;
				friction = FULL_STOP_FRICTION;
				jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					velocity.y = static_cast<float>((e_jumpForce/0.8) * direction.y);
					velocity.x = -velocity.x;
				}
				break;
			default:
				dragCoeff = NORMAL_DRAG;
				friction = FULL_STOP_FRICTION;
				break;
			}
		}
		 else if (platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType() < GOAL) {
			switch (platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType())
			{
			case STICKY_BLOCK:// sticky physics
				friction = FULL_STOP_FRICTION;
				dragCoeff = STICK_DRAG;
				jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					velocity.y = static_cast<float>((e_jumpForce / 0.8) * direction.y);
					velocity.x = -velocity.x;
				}
				break;
			default:
				dragCoeff = NORMAL_DRAG;
				friction = FULL_STOP_FRICTION;
				break;
			}
		}
	}
	if (!collisionFlag) {// for when they are not colliding with anything
		dragCoeff = AIR_DRAG;
		friction = 0.f;
	}
	float terminalVelocity{ 1.5f * e_gravity / dragCoeff };// ternimal velcity
	if (terminalVelocity < velocity.y) {// limits y velocity based on terminal velocity
		velocity.y += static_cast<float>(vertMod * e_gravity * e_deltaTime);
	}
	if (velocity.y) {// reduce the velocity based on drag
		velocity.y -= static_cast<float>(dragCoeff * velocity.y * e_deltaTime);
	}
	if (abs(velocity.x) < 2.f) {// makes velocity x not need to take forevery to get to 0
		velocity.x = 0;
	}
	if (velocity.x && friction != FULL_STOP_FRICTION) {// if the friction is not the fully stopping the player
		velocity.x -= static_cast<float>(friction * velocity.x * e_deltaTime);//velocity x will be reduced based on friction
	}
	else if (velocity.x && friction == FULL_STOP_FRICTION) {// if the friction is fully stopping the player
		velocity.x -= static_cast<float>(velocity.x);// stops the player fully on the x axis
	}
	// increase the player position 
	position.y += static_cast<float>(velocity.y * e_deltaTime);
	position.x += static_cast<float>(velocity.x * e_deltaTime);
}