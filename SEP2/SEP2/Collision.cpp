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
int e_collectableNum;
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

// Checks for player collsion and snap if required
void CollisionCheck() {
	
	float gridWidth = WINDOW_WIDTH / e_binaryMapWidth;
	float gridHeight = WINDOW_HEIGHT / e_binaryMapHeight;
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;

	e_collisionFlag = false;
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
		if (platform[abs(btmY)][abs(X1)].GetPlatformType() > EMPTY_SPACE && platform[abs(btmY)][abs(X1)].GetPlatformType() < COLLECTABLES
			|| platform[abs(btmY)][abs(X2)].GetPlatformType() > EMPTY_SPACE && platform[abs(btmY)][abs(X2)].GetPlatformType() < COLLECTABLES) {
			colliding = true;
			e_collisionFlag += COLLISION_BOTTOM;
			if (Player.position.x < (platform[abs(btmY)][abs(X1)].position.x + (platform[abs(btmY)][abs(X1)].GetScale().x / 2.f))) { // checks which side of the grid the player is cooupying more

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
					e_jumpForceMod = 0.7f;
					break;
				case SLIME_BLOCK:
					if (abs(Player.velocity.y) <= 2) Player.velocity.y = 0;
					Player.velocity.y = -(Player.velocity.y * 0.5f);
					friction = slimeFriction;
					break;
				case GOAL:
					level1_state = WIN;
				default:
					break;
				}
			}
			else if (Player.position.x > (platform[abs(btmY)][abs(X1)].position.x - (platform[abs(btmY)][abs(X1)].GetScale().x / 2.f))) {
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
					e_jumpForceMod = 0.7f;
					break;
				case SLIME_BLOCK:
					if (abs(Player.velocity.y) <= 2) Player.velocity.y = 0;
					Player.velocity.y = -(Player.velocity.y * 0.7f);
					friction = slimeFriction;
					break;
				case GOAL:
					level1_state = WIN;
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
		if (platform[abs(Y1)][abs(rightX)].GetPlatformType() > EMPTY_SPACE && platform[abs(Y1)][abs(rightX)].GetPlatformType() < COLLECTABLES) {
			colliding = true;
			e_collisionFlag += COLLISION_RIGHT;
			if (Player.position.y < (platform[abs(Y1)][abs(rightX)].position.y + (platform[abs(Y1)][abs(rightX)].GetScale().y / 2.f)) || // checks which side of the grid the player is cooupying more
				Player.position.y >(platform[abs(Y1)][abs(rightX)].position.y - (platform[abs(Y1)][abs(rightX)].GetScale().y / 2.f))) {
				switch (platform[abs(Y1)][abs(rightX)].GetPlatformType())
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
				case GOAL:
					level1_state = WIN;
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
			else if(platform[abs(Y2)][abs(rightX)].GetPlatformType() > EMPTY_SPACE && platform[abs(Y2)][abs(rightX)].GetPlatformType() < COLLECTABLES) {
				switch (platform[abs(Y2)][abs(rightX)].GetPlatformType())
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
		if (platform[abs(Y1)][abs(leftX)].GetPlatformType() > EMPTY_SPACE && platform[abs(Y1)][abs(leftX)].GetPlatformType() < COLLECTABLES) {
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
					currFrameStickyCollision = true;
					if (!prevFrameStickyCollision)Player.jumpReady = true;
					break;
				case SLIME_BLOCK:
					if (Player.velocity.x) {
						//Player.velocity.y = static_cast<float>(e_jumpForce * Player.direction.y);
						Player.velocity.x = -Player.velocity.x;
					}
					break;
				case GOAL:
					level1_state = WIN;
				}
			}
			else if (platform[abs(Y2)][abs(leftX)].GetPlatformType() > EMPTY_SPACE && platform[abs(Y2)][abs(leftX)].GetPlatformType() < COLLECTABLES) {
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
	prevFrameStickyCollision = currFrameStickyCollision;
}

void CollectableCheck() {
	// Thinking of making this into a static, when there will be grids outside of the exe window
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

	e_collectableNum = 0;

	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {
			if (platform[i][j].GetPlatformType() == COLLECTABLES) {

				e_collectableNum++;

				float collectableTopY = heightOffset - i * gridHeight - (gridHeight - COLLECTABLE_SIZE_Y) / 2.0f;
				float collectableBtmY = heightOffset - (i + 1) * gridHeight + (gridHeight - COLLECTABLE_SIZE_Y) / 2.0f;
				float collectableLeftX = -widthOffset + j * gridWidth + (gridWidth - COLLECTABLE_SIZE_X) / 2;
				float collectableRightX = -widthOffset + (j + 1) * gridWidth - (gridWidth - COLLECTABLE_SIZE_X) / 2.0f;

				// If player x position is within the collectable
				if (playerHsX1 > collectableLeftX && playerLeftX < collectableRightX || playerHsX2 < collectableRightX && playerRightX > collectableLeftX) {
					// If player y position is within the collectable
					if (playerHsY1 > collectableBtmY && playerTopY < collectableTopY || playerHsY2 > collectableBtmY && playerBtmY < collectableTopY) {
						platform[i][j].SetPlatformType(EMPTY_SPACE);


#if DEBUG
						e_collectableNum--;
						std::cout << "Collision with a collectible \n";
						std::cout << "Collectable Left: " << e_collectableNum << "\n";
						
#endif
					}
				}
			}
		}
	}

}
