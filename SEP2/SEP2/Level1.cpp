/**
  *  \file Level1.cpp (might need to change this file name later)
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  the basic logics to our levels and the game states, loops for our game
  *
*/

// ---------------------------------------------------------------------------
// includes
#pragma once

#include "Level1.hpp"

// ---------------------------------------------------------------------------


#define GROUND_LEVEL 20
static int s_levelGrid[GRID_SIZE][GRID_SIZE];
mousePos mouse;
DynamicObj Player;
GameObject platform[GRID_SIZE][GRID_SIZE];
GameObject jumpArrow;



int gGameRunning = 1;
bool flick = false;

CameraPos cam;
bool heavyshake, mediumshake;
bool shake;
float shakespeed;
float shakedistance;
f64 shaketime;



// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level1_Load()
{
	std::cout << "Level 1:Load\n";
	std::fstream level1Map("Assets/Script/Level1.txt", std::ios_base::in);

	if (level1Map.is_open()) {
		std::cout << "Level 1 File opened\n";
	}
	else {
		std::cout << "Level 1 File Cannot be opened\n";
		exit(0);
	}

	char character = 0;
	int i = 0, j = 0;
	while (level1Map.get(character)) {

		if (j == GRID_SIZE) {
			j = 0;
			i++;

			if (i == GRID_SIZE) {
				break;
			}
		}

		if (character == '0' || character == '1') {
			s_levelGrid[i][j] = static_cast<int>(character) - 48;
			j++;
		}

		//std::cout << character;

	}

}

// ----------------------------------------------------------------------------
// This function initialize game object instances
// It is called once at the start of the state
// ----------------------------------------------------------------------------
void Level1_Initialize()
{
	std::cout << "Level 1:Initialize\n";

	Player = DynamicObj();
	Player.position = { 0,10 };
	Player.SetColour({ 0.f,1.f,1.f,1.f });

	// sets the array with informations needed for the platform's property
#pragma region set platform objects

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (s_levelGrid[i][j] == 1) {
				platform[i][j] = GameObject(
					{ gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * (WINDOW_WIDTH / GRID_SIZE), -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * (WINDOW_HEIGHT / GRID_SIZE) },
					{ gridWidth, gridHeight });


			}
		}
	}
#pragma endregion
	//sets the ui indicator for where the character is about to jump
	jumpArrow = GameObject();
	jumpArrow.SetScale({ 10.f,100.f });
	jumpArrow.SetColour({ 0.f,1.f,0.f,0.5f });
	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;

	shake = false;
	heavyshake = false;
	mediumshake = false;
	shakespeed = 0.0f;
	shakedistance = 0.5f;
	
	MakeMesh();
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level1_Update()
{
	// code that allows the player to get affected by gravity (might need to look back at it to improve)
	if (!Player.collideBotton) {
		Player.velocity.y += static_cast<float>(e_gravity * AEFrameRateControllerGetFrameTime());
		Player.position.y += static_cast<float>(Player.velocity.y * AEFrameRateControllerGetFrameTime());
		Player.position.x += static_cast<float>(Player.velocity.x * AEFrameRateControllerGetFrameTime());
	}
	// Checks the current pos of the mouse when initially clicked
	if (AEInputCheckTriggered(AEVK_LBUTTON) && Player.collideBotton) {
		AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
	}
	//shows the direction of the player will initially jump on mouse release(will have to revise this part as it is based off jump force, might want to change it later to base off time held)
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.collideBotton) {
		Input_Handle_HoldCheck();
		if (e_jumpForce <= 100) {
			AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
			Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ClickX) - WINDOW_WIDTH / 2.f + Player.position.x, -(static_cast<float>(mouse.ClickY) - WINDOW_HEIGHT / 2.f) + Player.position.y };
			Vector2D nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
			float angle = atan2f(-nDirection.x, nDirection.y);
			std::cout << angle;
			jumpArrow.SetRotation(angle);
			jumpArrow.position = { mouseClickQuadPos.x,mouseClickQuadPos.y };
			std::cout << mouse.ReleaseY << "\n";
		}
	}
	// the player jumps in according to the direction previously specified, then resets all the rotations and click pos to 0;
	if (AEInputCheckReleased(AEVK_LBUTTON) && Player.collideBotton) {
		AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
		Input_Handle_Jump();
		jumpArrow.SetRotation(0);
		mouse = { 0,0,0,0 };
	}

	AEGfxSetCamPosition(Player.position.x, cam.Y); //set camera to follow player
	collisionCheck(Player.position.x, Player.position.y); //collision function


	if (Player.position.x <  (-WINDOW_WIDTH / 2) || Player.position.x >(WINDOW_WIDTH / 2) || Player.position.y < (-WINDOW_HEIGHT) || AEInputCheckTriggered(AEVK_Q)) //press 'q' to reset player position
	{
		Player.position.x = 0.0f;
		Player.position.y = 10.0f;
		Player.velocity.y = 0.0f;
		Player.velocity.x = 0.0f;
	}

	//cam shake
	if (!Player.collideBotton) //set shake and shaketime
	{
		shake = 1;
		shaketime = 0;
		heavyshake = false;
		mediumshake = false;
	}

	if (shake == 1 && (Player.collideBotton) && (shaketime < 0.2f)) //shake conditions
	{	
		shakespeed = 1.0f;
		shaketime += AEFrameRateControllerGetFrameTime();
		float distance = cam.Y - Player.position.y;
		if (shakespeed >= 0)
		{
			if (heavyshake == true)
			{
				shakespeed = 500.0f;
			}
			else if (mediumshake == true)
			{
				shakespeed = 100.0f;
			}
			else
			{
				shakespeed = 0.0f;
			}

			if (distance > shakedistance)
			{
				shakespeed *= -1.0f;
			}
		}
		else
		{
			if (distance < -shakedistance)
			{
				shakespeed *= -1.0f;
			}
		}
	}
	cam.Y = Player.position.y + shakespeed * AEFrameRateControllerGetFrameTime();
	
}

// ----------------------------------------------------------------------------
// This function sends data that needs to be drawn to the graphic engine
// It is called after update to show animation/movement
// ----------------------------------------------------------------------------
void Level1_Draw()
{

	// Set the background to black.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;
	//draws the platform
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (s_levelGrid[i][j] == 1) {
				platform[i][j].DrawObj();
			}
		}
	}
	//draws the player
	Player.DrawObj();
	//draws the arrow direction
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.collideBotton && e_jumpForce <= 100) {
		jumpArrow.DrawObj();
	}
}

// ----------------------------------------------------------------------------
// This function frees objects instances
// It is called after to prepare the state to be unloaded or initialized again
// ----------------------------------------------------------------------------
void Level1_Free()
{
	std::cout << "Level 1:Free\n";
}

// ----------------------------------------------------------------------------
// This function dumps all loaded during Level1_Load()
// It is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{
	std::cout << "Level 1:Unload\n";
}

// ----------------------------------------------------------------------------
// This function checks for player collsion 
// ----------------------------------------------------------------------------
void collisionCheck(float playerX, float playerY) {

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

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
		heavyshake = true;
	}
	else if (Player.velocity.y < -140.0f)
	{
		mediumshake = true;
	}
	

	bool leftOfPlayerHit = false, rightOfPlayerHit = false, topOfPlayerHit = false, btmOfPlayerHit = false;
	
	// If on the left halve of a block
	if ((Player.position.x + PLAYER_SIZE / 2) > ((xCoord + 1) * gridWidth - WINDOW_WIDTH / 2.0f) && s_levelGrid[yCoord][xCoord+1] == 1) {
		rightOfPlayerHit = true;
	}
	// If on the right halve of a block
	if ((Player.position.x - PLAYER_SIZE / 2) < ((xCoord) * gridWidth - WINDOW_WIDTH / 2.0f) && s_levelGrid[yCoord][xCoord-1] == 1) {
		leftOfPlayerHit = true;
	}
	// If on the top of the block (Platform below you)
	if ((Player.position.y - PLAYER_SIZE / 2) < (WINDOW_HEIGHT / 2.0f - (yCoord + 1) * gridHeight) && s_levelGrid[yCoord+1][xCoord] == 1) {
		btmOfPlayerHit = true;
	}
	// If on the btm of the block (Platform above you)
	if ((Player.position.y + PLAYER_SIZE / 2) > (WINDOW_HEIGHT / 2.0f - (yCoord) * gridHeight) && s_levelGrid[yCoord-1][xCoord] == 1) {
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
		Player.position.y = WINDOW_HEIGHT / 2.0f - (yCoord) * gridHeight - (PLAYER_SIZE / 2.0f);
		std::cout << "Player top bound hit block above\n";
	}


}