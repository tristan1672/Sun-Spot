/*
  *  \file Collision.cpp
  *  \author      : Peh Zong Lin Adrian
  *  \par DP Email: p.zonglinadrian\@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *  Collision component.
  *  - LevelCollision
  *		 Checks for player collision against level and snap accordingly.
  *  - ObjectiveCollision
  *		 Checks for player collision against objects that dont require have seperate width and height.
  *
*/

// ---------------------------------------------------------------------------
// Includes
#include "Collision.hpp"
#include "Timer.hpp"
#include <iostream>
#include <fstream>
// --------------------------------------------------------------------------- // End of includes

// ---------------------------------------------------------------------------
// External Variables
DynamicObj Player;
Platform** platform;
int e_collisionFlag;
int e_numOfCollectableCollected;
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------
// Const Variables
const int	COLLISION_LEFT   = 0x00000001;	//0001
const int	COLLISION_RIGHT  = 0x00000002;	//0010
const int	COLLISION_TOP    = 0x00000004;	//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000
// --------------------------------------------------------------------------- // End of external variables
bool prevFrameStickyCollision{};
bool currFrameStickyCollision{};


// ----------------------------------------------------------------------------
// Checks for player collision against level and snap accordingly
// ----------------------------------------------------------------------------
void LevelCollision() {
	
	// Will be a static value once there are grids outside of the window
	float gridWidth = WINDOW_WIDTH / e_binaryMapWidth;
	float gridHeight = WINDOW_HEIGHT / e_binaryMapHeight;
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;

	e_collisionFlag = 0;
	currFrameStickyCollision = false;
	bool colliding{};

	// "Normalizing" hotspots
	int topY = (heightOffset - Player.position.y - Player.GetScale().y / 2.0f) / gridHeight; // Top bound
	int btmY = (heightOffset - Player.position.y + Player.GetScale().y / 2.0f) / gridHeight; // Btm bound
	int leftX = (widthOffset + Player.position.x - Player.GetScale().x / 2.0f) / gridWidth; // Left bound
	int rightX = (widthOffset + Player.position.x + Player.GetScale().x / 2.0f) / gridWidth; // Right bound

	int X1 = (widthOffset + Player.position.x - Player.GetScale().x / 4.0f) / gridWidth; // 25% X
	int X2 = (widthOffset + Player.position.x + Player.GetScale().x / 4.0f) / gridWidth; // 75% X
	int Y1 = (heightOffset - Player.position.y - Player.GetScale().y / 4.0f) / gridHeight; // 25% Y
	int Y2 = (heightOffset - Player.position.y + Player.GetScale().y / 4.0f) / gridHeight; // 75% Y

	// If out of play area // This not running cause the 1 in level 1 running
	if (leftX < 0 || rightX > e_binaryMapWidth-1 || topY < 0 || btmY > e_binaryMapHeight-1) {
		Player.velocity.x = 0.0f;
		Player.velocity.y = 0.0f;
		Player.jumpReady = true;
		Player.position = { e_playerSpawnPointX,e_playerSpawnPointY };

	}
	else {
		// Top collided
		if (platform[topY][X1].GetPlatformType() > EMPTY_SPACE && platform[topY][X1].GetPlatformType() < GOAL
			|| platform[topY][X2].GetPlatformType() > EMPTY_SPACE && platform[topY][X2].GetPlatformType() < GOAL) {
			colliding = true;
			e_collisionFlag += COLLISION_TOP;
			Player.velocity.y -= Player.velocity.y;

#if DEBUG
				std::cout << "Top collided, Coordinates\n\n";
				std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
				std::cout << "        +\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
				std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
#endif
		}

		// Btm collided
		if (platform[btmY][X1].GetPlatformType() > EMPTY_SPACE && platform[btmY][X1].GetPlatformType() < GOAL
			|| platform[btmY][X2].GetPlatformType() > EMPTY_SPACE && platform[btmY][X2].GetPlatformType() < GOAL) {
			colliding = true;
			e_collisionFlag += COLLISION_BOTTOM;
			if (Player.position.x < (platform[btmY][X1].position.x + (platform[btmY][X1].GetScale().x / 2.f))) { // checks which side of the grid the player is cooupying more

				switch (platform[btmY][X1].GetPlatformType())
				{
				case NORMAL_BLOCK:// normal surface
					Player.velocity.y -= Player.velocity.y;
					friction = normalFriction;
					shake = true;
					break;
				case ICE_BLOCK: // ice physics
					Player.velocity.y -= Player.velocity.y;
					friction = iceFriction;
					break;
				case STICKY_BLOCK:// sticky physics
					Player.velocity.y -= Player.velocity.y;
					friction = fullStopFriction;
					e_jumpForceMod = 0.7f;
					shake = true;
					break;
				case SLIME_BLOCK:
					if (abs(Player.velocity.y) <= 2) Player.velocity.y = 0;
					Player.velocity.y = -(Player.velocity.y * 0.5f);
					friction = slimeFriction;
					break;
				default:
					break;
				}
			}
			else if (Player.position.x > (platform[btmY][X1].position.x - (platform[btmY][X1].GetScale().x / 2.f))) {
				switch (platform[btmY][X2].GetPlatformType())
				{
				case NORMAL_BLOCK:// normal surface
					Player.velocity.y -= Player.velocity.y;
					friction = normalFriction;
					if (abs(Player.velocity.x) < 2.f) {
						Player.velocity.x = 0;
					}
					break;
				case ICE_BLOCK:// ice physics
					Player.velocity.y -= Player.velocity.y;
					friction = iceFriction;
					break;
				case STICKY_BLOCK:// sticky physics
					Player.velocity.y -= Player.velocity.y;
					friction = fullStopFriction;
					e_jumpForceMod = 0.7f;
					break;
				case SLIME_BLOCK:
					if (abs(Player.velocity.y) <= 2) Player.velocity.y = 0;
					Player.velocity.y = -(Player.velocity.y * 0.7f);
					friction = slimeFriction;
					break;
				default:
					break;
				}
			}

#if DEBUG		
			if (Player.jumpReady == false) {
			std::cout << "Btm collided, Coordinates\n";
			std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
			std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
			std::cout << "        +\n";
			std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
			std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
			}
#endif
			if (!Player.velocity.x) {
				Player.jumpReady = true;
			}
		}

		// Right collided
		if (platform[Y1][rightX].GetPlatformType() > EMPTY_SPACE && platform[Y1][rightX].GetPlatformType() < GOAL) {
			colliding = true;
			e_collisionFlag += COLLISION_RIGHT;
			if (Player.position.y < (platform[Y1][rightX].position.y + (platform[Y1][rightX].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
				Player.position.y >(platform[Y1][rightX].position.y - (platform[Y1][rightX].GetScale().y / 2.f))) {
				switch (platform[Y1][rightX].GetPlatformType())
				{
				case STICKY_BLOCK:// sticky physics
					dragCoeff = stickDrag;
					friction = fullStopFriction;
					currFrameStickyCollision = true;
					if(!prevFrameStickyCollision)Player.jumpReady = true;
					break;
				case EMPTY_SPACE:
					colliding = false;
					break;
				case SLIME_BLOCK:
					if (Player.velocity.x) {
						//Player.velocity.y = static_cast<float>(e_jumpForce * Player.direction.y);
						Player.velocity.x = -Player.velocity.x;
					}
					break;
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					break;
				}
			}
			else if(platform[Y2][rightX].GetPlatformType() > EMPTY_SPACE && platform[Y2][rightX].GetPlatformType() < GOAL) {
				switch (platform[Y2][rightX].GetPlatformType())
				{
				case STICKY_BLOCK:// sticky physics
					dragCoeff = stickDrag;
					friction = fullStopFriction;
					currFrameStickyCollision = true;
					if (!prevFrameStickyCollision)Player.jumpReady = true;
					break;
				case EMPTY_SPACE:
					colliding = false;
					break;
				case SLIME_BLOCK:
					if (Player.velocity.x) {
						//Player.velocity.y = static_cast<float>(e_jumpForce * Player.direction.y); 
						Player.velocity.x = -Player.velocity.x;
					}
					break;
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					break;
				}
			}
#if DEBUG
				std::cout << "Right collided, Coordinates\n";
				std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
				std::cout << "        +\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
				std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
#endif
		}

		// Left collided
		if (platform[Y1][leftX].GetPlatformType() > EMPTY_SPACE && platform[Y1][leftX].GetPlatformType() < GOAL) {
			colliding = true;
			e_collisionFlag += COLLISION_LEFT;
			if (Player.position.y < (platform[Y1][leftX].position.y + (platform[Y1][leftX].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
				Player.position.y >(platform[Y1][leftX].position.y - (platform[Y1][leftX].GetScale().y / 2.f))) {
				switch (platform[Y1][leftX].GetPlatformType())
				{
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					break;
				case STICKY_BLOCK:// sticky physics
					dragCoeff = stickDrag;
					friction = fullStopFriction;
					currFrameStickyCollision = true;
					if (!prevFrameStickyCollision)Player.jumpReady = true;
					break;
				case SLIME_BLOCK:
					if (Player.velocity.x) {
						//Player.velocity.y = static_cast<float>(e_jumpForce * Player.direction.y);
						Player.velocity.x = -Player.velocity.x;
					}
					break;
				}
			}
			else if (platform[Y2][leftX].GetPlatformType() > EMPTY_SPACE && platform[Y2][leftX].GetPlatformType() < GOAL) {
				switch (platform[Y2][leftX].GetPlatformType())
				{
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					break;
				case STICKY_BLOCK:// sticky physics
					friction = fullStopFriction;
					dragCoeff = stickDrag;
					currFrameStickyCollision = true;
					if (!prevFrameStickyCollision)Player.jumpReady = true;
					break;
				case SLIME_BLOCK:
					if (Player.velocity.x) {
						//Player.velocity.y = static_cast<float>(e_jumpForce * Player.direction.y);
						Player.velocity.x = -Player.velocity.x;
					}
					else
					break;
				}
			}

#if DEBUG
				std::cout << "Left collided, Coordinates\n";
				std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
				std::cout << "        +\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
				std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
#endif
		}
		if (!colliding) {
			dragCoeff = airDrag;
			friction = 0.f;
		}
	}

	// Cam shake effect
	if (Player.velocity.y < -240.0f)
	{
		e_shakeStrength = HEAVY_SHAKE;
	}
	else if (Player.velocity.y < -90.0f)
	{
		e_shakeStrength = MEDIUM_SHAKE;
	}
	
	// Snapping
	if (e_collisionFlag == COLLISION_TOP) {
		Player.position.y = heightOffset - (topY+1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
	}
	if (e_collisionFlag == COLLISION_TOP + COLLISION_LEFT) {
		Player.position.y = heightOffset - (topY + 1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + (leftX + 0.9999) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_TOP + COLLISION_RIGHT) {
		Player.position.y = heightOffset - (topY + 1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_BOTTOM) {
		Player.position.y = heightOffset - btmY * gridHeight + (PLAYER_SIZE_Y / 2.0f);
	}
	if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_LEFT) {
		Player.position.y = heightOffset - btmY * gridHeight + (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + (leftX + 0.9999) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_RIGHT) {
		Player.position.y = heightOffset - btmY * gridHeight + (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_LEFT) {
		Player.position.x = -widthOffset + (leftX+0.9999) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_RIGHT) {
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	prevFrameStickyCollision = currFrameStickyCollision;
}

// ----------------------------------------------------------------------------
// Checks for player collision against objects that dont require have seperate width and height,
// such as collectables and goal(exit point)
// ----------------------------------------------------------------------------
void ObjectiveCollision() {
	// Will be a static value once there are grids outside of the window
	float gridWidth = WINDOW_WIDTH / e_binaryMapWidth;
	float gridHeight = WINDOW_HEIGHT / e_binaryMapHeight;

	// Offset used for grid position calculation, making calculation start from top left instead of center of window
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;

	// Player hotspots
	int playerTopY = Player.position.y - Player.GetScale().y / 2.0f; // Top bound
	int playerBtmY = Player.position.y + Player.GetScale().y / 2.0f; // Btm bound
	int playerLeftX = Player.position.x - Player.GetScale().x / 2.0f; // Left bound
	int playerRightX = Player.position.x + Player.GetScale().x / 2.0f; // Right bound

	int playerHsX1 = Player.position.x - Player.GetScale().x / 4.0f; // 25% X
	int playerHsX2 = Player.position.x + Player.GetScale().x / 4.0f; // 75% X
	int playerHsY1 = Player.position.y - Player.GetScale().y / 4.0f; // 25% Y
	int playerHsY2 = Player.position.y + Player.GetScale().y / 4.0f; // 75% Y

	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {

			if (platform[i][j].GetPlatformType() == GOAL) {
				float goalTopY = heightOffset - i * gridHeight - (gridHeight - GOAL_SIZE_Y) / 2.0f;
				float goalBtmY = heightOffset - (i + 1) * gridHeight + (gridHeight - GOAL_SIZE_Y) / 2.0f;
				float goalLeftX = -widthOffset + j * gridWidth + (gridWidth - GOAL_SIZE_X) / 2;
				float goalRightX = -widthOffset + (j + 1) * gridWidth - (gridWidth - GOAL_SIZE_X) / 2.0f;

				// If player x position is within the goal
				if (playerHsX1 > goalLeftX && playerLeftX < goalRightX || playerHsX2 < goalRightX && playerRightX > goalLeftX) {
					// If player y position is within the goal
					if (playerHsY1 > goalBtmY && playerTopY < goalTopY || playerHsY2 > goalBtmY && playerBtmY < goalTopY) {
						level1_state = WIN;
						Player.velocity.x = 0.0f;
						Player.velocity.y = 0.0f;
					}
				}
			}

			if (platform[i][j].GetPlatformType() == COLLECTABLES) {
				float collectableTopY = heightOffset - i * gridHeight - (gridHeight - COLLECTABLE_SIZE_Y) / 2.0f;
				float collectableBtmY = heightOffset - (i + 1) * gridHeight + (gridHeight - COLLECTABLE_SIZE_Y) / 2.0f;
				float collectableLeftX = -widthOffset + j * gridWidth + (gridWidth - COLLECTABLE_SIZE_X) / 2;
				float collectableRightX = -widthOffset + (j + 1) * gridWidth - (gridWidth - COLLECTABLE_SIZE_X) / 2.0f;

				// If player x position is within the collectable
				if (playerHsX1 > collectableLeftX && playerLeftX < collectableRightX || playerHsX2 < collectableRightX && playerRightX > collectableLeftX) {
					// If player y position is within the collectable
					if (playerHsY1 > collectableBtmY && playerTopY < collectableTopY || playerHsY2 > collectableBtmY && playerBtmY < collectableTopY) {
						platform[i][j].SetPlatformType(EMPTY_SPACE);

						++e_numOfCollectableCollected;


#if DEBUG
						std::cout << "Collision with a collectible \n";
						std::cout << "Collectable Left: " << e_totalNumOfCollectable - e_numOfCollectableCollected << "\n";
						
#endif
					}
				}
			}
		}
	}

}
