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
int e_numOfcollectibleCollected;
// --------------------------------------------------------------------------- // End of external variables

// ----------------------------------------------------------------------------
// Checks for player collision against level and snap accordingly
// ----------------------------------------------------------------------------
void DynamicObj::LevelCollision(){
	collisionFlag = 0;
	// Hotspots
	topY = (WINDOW_HEIGHT_OFFSET - position.y - GetScale().y / 2.0f) / GRID_HEIGHT_SIZE; // Top bound
	btmY = (WINDOW_HEIGHT_OFFSET - position.y + GetScale().y / 2.0f) / GRID_HEIGHT_SIZE; // Btm bound
	leftX = (WINDOW_WIDTH_OFFSET + position.x - GetScale().x / 2.0f) / GRID_WIDTH_SIZE; // Left bound
	rightX = (WINDOW_WIDTH_OFFSET + position.x + GetScale().x / 2.0f) / GRID_WIDTH_SIZE; // Right bound
	X1 = (WINDOW_WIDTH_OFFSET + position.x - GetScale().x / 4.0f) / GRID_WIDTH_SIZE; // 25% X
	X2 = (WINDOW_WIDTH_OFFSET + position.x + GetScale().x / 4.0f) / GRID_WIDTH_SIZE; // 75% X
	Y1 = (WINDOW_HEIGHT_OFFSET - position.y - GetScale().y / 4.0f) / GRID_HEIGHT_SIZE; // 25% Y
	Y2 = (WINDOW_HEIGHT_OFFSET - position.y + GetScale().y / 4.0f) / GRID_HEIGHT_SIZE; // 75% Y

	// If out of play area // This not running cause the 1 in level 1 running (SHIFT OUT IF GOT TIME)
	if (leftX < 0 || rightX > e_binaryMapWidth || btmY > e_binaryMapHeight) {
		
#if DEBUG
		std::cout << "==================== Reset =====================\n";
		std::cout << "  [" << (X1) << "," << (topY) << "] " << "[" << (X2) << "," << (topY) << "]\n";
		std::cout << "[" << (leftX) << "," << (Y1) << "]     " << "[" << (rightX) << "," << (Y1) << "]\n";
		std::cout << "        +\n";
		std::cout << "[" << (leftX) << "," << (Y2) << "]     " << "[" << (rightX) << "," << (Y2) << "]\n";
		std::cout << "  [" << (X1) << "," << (btmY) << "] " << "[" << (X2) << "," << (btmY) << "]\n\n";
#endif


		velocity.x = 0.0f;
		velocity.y = 0.0f;
		jumpReady = true;
		position = { playerSpawnPoint.x,playerSpawnPoint.y };

	}
	else {
		// Top collided
		if (platform[static_cast<int>(topY)][static_cast<int>(X1)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(topY)][static_cast<int>(X1)].GetPlatformType() < GOAL
			|| platform[static_cast<int>(topY)][static_cast<int>(X2)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(topY)][static_cast<int>(X2)].GetPlatformType() < GOAL) {
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
		if (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetPlatformType() < GOAL
			|| platform[static_cast<int>(btmY)][static_cast<int>(X2)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(btmY)][static_cast<int>(X2)].GetPlatformType() < GOAL) {
			collisionFlag |= COLLISION_BOTTOM;

			//std::cout << "Btm collided Jump ready: " << jumpReady << "\n";

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
		if (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetPlatformType() < GOAL
			|| platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType() < GOAL) {
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
		if (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetPlatformType() < GOAL
			|| platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType() < GOAL) {
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

	if (collisionFlag & COLLISION_TOP) {
		position.y = WINDOW_HEIGHT_OFFSET - static_cast<int>(topY + 1) * GRID_HEIGHT_SIZE - (PLAYER_SIZE_Y / 2.0f);
	}

	if (collisionFlag & COLLISION_BOTTOM) {
		position.y = WINDOW_HEIGHT_OFFSET - static_cast<int>(btmY) * GRID_HEIGHT_SIZE + (PLAYER_SIZE_Y / 2.0f);
		//std::cout << "Y Pos = " << position.y << "\n";
	}

	if (collisionFlag & COLLISION_LEFT) {
		position.x = -WINDOW_WIDTH_OFFSET + (static_cast<int>(leftX) + 0.9999) * GRID_WIDTH_SIZE + PLAYER_SIZE_X / 2.0f;
	}

	if (collisionFlag & COLLISION_RIGHT) {
		position.x = -WINDOW_WIDTH_OFFSET + static_cast<int>(rightX) * GRID_WIDTH_SIZE - PLAYER_SIZE_X / 2.0f;
	}
}

// ----------------------------------------------------------------------------
// Checks for player collision against objects that dont require have seperate width and height,
// such as COLLECTIBLES and goal(exit point)
// ----------------------------------------------------------------------------
void ObjectiveCollision() {
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
				float goalTopY = WINDOW_HEIGHT_OFFSET - i * GRID_HEIGHT_SIZE - (GRID_HEIGHT_SIZE - GOAL_SIZE_Y * 0.7f) / 2.0f;
				float goalBtmY = WINDOW_HEIGHT_OFFSET - (i + 1) * GRID_HEIGHT_SIZE + (GRID_HEIGHT_SIZE - GOAL_SIZE_Y * 0.7f) / 2.0f;
				float goalLeftX = -WINDOW_WIDTH_OFFSET + j * GRID_WIDTH_SIZE + (GRID_WIDTH_SIZE - GOAL_SIZE_X * 0.6f ) * 0.5f;
				float goalRightX = -WINDOW_WIDTH_OFFSET + (j + 1) * GRID_WIDTH_SIZE - (GRID_WIDTH_SIZE - GOAL_SIZE_X * 0.6f) / 2.0f;

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
			if (platform[i][j].GetPlatformType() == CHECKPOINT) {
				float checkPointTopY = WINDOW_HEIGHT_OFFSET - i * GRID_HEIGHT_SIZE - (GRID_HEIGHT_SIZE - GOAL_SIZE_Y) / 2.0f;
				float checkPointBtmY = WINDOW_HEIGHT_OFFSET - (i + 1) * GRID_HEIGHT_SIZE + (GRID_HEIGHT_SIZE - GOAL_SIZE_Y) / 2.0f;
				float checkPointLeftX = -WINDOW_WIDTH_OFFSET + j * GRID_WIDTH_SIZE + (GRID_WIDTH_SIZE - GOAL_SIZE_X) / 2;
				float checkPointRightX = -WINDOW_WIDTH_OFFSET + (j + 1) * GRID_WIDTH_SIZE - (GRID_WIDTH_SIZE - GOAL_SIZE_X) / 2.0f;

				// If player x position is within the goal
				if (playerHsX1 > checkPointLeftX && playerLeftX < checkPointRightX || playerHsX2 < checkPointRightX && playerRightX > checkPointLeftX) {
					// If player y position is within the goal
					if (playerHsY1 > checkPointBtmY && playerTopY < checkPointTopY || playerHsY2 > checkPointBtmY && playerBtmY < checkPointTopY) {
						playerSpawnPoint = platform[i][j].GetPosition();
						platform[i][j].SetPlatformType(EMPTY_SPACE);
					}
				}
			}

			if (platform[i][j].GetPlatformType() == COLLECTIBLES) {
				float collectibleTopY = WINDOW_HEIGHT_OFFSET - i * GRID_HEIGHT_SIZE - (GRID_HEIGHT_SIZE - collectible_SIZE_Y) / 2.0f;
				float collectibleBtmY = WINDOW_HEIGHT_OFFSET - (i + 1) * GRID_HEIGHT_SIZE + (GRID_HEIGHT_SIZE - collectible_SIZE_Y) / 2.0f;
				float collectibleLeftX = -WINDOW_WIDTH_OFFSET + j * GRID_WIDTH_SIZE + (GRID_WIDTH_SIZE - collectible_SIZE_X) / 2;
				float collectibleRightX = -WINDOW_WIDTH_OFFSET + (j + 1) * GRID_WIDTH_SIZE - (GRID_WIDTH_SIZE - collectible_SIZE_X) / 2.0f;

				// If player x position is within the collectible
				if (playerHsX1 > collectibleLeftX && playerLeftX < collectibleRightX || playerHsX2 < collectibleRightX && playerRightX > collectibleLeftX) {
					// If player y position is within the collectible
					if (playerHsY1 > collectibleBtmY && playerTopY < collectibleTopY || playerHsY2 > collectibleBtmY && playerBtmY < collectibleTopY) {
						platform[i][j].SetPlatformType(EMPTY_SPACE);

						++e_numOfcollectibleCollected;


#if DEBUG
						std::cout << "Collision with a collectible \n";
						std::cout << "collectible Left: " << e_totalNumOfcollectible - e_numOfcollectibleCollected << "\n";
						
#endif
					}
				}
			}
		}
	}

}
