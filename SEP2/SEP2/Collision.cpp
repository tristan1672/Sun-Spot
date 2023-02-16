// ---------------------------------------------------------------------------
// includes
#include "Collision.hpp"

extern DynamicObj Player;
extern Platform** platform;
// ----------------------------------------------------------------------------
// This function checks for player collsion 
// ----------------------------------------------------------------------------
void collisionCheck(float playerX, float playerY) {

	float gridWidth = WINDOW_WIDTH / BINARY_MAP_WIDTH;
	float gridHeight = WINDOW_HEIGHT / BINARY_MAP_HEIGHT;

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

	//std::cout << "Width Grid: " << xCoord + 1 << "\n";
	//std::cout << "Height Grid: " << yCoord + 1 << "\n";

	if (Player.velocity.y < -240.0f)
	{
		e_shakeStrength = HEAVY_SHAKE;
	}
	else if (Player.velocity.y < -140.0f)
	{
		e_shakeStrength = MEDIUM_SHAKE;
	}


	bool leftOfPlayerHit = false, rightOfPlayerHit = false, topOfPlayerHit = false, btmOfPlayerHit = false;

	// If on the left halve of a block
	if ((Player.position.x + PLAYER_SIZE / 2) > ((xCoord + 1) * gridWidth - WINDOW_WIDTH / 2.0f) && platform[yCoord][xCoord + 1].GetPlatformType() == 1) {
		rightOfPlayerHit = true;
	}
	// If on the right halve of a block
	if ((Player.position.x - PLAYER_SIZE / 2) < ((xCoord)*gridWidth - WINDOW_WIDTH / 2.0f) && platform[yCoord][xCoord - 1].GetPlatformType() == 1) {
		leftOfPlayerHit = true;
	}
	// If on the top of the block (Platform below you)
	if ((Player.position.y - PLAYER_SIZE / 2) < (WINDOW_HEIGHT / 2.0f - (yCoord + 1) * gridHeight) && platform[yCoord + 1][xCoord].GetPlatformType() == 1) {
		btmOfPlayerHit = true;
	}
	// If on the btm of the block (Platform above you)
	if ((Player.position.y + PLAYER_SIZE / 2) > (WINDOW_HEIGHT / 2.0f - (yCoord)*gridHeight) && platform[yCoord - 1][xCoord].GetPlatformType() == 1) {
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
	}


}