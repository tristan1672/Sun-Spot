#include "Physics.hpp"
void DynamicObj::PhysicsUpdate() {
	currFrameStickyCollision = false;
	if (collisionFlag & COLLISION_TOP) {
		velocity.y -= velocity.y;
	}
	if (collisionFlag & COLLISION_BOTTOM) {
		if (position.x < (platform[btmY][X1].position.x + (platform[btmY][X1].GetScale().x / 2.f))) { // checks which side of the grid the player is cooupying more

			switch (platform[btmY][X1].GetPlatformType())
			{
			case NORMAL_BLOCK:// normal surface
				velocity.y -= velocity.y;
				friction = NORMAL_FRICTION;
				jumpReady = true;
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
			case SLIME_BLOCK:
				if (abs(velocity.y) <= 2) velocity.y = 0;
				velocity.y = -(velocity.y * 0.5f);
				friction = SLIME_FRICTION;
				break;
			default:
				break;
			}
		}
		else if (position.x > (platform[btmY][X1].position.x - (platform[btmY][X1].GetScale().x / 2.f))) {
			switch (platform[btmY][X2].GetPlatformType())
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
			case SLIME_BLOCK:
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
	if (collisionFlag & COLLISION_RIGHT) {
		if (position.y < (platform[Y1][rightX].position.y + (platform[Y1][rightX].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
			position.y >(platform[Y1][rightX].position.y - (platform[Y1][rightX].GetScale().y / 2.f))) {
			switch (platform[Y1][rightX].GetPlatformType())
			{
			case STICKY_BLOCK:// sticky physics
				dragCoeff = STICK_DRAG;
				friction = FULL_STOP_FRICTION;
				currFrameStickyCollision = true;
				if (!prevFrameStickyCollision)jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					//velocity.y = static_cast<float>(e_jumpForce * direction.y);
					velocity.x = -velocity.x;
				}
				break;
			default:
				dragCoeff = NORMAL_DRAG;
				friction = FULL_STOP_FRICTION;
				break;
			}
		}
		else if (platform[Y2][rightX].GetPlatformType() > EMPTY_SPACE && platform[Y2][rightX].GetPlatformType() < GOAL) {
			switch (platform[Y2][rightX].GetPlatformType())
			{
			case STICKY_BLOCK:// sticky physics
				dragCoeff = STICK_DRAG;
				friction = FULL_STOP_FRICTION;
				currFrameStickyCollision = true;
				if (!prevFrameStickyCollision)jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					//velocity.y = static_cast<float>(e_jumpForce * direction.y); 
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
	if (collisionFlag & COLLISION_LEFT) {
		if (position.y < (platform[Y1][leftX].position.y + (platform[Y1][leftX].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
			position.y >(platform[Y1][leftX].position.y - (platform[Y1][leftX].GetScale().y / 2.f))) {
			switch (platform[Y1][leftX].GetPlatformType())
			{

			case STICKY_BLOCK:// sticky physics
				dragCoeff = STICK_DRAG;
				friction = FULL_STOP_FRICTION;
				currFrameStickyCollision = true;
				if (!prevFrameStickyCollision)jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					//velocity.y = static_cast<float>(e_jumpForce * direction.y);
					velocity.x = -velocity.x;
				}
				break;
			default:
				dragCoeff = NORMAL_DRAG;
				friction = FULL_STOP_FRICTION;
				break;
			}
		}
		else if (platform[Y2][leftX].GetPlatformType() > EMPTY_SPACE && platform[Y2][leftX].GetPlatformType() < GOAL) {
			switch (platform[Y2][leftX].GetPlatformType())
			{
			case STICKY_BLOCK:// sticky physics
				friction = FULL_STOP_FRICTION;
				dragCoeff = STICK_DRAG;
				currFrameStickyCollision = true;
				if (!prevFrameStickyCollision)jumpReady = true;
				break;
			case SLIME_BLOCK:
				if (velocity.x) {
					//velocity.y = static_cast<float>(e_jumpForce * direction.y);
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
	if (!collisionFlag) {
		dragCoeff = AIR_DRAG;
		friction = 0.f;
	}
	float terminalVelocity{ 2.f * e_gravity / dragCoeff };
	if (terminalVelocity < velocity.y) {
		velocity.y += static_cast<float>(vertMod * e_gravity * e_deltaTime);
	}
	if (velocity.y) {
		velocity.y -= static_cast<float>(dragCoeff * velocity.y * e_deltaTime);
	}
	if (abs(velocity.x) < 2.f) {
		velocity.x = 0;
	}
	if (velocity.x && friction != FULL_STOP_FRICTION) {
		velocity.x -= static_cast<float>(friction * velocity.x * e_deltaTime);
	}
	else if (velocity.x && friction == FULL_STOP_FRICTION) {
		velocity.x -= static_cast<float>(velocity.x);
	}

	position.y += static_cast<float>(velocity.y * e_deltaTime);
	position.x += static_cast<float>(velocity.x * e_deltaTime);

	prevFrameStickyCollision = currFrameStickyCollision;
}