/*****************************************************************
  *  \file Collision.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  Collision component.
  *  - LevelCollision (Class member function)
  *		 Checks for player collision against level.
  *
  *  - SnapToGrid (Class member function)
  *		 Snaps to grid
  *
  *  - ObjectCollision
  *		 Checks for player collision against objects that is not a platform
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/

#include "Collision.hpp"
#include "Timer.hpp"
#include <iostream>
#include <fstream>

// External Variables
bool e_outOfMap;
unsigned int e_collidedObjectType, e_numOfcollectibleCollected, e_collidedObjectXPosX, e_collidedObjectXPosY;

/*****************************************************************
 * @brief
 *		 Checks for player collision against level.
****************************************************************/
void DynamicObj::LevelCollision(){

	// Player Hotspots Normalized
	topY = (HALVE_WINDOW_HEIGHT - position.y - GetScale().y / 2.0f) / GRID_HEIGHT_SIZE; // Top bound
	btmY = (HALVE_WINDOW_HEIGHT - position.y + GetScale().y / 2.0f) / GRID_HEIGHT_SIZE; // Btm bound
	leftX = (HALVE_WINDOW_WIDTH + position.x - GetScale().x / 2.0f) / GRID_WIDTH_SIZE; // Left bound
	rightX = (HALVE_WINDOW_WIDTH + position.x + GetScale().x / 2.0f) / GRID_WIDTH_SIZE; // Right bound
	X1 = (HALVE_WINDOW_WIDTH + position.x - GetScale().x / 4.0f) / GRID_WIDTH_SIZE; // 25% X
	X2 = (HALVE_WINDOW_WIDTH + position.x + GetScale().x / 4.0f) / GRID_WIDTH_SIZE; // 75% X
	Y1 = (HALVE_WINDOW_HEIGHT - position.y - GetScale().y / 4.0f) / GRID_HEIGHT_SIZE; // 25% Y
	Y2 = (HALVE_WINDOW_HEIGHT - position.y + GetScale().y / 4.0f) / GRID_HEIGHT_SIZE; // 75% Y

	// If out of play area
	if (leftX < 0 || rightX > e_binaryMapWidth || topY < 0 || btmY > e_binaryMapHeight) {
		e_outOfMap = true;
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
}

/*****************************************************************
 * @brief
 *		 Snaps to grid
****************************************************************/
void DynamicObj::SnapToGrid() {

	if (collisionFlag & COLLISION_TOP) {
		position.y = HALVE_WINDOW_HEIGHT - static_cast<int>(topY + 1) * GRID_HEIGHT_SIZE - (PLAYER_SIZE_Y / 2.0f);
	}

	if (collisionFlag & COLLISION_BOTTOM) {
		position.y = HALVE_WINDOW_HEIGHT - static_cast<int>(btmY) * GRID_HEIGHT_SIZE + (PLAYER_SIZE_Y / 2.0f);
	}

	if (collisionFlag & COLLISION_LEFT) {
		position.x = -HALVE_WINDOW_WIDTH + (static_cast<int>(leftX) + 0.99999f) * GRID_WIDTH_SIZE + (PLAYER_SIZE_X / 2.0f);
	}

	if (collisionFlag & COLLISION_RIGHT) {
		position.x = -HALVE_WINDOW_WIDTH + static_cast<int>(rightX) * GRID_WIDTH_SIZE - (PLAYER_SIZE_X / 2.0f);
	}
}

/*****************************************************************
 * @brief 
 *		 Checks for player collision against objects that is not a platform
****************************************************************/
void ObjectCollision() {
	// Player hotspots
	int playerTopY = static_cast<int>(Player.position.y - Player.GetScale().y / 2.0f); // Top bound
	int playerBtmY = static_cast<int>(Player.position.y + Player.GetScale().y / 2.0f); // Btm bound
	int playerLeftX = static_cast<int>(Player.position.x - Player.GetScale().x / 2.0f); // Left bound
	int playerRightX = static_cast<int>(Player.position.x + Player.GetScale().x / 2.0f); // Right bound

	int playerHsX1 = static_cast<int>(Player.position.x - Player.GetScale().x / 4.0f); // 25% X
	int playerHsX2 = static_cast<int>(Player.position.x + Player.GetScale().x / 4.0f); // 75% X
	int playerHsY1 = static_cast<int>(Player.position.y - Player.GetScale().y / 4.0f); // 25% Y
	int playerHsY2 = static_cast<int>(Player.position.y + Player.GetScale().y / 4.0f); // 75% Y

	float objectTopY = 0.f, objectBtmY = 0.f, objectLeftX = 0.f, objectRightX = 0.f;
	float scaleY = 0.f, scaleX = 0.f;

	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {

			if (platform[i][j].GetPlatformType() == GOAL) {
				scaleX = 0.6f;
				scaleY = 0.7f;
			}
			else {
				scaleX = 1.f;
				scaleY = 1.f;
			}
			
			// Object bounds
			objectTopY = HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE - (GRID_HEIGHT_SIZE - platform[i][j].GetScale().y * scaleY) / 2.0f;
			objectBtmY = HALVE_WINDOW_HEIGHT - (i + 1) * GRID_HEIGHT_SIZE + (GRID_HEIGHT_SIZE - platform[i][j].GetScale().y * scaleY) / 2.0f;
			objectLeftX = -HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE + (GRID_WIDTH_SIZE - platform[i][j].GetScale().x * scaleX) / 2;
			objectRightX = -HALVE_WINDOW_WIDTH + (j + 1) * GRID_WIDTH_SIZE - (GRID_WIDTH_SIZE - platform[i][j].GetScale().x * scaleX) / 2.0f;
			
			// If player x position is within the object
			if (playerHsX1 > objectLeftX && playerLeftX < objectRightX || playerHsX2 < objectRightX && playerRightX > objectLeftX) {
				// If player y position is within the object
				if (playerHsY1 > objectBtmY && playerTopY < objectTopY || playerHsY2 > objectBtmY && playerBtmY < objectTopY) {

					if (platform[i][j].GetPlatformType() == GOAL) {
						e_collidedObjectType = GOAL;
					}
					else if (platform[i][j].GetPlatformType() == CHECKPOINT) {
						e_collidedObjectType = CHECKPOINT;
						e_collidedObjectXPosX = j;
						e_collidedObjectXPosY = i;
					}
					else if (platform[i][j].GetPlatformType() == COLLECTIBLES) {
						e_collidedObjectType = COLLECTIBLES;
						e_collidedObjectXPosX = j;
						e_collidedObjectXPosY = i;
#if DEBUG
						std::cout << "Collision with a collectible \n";
						std::cout << "collectible Left: " << e_totalNumOfcollectible - e_numOfcollectibleCollected << "\n";

#endif
					}
				}
			}

		} // End of width looping
	} // End of height looping
}
