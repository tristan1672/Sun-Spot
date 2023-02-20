// ---------------------------------------------------------------------------
// includes
#include "Collision.hpp"

extern DynamicObj Player;
extern Platform** platform;

extern int e_collisionFlag;
const int	COLLISION_LEFT   = 0x00000001;	//0001
const int	COLLISION_RIGHT  = 0x00000002;	//0010
const int	COLLISION_TOP    = 0x00000004;	//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000

// ----------------------------------------------------------------------------
// This function checks for player collsion 
// ----------------------------------------------------------------------------
void collisionCheck(float playerX, float playerY) {
	
	float gridWidth = WINDOW_WIDTH / BINARY_MAP_WIDTH;
	float gridHeight = WINDOW_HEIGHT / BINARY_MAP_HEIGHT;
	float widthOffset = WINDOW_WIDTH / 2.0f;
	float heightOffset = WINDOW_HEIGHT / 2.0f;

	int e_collisionFlag = 0;
	bool colliding{};

	// "Normalizing"
	int topY = (heightOffset - playerY - Player.GetScale().y / 2.0f) / gridHeight; // Top bound
	int btmY = (heightOffset - playerY + Player.GetScale().y / 2.0f) / gridHeight; // Btm bound
	int leftX = (widthOffset + playerX - Player.GetScale().x / 2.0f) / gridWidth; // Left bound
	int rightX = (widthOffset + playerX + Player.GetScale().x / 2.0f) / gridWidth; // Right bound

	int X1 = (widthOffset + playerX - Player.GetScale().x / 4.0f) / gridWidth; // 25% X
	int X2 = (widthOffset + playerX + Player.GetScale().x / 4.0f) / gridWidth; // 75% X
	int Y1 = (heightOffset - playerY - Player.GetScale().y / 4.0f) / gridHeight; // 25% Y
	int Y2 = (heightOffset - playerY + Player.GetScale().y / 4.0f) / gridHeight; // 75% Y

	/*
	if (DEBUG) {
		std::cout << "Coordinates\n\n";
		std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
		std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
		std::cout << "        +\n";
		std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
		std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
	}
	*/

	// If out of play area
	if (leftX < 0 || rightX > BINARY_MAP_WIDTH-1 || topY < 0 || btmY > BINARY_MAP_HEIGHT-1) {
		//std::cout << Player.velocity.x << '\n';
		Player.velocity.x = 0.0f;
		Player.velocity.y = 0.0f;
		Player.collideBotton = true;
		Player.position.x = 0.0f;
		Player.position.y = PLAYER_SIZE_Y / 2.0f;
	}
	else {
		// Top collided
		if (platform[abs(topY)][abs(X1)].GetPlatformType()|| platform[abs(topY)][abs(X2)].GetPlatformType()) {
			colliding = true;
			std::cout << "Top collided \n";

			// Collectabiles detection
			if (platform[abs(topY)][abs(X1)].GetPlatformType() == COLLECTABLES || platform[abs(topY)][abs(X2)].GetPlatformType() == COLLECTABLES) {
				e_collisionFlag = 0;
				colliding = false;
				platform[abs(btmY)][abs(X1)].SetPlatformType(EMPTY_SPACE);
			}else{
				e_collisionFlag += COLLISION_TOP;
				Player.velocity.y -= Player.velocity.y;
			}

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
				Player.collideBotton = true;
			}
			//std::cout << "Btm collided \n";
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
					Player.collideBotton = true;
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
					Player.collideBotton = true;
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
			std::cout << "Right collided \n";
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
					Player.collideBotton = true;
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					platform[abs(Y1)][abs(leftX)].SetPlatformType(EMPTY_SPACE);
					colliding = false;
					dragCoeff = airDrag;
					friction = 0.f;
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
					Player.collideBotton = true;
					break;
				case COLLECTABLES:
					e_collisionFlag = 0;
					platform[abs(Y2)][abs(leftX)].SetPlatformType(EMPTY_SPACE);
					colliding = false;
					dragCoeff = airDrag;
					friction = 0.f;
					std::cout << "3 \n";
					break;
				case EMPTY_SPACE:
					colliding = false;
					break;
				case GOAL:
					level1_state = WIN;
				}
			}
			std::cout << "Left collided \n";
		}
		if (!colliding) {
			//std::cout << " test 1 \n" << colliding;
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

	/*if (e_collisionFlag == COLLISION_TOP) {
		Player.position.y -= PLAYER_SIZE_Y / 4;
	}
	else if (e_collisionFlag == COLLISION_TOP + COLLISION_LEFT) {
		Player.position.y -= PLAYER_SIZE_Y / 4;
		Player.position.x += PLAYER_SIZE_X / 4;
	}
	else if (e_collisionFlag == COLLISION_TOP + COLLISION_RIGHT) {
		Player.position.y -= PLAYER_SIZE_Y / 4;
		Player.position.x -= PLAYER_SIZE_X / 4;
	}
	else if (e_collisionFlag == COLLISION_BOTTOM) {
		Player.position.y += PLAYER_SIZE_Y / 4;
	}
	else if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_LEFT) {
		Player.position.y += PLAYER_SIZE_Y / 4;
		Player.position.x += PLAYER_SIZE_X / 4;
	}
	else if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_RIGHT) {
		Player.position.y += PLAYER_SIZE_Y / 4;
		Player.position.x -= PLAYER_SIZE_X / 4;
	}
	else if (e_collisionFlag == COLLISION_LEFT) {
		Player.position.x += PLAYER_SIZE_X / 4;
	}
	else if (e_collisionFlag == COLLISION_RIGHT) {
		Player.position.x -= PLAYER_SIZE_X / 4;
	}*/

	
	if (e_collisionFlag == COLLISION_TOP) {
		Player.position.y = heightOffset - (topY+1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
	}
	if (e_collisionFlag == COLLISION_TOP + COLLISION_LEFT) {
		Player.position.y = heightOffset - (topY + 1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + (leftX + 1) * gridWidth + PLAYER_SIZE_X / 2.0f;
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
		Player.position.x = -widthOffset + (leftX + 1) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_RIGHT) {
		Player.position.y = heightOffset - btmY * gridHeight + (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_LEFT) {
		Player.position.x = -widthOffset + (leftX+1) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_RIGHT) {
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	




	/*
	if (e_collisionFlag == COLLISION_TOP) {
		Player.position.y -= (PLAYER_SIZE_Y / 4.0f);
		if (DEBUG) {
			std::cout << "Coordinates\n\n";
			std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
			std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
			std::cout << "        +\n";
			std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
			std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
		}
	}
	if (e_collisionFlag == COLLISION_TOP + COLLISION_LEFT) {
		Player.position.y = heightOffset - (topY + 1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + (leftX + 1) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_TOP + COLLISION_RIGHT) {
		Player.position.y = heightOffset - (topY + 1) * gridHeight - (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_BOTTOM) {
		Player.position.y += (PLAYER_SIZE_Y / 4.0f);
		if (DEBUG) {
			std::cout << "Coordinates\n\n";
			std::cout << "  [" << abs(X1) << "," << abs(topY) << "] " << "[" << abs(X2) << "," << abs(topY) << "]\n";
			std::cout << "[" << abs(leftX) << "," << abs(Y1) << "]     " << "[" << abs(rightX) << "," << abs(Y1) << "]\n";
			std::cout << "        +\n";
			std::cout << "[" << abs(leftX) << "," << abs(Y2) << "]     " << "[" << abs(rightX) << "," << abs(Y2) << "]\n";
			std::cout << "  [" << abs(X1) << "," << abs(btmY) << "] " << "[" << abs(X2) << "," << abs(btmY) << "]\n\n";
		}
	}
	if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_LEFT) {
		Player.position.y = heightOffset - btmY * gridHeight + (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + (leftX + 1) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_BOTTOM + COLLISION_RIGHT) {
		Player.position.y = heightOffset - btmY * gridHeight + (PLAYER_SIZE_Y / 2.0f);
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_LEFT) {
		Player.position.x = -widthOffset + (leftX + 1) * gridWidth + PLAYER_SIZE_X / 2.0f;
	}
	if (e_collisionFlag == COLLISION_RIGHT) {
		Player.position.x = -widthOffset + rightX * gridWidth - PLAYER_SIZE_X / 2.0f;
	}
	*/

	


	/*

	// Checking current location
	double width = -(WINDOW_WIDTH / 2.0f);
	double height = WINDOW_HEIGHT / 2.0f;
	int xCoord = 0, yCoord = 0;

	// Getting X coord in grid
	while (1) {
		if (playerX > width) {
			width += gridWidth;
			xCoord++;
		}
		else {
			xCoord -= 1;
			break;
		}
	}

	// Getting Y coord in grid
	while (1) {
		if (playerY < height) {
			height -= gridHeight;
			yCoord++;
		}
		else {
			yCoord -= 1;
			break;
		}
	}
	*/

	//std::cout << "Width Grid: " << xCoord + 1 << "\n";
	//std::cout << "Height Grid: " << yCoord + 1 << "\n";

	/*
	bool leftOfPlayerHit = false, rightOfPlayerHit = false, topOfPlayerHit = false, btmOfPlayerHit = false;

	// If on the left halve of a block
	if ((Player.position.x + PLAYER_SIZE_X / 2) > ((xCoord + 1) * gridWidth - WINDOW_WIDTH / 2.0f) && platform[yCoord][xCoord + 1].GetPlatformType() == 1) {
		rightOfPlayerHit = true;
	}
	// If on the right halve of a block
	if ((Player.position.x - PLAYER_SIZE_X / 2) < ((xCoord)*gridWidth - WINDOW_WIDTH / 2.0f) && platform[yCoord][xCoord - 1].GetPlatformType() == 1) {
		leftOfPlayerHit = true;
	}
	// If on the top of the block (Platform below you)
	if ((Player.position.y - PLAYER_SIZE_Y / 2) < (WINDOW_HEIGHT / 2.0f - (yCoord + 1) * gridHeight) && platform[yCoord + 1][xCoord].GetPlatformType() == 1) {
		btmOfPlayerHit = true;
	}
	// If on the btm of the block (Platform above you)
	if ((Player.position.y + PLAYER_SIZE_Y / 2) > (WINDOW_HEIGHT / 2.0f - (yCoord)*gridHeight) && platform[yCoord - 1][xCoord].GetPlatformType() == 1) {
		topOfPlayerHit = true;
	}

	// If collided, does smth (Switch case for diff surface)
	if (rightOfPlayerHit == true) { // Hit leftside of block
		Player.velocity.y = 0;
		Player.velocity.x = 0;
		Player.position.x = (xCoord + 1) * gridWidth - WINDOW_WIDTH / 2.0f - (PLAYER_SIZE / 2.0f);
		std::cout << "Player right bound hit block on the right\n";
	}
	if (leftOfPlayerHit == true) { // Hit rightside of block
		Player.velocity.y = 0;
		Player.velocity.x = 0;
		Player.position.x = xCoord * gridWidth - WINDOW_WIDTH / 2.0f + (PLAYER_SIZE / 2.0f);
		std::cout << "Player left bound hit block of the left\n";
	}

	if (btmOfPlayerHit == true) { // Hit floor(top side of block)
		Player.velocity.y = 0.0f;
		Player.position.y = WINDOW_HEIGHT / 2.0f - (yCoord + 1) * gridHeight + (PLAYER_SIZE / 2.0f);
		Player.collideBotton = true;
		std::cout << "Player btm bound hit floor\n";
	}

	if (topOfPlayerHit == true) { // Hit btm of block
		Player.velocity.y = 0;
		Player.position.y = WINDOW_HEIGHT / 2.0f - (yCoord)*gridHeight - (PLAYER_SIZE / 2.0f);
		std::cout << "Player top bound hit block above\n";
	}*/
}