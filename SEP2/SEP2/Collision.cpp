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
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------
// Const Variables
const int	COLLISION_LEFT   = 0x00000001;	//0001
const int	COLLISION_RIGHT  = 0x00000002;	//0010
const int	COLLISION_TOP    = 0x00000004;	//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000
// --------------------------------------------------------------------------- // End of external variables

// Checks for player collsion and snap if required
void CollisionCheck() {
	
	float gridWidth = WINDOW_WIDTH / e_binaryMapWidth;
	float gridHeight = WINDOW_HEIGHT / e_binaryMapHeight;
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;

	e_collisionFlag = 0;
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
	

	// If out of play area
	if (leftX < 0 || rightX > e_binaryMapWidth-1 || topY < 0 || btmY > e_binaryMapHeight-1) {
		Player.velocity.x = 0.0f;
		Player.velocity.y = 0.0f;
		Player.jumpReady = true;
		Player.position.x = 0.0f;
		Player.position.y = PLAYER_SIZE_Y / 2.0f;
		e_levelTime = 0.0f;
	}
	else {
		// Top collided
		if (platform[abs(topY)][abs(X1)].GetPlatformType()|| platform[abs(topY)][abs(X2)].GetPlatformType()) {
			colliding = true;

			// Collectabiles detection
			if (platform[abs(topY)][abs(X1)].GetPlatformType() == COLLECTABLES || platform[abs(topY)][abs(X2)].GetPlatformType() == COLLECTABLES) {
				e_collisionFlag = 0;
				colliding = false;
				platform[abs(btmY)][abs(X1)].SetPlatformType(EMPTY_SPACE);
			}else{
				e_collisionFlag += COLLISION_TOP;
				Player.velocity.y -= Player.velocity.y;
			}

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
		if (platform[abs(btmY)][abs(X1)].GetPlatformType()|| platform[abs(btmY)][abs(X2)].GetPlatformType()) {
			colliding = true;
			e_collisionFlag += COLLISION_BOTTOM;
			if (Player.position.x < (platform[abs(btmY)][abs(X1)].position.x + (platform[abs(btmY)][abs(X1)].GetScale().x / 2.f)) || // checks which side of the grid the player is cooupying more
				Player.position.x >(platform[abs(btmY)][abs(X1)].position.x - (platform[abs(btmY)][abs(X1)].GetScale().x / 2.f))) {
				switch (platform[abs(btmY)][abs(X1)].GetPlatformType())
				{
				case NORMAL_BLOCK:// normal surface
					Player.velocity.y -= Player.velocity.y;
					friction = normalFriction;
					break;
				case ICE_BLOCK: // ice physics
					Player.velocity.y -= Player.velocity.y;
					friction = iceFriction;
					break;
				case STICKY_BLOCK:// sticky physics
					Player.velocity.y -= Player.velocity.y;
					friction = fullStopFriction;
					std::cout << e_jumpForce << '\n';
					if (e_jumpForce == original_jumpForce && min_jumpForce == originalMin_jumpForce) {
						e_jumpForce -= 50.f;
						min_jumpForce -= 50.f;
					}
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					colliding = false;
					platform[abs(btmY)][abs(X1)].SetPlatformType(EMPTY_SPACE);
					break;
				case GOAL:
					level1_state = WIN;
				default:
					break;
				}
			}
			else {
				switch (platform[abs(btmY)][abs(X2)].GetPlatformType())
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
					if (e_jumpForce == original_jumpForce && min_jumpForce == originalMin_jumpForce) {
						e_jumpForce -= 50.f;
						min_jumpForce -= 50.f;
					}
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					colliding = false;
					platform[abs(btmY)][abs(X2)].SetPlatformType(EMPTY_SPACE);
					break;
				case GOAL:
					level1_state = WIN;
				default:
					break;
				}
			}
			if (!Player.velocity.x) {
				Player.jumpReady = true;
			}
			
			/*
#if DEBUG
				std::cout << "Btm collided, Coordinates\n";
				std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
				std::cout << "        +\n";
				std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
				std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
#endif
			*/
		}
		// Right collided
		if (platform[abs(Y1)][abs(rightX)].GetPlatformType()|| platform[abs(Y2)][abs(rightX)].GetPlatformType()) {
			colliding = true;
			e_collisionFlag += COLLISION_RIGHT;
			if (Player.position.y < (platform[abs(Y1)][abs(rightX)].position.y + (platform[abs(Y1)][abs(rightX)].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
				Player.position.y >(platform[abs(Y1)][abs(rightX)].position.y - (platform[abs(Y1)][abs(rightX)].GetScale().y / 2.f))) {
				switch (platform[abs(Y1)][abs(rightX)].GetPlatformType())
				{
				case STICKY_BLOCK:// sticky physics
					dragCoeff = stickDrag;
					friction = fullStopFriction;
					Player.jumpReady = true;
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					colliding = false;
					platform[abs(Y1)][abs(rightX)].SetPlatformType(EMPTY_SPACE);
					break;
				case EMPTY_SPACE:
					colliding = false;
					break;
				case GOAL:
					level1_state = WIN;
					break;
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					break;
				}
			}
			else {
				switch (platform[abs(Y2)][abs(rightX)].GetPlatformType())
				{
				case STICKY_BLOCK:// sticky physics
					dragCoeff = stickDrag;
					friction = fullStopFriction;
					Player.jumpReady = true;
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					colliding = false;
					platform[abs(Y2)][abs(rightX)].SetPlatformType(EMPTY_SPACE);
					break;
				case EMPTY_SPACE:
					colliding = false;
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
		if (platform[abs(Y1)][abs(leftX)].GetPlatformType() || platform[abs(Y2)][abs(leftX)].GetPlatformType()) {
			colliding = true;
			e_collisionFlag += COLLISION_LEFT;
			if (Player.position.y < (platform[abs(Y1)][abs(leftX)].position.y + (platform[abs(Y1)][abs(leftX)].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
				Player.position.y >(platform[abs(Y1)][abs(leftX)].position.y - (platform[abs(Y1)][abs(leftX)].GetScale().y / 2.f))) {
				switch (platform[abs(Y1)][abs(leftX)].GetPlatformType())
				{
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					std::cout << "2 \n";
					break;
				case STICKY_BLOCK:// sticky physics
					dragCoeff = stickDrag;
					friction = fullStopFriction;
					Player.jumpReady = true;
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					platform[abs(Y1)][abs(leftX)].SetPlatformType(EMPTY_SPACE);
					colliding = false;
					std::cout << "1 \n";
					break;
				case EMPTY_SPACE:
					colliding = false;
					break;
				case GOAL:
					level1_state = WIN;
				}
			}
			else {
				switch (platform[abs(Y2)][abs(leftX)].GetPlatformType())
				{
				default:
					dragCoeff = normalDrag;
					friction = fullStopFriction;
					std::cout << "4 \n";
					break;
				case STICKY_BLOCK:// sticky physics
					friction = fullStopFriction;
					dragCoeff = stickDrag;
					Player.jumpReady = true;
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					platform[abs(Y2)][abs(leftX)].SetPlatformType(EMPTY_SPACE);
					colliding = false;
					std::cout << "3 \n";
					break;
				case EMPTY_SPACE:
					colliding = false;
					break;
				case GOAL:
					level1_state = WIN;
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
}

void CollectibleCheck() {
	// Thinking of making this into a static, when there will be grids outside of the exe window
	float gridWidth = WINDOW_WIDTH / e_binaryMapWidth;
	float gridHeight = WINDOW_HEIGHT / e_binaryMapHeight;

	// Offset used for grid position calculation, making calculation start from top left instead of center of window
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;

	// "Normalizing" player hotspots
	int playerTopY = (heightOffset - Player.position.y - Player.GetScale().y / 2.0f) / gridHeight; // Top bound
	int playerBtmY = (heightOffset - Player.position.y + Player.GetScale().y / 2.0f) / gridHeight; // Btm bound
	int playerLeftX = (widthOffset + Player.position.x - Player.GetScale().x / 2.0f) / gridWidth; // Left bound
	int playerRightX = (widthOffset + Player.position.x + Player.GetScale().x / 2.0f) / gridWidth; // Right bound

	int playerHsX1 = (widthOffset + Player.position.x - Player.GetScale().x / 4.0f) / gridWidth; // 25% X
	int playerHsX2 = (widthOffset + Player.position.x + Player.GetScale().x / 4.0f) / gridWidth; // 75% X
	int playerHsY1 = (heightOffset - Player.position.y - Player.GetScale().y / 4.0f) / gridHeight; // 25% Y
	int playerHsY2 = (heightOffset - Player.position.y + Player.GetScale().y / 4.0f) / gridHeight; // 75% Y

	// Variables used for debugging
#ifdef DEBUG
	int collectibleCounter = 0;
#endif

	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {
			if (platform[i][j].GetPlatformType() == COLLECTABLES) {
				float collectableTopY = heightOffset - i * gridHeight - (gridHeight - COLLECTABLE_SIZE_Y) / 2;
				float collectableBtmY = heightOffset - (i + 1) * gridHeight + (gridHeight - COLLECTABLE_SIZE_Y) / 2;
				float collectableLeftX = -widthOffset + j * gridWidth + (gridWidth - COLLECTABLE_SIZE_X) / 2;
				float collectableRightX = -widthOffset + (j + 1) * gridWidth - (gridWidth - COLLECTABLE_SIZE_X) / 2;

#ifdef DEBUG
				collectibleCounter++;
#endif
				
			}
		}
	}

#ifdef DEBUG
	std::cout << "Collectable Left: " << collectibleCounter << "\n";
#endif

}