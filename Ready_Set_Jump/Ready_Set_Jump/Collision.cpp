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
int e_numOfCollectableCollected;
// --------------------------------------------------------------------------- // End of external variables


// --------------------------------------------------------------------------- // End of external variables


// ----------------------------------------------------------------------------
// Checks for player collision against level and snap accordingly
// ----------------------------------------------------------------------------
void DynamicObj::LevelCollision(){
	// Will be a static value once there are grids outside of the window
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;
	collisionFlag = 0;
	// "Normalizing" hotspots
	topY = (heightOffset - position.y - GetScale().y / 2.0f) / e_gridHeightSize; // Top bound
	btmY = (heightOffset - position.y + GetScale().y / 2.0f) / e_gridHeightSize; // Btm bound
	leftX = (widthOffset + position.x - GetScale().x / 2.0f) / e_gridWidthSize; // Left bound
	rightX = (widthOffset + position.x + GetScale().x / 2.0f) / e_gridWidthSize; // Right bound
	X1 = (widthOffset + position.x - GetScale().x / 4.0f) / e_gridWidthSize; // 25% X
	X2 = (widthOffset + position.x + GetScale().x / 4.0f) / e_gridWidthSize; // 75% X
	Y1 = (heightOffset - position.y - GetScale().y / 4.0f) / e_gridHeightSize; // 25% Y
	Y2 = (heightOffset - position.y + GetScale().y / 4.0f) / e_gridHeightSize; // 75% Y

	// If out of play area // This not running cause the 1 in level 1 running
	if (leftX < 0 || rightX > e_binaryMapWidth-1 || topY < 0 || btmY > e_binaryMapHeight-1) {
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		jumpReady = true;
		position = { e_playerSpawnPointX,e_playerSpawnPointY };

	}
	else {
		// Top collided
		if (platform[topY][X1].GetPlatformType() > EMPTY_SPACE && platform[topY][X1].GetPlatformType() < GOAL
			|| platform[topY][X2].GetPlatformType() > EMPTY_SPACE && platform[topY][X2].GetPlatformType() < GOAL) {
			collisionFlag |= COLLISION_TOP;

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
			collisionFlag |= COLLISION_BOTTOM;

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

		}

		// Right collided
		if (platform[Y1][rightX].GetPlatformType() > EMPTY_SPACE && platform[Y1][rightX].GetPlatformType() < GOAL) {
			collisionFlag |= COLLISION_RIGHT;
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
			collisionFlag |= COLLISION_LEFT;

#if DEBUG
				std::cout << "Left collided, Coordinates\n";
				std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
				std::cout << "        +\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
				std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
#endif
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
}

void DynamicObj::SnapToGrid() {

	// Will be a static value once there are grids outside of the window
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;


	if (collisionFlag & COLLISION_TOP) {
		position.y = heightOffset - (topY + 1) * e_gridHeightSize - (PLAYER_SIZE_Y / 2.0f);
	}

	if (collisionFlag & COLLISION_BOTTOM) {
		position.y = heightOffset - btmY * e_gridHeightSize + (PLAYER_SIZE_Y / 2.0f);
	}

	if (collisionFlag & COLLISION_LEFT) {
		position.x = -widthOffset + (leftX + 0.9999) * e_gridWidthSize + PLAYER_SIZE_X / 2.0f;
	}

	if (collisionFlag & COLLISION_RIGHT) {
		position.x = -widthOffset + rightX * e_gridWidthSize - PLAYER_SIZE_X / 2.0f;
	}
}

// ----------------------------------------------------------------------------
// Checks for player collision against objects that dont require have seperate width and height,
// such as collectables and goal(exit point)
// ----------------------------------------------------------------------------
void ObjectiveCollision() {
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
				float goalTopY = heightOffset - i * e_gridHeightSize - (e_gridHeightSize - GOAL_SIZE_Y) / 2.0f;
				float goalBtmY = heightOffset - (i + 1) * e_gridHeightSize + (e_gridHeightSize - GOAL_SIZE_Y) / 2.0f;
				float goalLeftX = -widthOffset + j * e_gridWidthSize + (e_gridWidthSize - GOAL_SIZE_X) / 2;
				float goalRightX = -widthOffset + (j + 1) * e_gridWidthSize - (e_gridWidthSize - GOAL_SIZE_X) / 2.0f;

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
				float collectableTopY = heightOffset - i * e_gridHeightSize - (e_gridHeightSize - COLLECTABLE_SIZE_Y) / 2.0f;
				float collectableBtmY = heightOffset - (i + 1) * e_gridHeightSize + (e_gridHeightSize - COLLECTABLE_SIZE_Y) / 2.0f;
				float collectableLeftX = -widthOffset + j * e_gridWidthSize + (e_gridWidthSize - COLLECTABLE_SIZE_X) / 2;
				float collectableRightX = -widthOffset + (j + 1) * e_gridWidthSize - (e_gridWidthSize - COLLECTABLE_SIZE_X) / 2.0f;

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
