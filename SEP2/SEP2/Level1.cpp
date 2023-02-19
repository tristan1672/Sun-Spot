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
#include "Collision.hpp"
//#include <vector>
#include<string>

// ---------------------------------------------------------------------------


#define GROUND_LEVEL 20

mousePos mouse;
DynamicObj Player;
Platform **platform;
//GameObject platform[BINARY_MAP_HEIGHT][BINARY_MAP_WIDTH]{};
GameObject jumpArrow;

int** e_levelGrid;
int BINARY_MAP_WIDTH;
int BINARY_MAP_HEIGHT;



int gGameRunning = 1;
bool flick = false;

CameraPos cam;
bool shake;
short e_shakeStrength;

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
	std::fstream levelMap("Assets/Script/Level1.txt", std::ios_base::in);

	if (levelMap.is_open()) {
		std::cout << "Level File opened\n";
		std::string temp;
		std::getline(levelMap, temp);
		std::string::size_type start = temp.find_first_of("0123456789");
		std::string::size_type end = temp.find_first_of('\n');
		std::string subStr = temp.substr(start,end-start);
		BINARY_MAP_WIDTH = std::stoi(subStr);

		std::getline(levelMap, temp);
		start = temp.find_first_of("0123456789");
		end = temp.find_first_of('\n');
		subStr = temp.substr(start, end - start);
		BINARY_MAP_HEIGHT = std::stoi(subStr);

		std::cout << "Width :" << BINARY_MAP_WIDTH << '\n';
		std::cout << "Height :" << BINARY_MAP_HEIGHT << '\n';


		//e_levelGrid = new int* [BINARY_MAP_HEIGHT];
		//for (int i = 0; i < BINARY_MAP_HEIGHT; ++i) {
		//	e_levelGrid[i] = new int[BINARY_MAP_WIDTH];
		//}


		platform = new Platform * [BINARY_MAP_HEIGHT] {};
		for (int i = 0; i < BINARY_MAP_HEIGHT; i++) {
			platform[i] = new Platform[BINARY_MAP_WIDTH]{};
		}

		char character = 0;
		int i = 0, j = 0;
		while (levelMap.get(character)) {

			if (character >= '0' && character <= '9')
			{
				platform[i][j].SetPlatformType(static_cast<int>(character) - '0');
					std::cout << platform[i][j].GetPlatformType();

				j++;

				if (j == BINARY_MAP_WIDTH) {
					std::cout << "	Row " << i << "\n";
					j = 0;
					i++;

					if (i == BINARY_MAP_HEIGHT) {
						break;
					}
				}
			}
			//std::cout << character;

		}

		levelMap.close();
	}
	else {
		std::cout << "Level File Cannot be opened\n";
		exit(0);
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
	Player.position = { 0,PLAYER_SIZE_Y/2 };
	Player.SetColour({ 0.f,1.f,1.f,1.f });
	Player.SetScale({ PLAYER_SIZE_X , PLAYER_SIZE_Y });
	// sets the array with informations needed for the platform's property
#pragma region set platform objects

	float gridWidth = WINDOW_WIDTH / BINARY_MAP_WIDTH;
	float gridHeight = WINDOW_HEIGHT / BINARY_MAP_HEIGHT;

	for (int i = 0; i < BINARY_MAP_HEIGHT; i++) {
		for (int j = 0; j < BINARY_MAP_WIDTH; j++) {
			switch (platform[i][j].GetPlatformType())
			{
			case NORMAL_BLOCK:
				platform[i][j] = Platform(
					{ gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * gridWidth, -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * gridHeight },
					{ gridWidth, gridHeight });
				break;
			case ICE_BLOCK:
				platform[i][j] = Platform(
					{ gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * gridWidth, -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * gridHeight },
					{ gridWidth, gridHeight }, {0.47f,0.76f,0.93f,1.f});
				break;
			case STICKY_BLOCK:
				platform[i][j] = Platform(
					{ gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * gridWidth, -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * gridHeight },
					{ gridWidth, gridHeight }, { 1.f,0.98f,0.63f,1.f });
				break;
			case COLLECTABLES:
				platform[i][j] = Platform(
					{ gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * gridWidth, -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * gridHeight },
					{ PLAYER_SIZE_X, PLAYER_SIZE_Y }, { 0.65f, 0.39f, 0.65f,1.f });
				break;
			default:
				break;
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
	e_shakeStrength = NO_SHAKE;
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

	// Checks the current pos of the mouse when initially clicked
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
	}
	//shows the direction of the player will initially jump on mouse release(will have to revise this part as it is based off jump force, might want to change it later to base off time held)
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.collideBotton) {
		Input_Handle_HoldCheck();
		if (e_jumpForce <= min_jumpForce) {
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

	collisionCheck(Player.position.x, Player.position.y); //collision function
	//std::cout << Player.position.y <<'\n';
	if (Player.position.x <  (-WINDOW_WIDTH / 2) || Player.position.x >(WINDOW_WIDTH / 2) || Player.position.y < (-WINDOW_HEIGHT) || AEInputCheckTriggered(AEVK_Q)) //press 'q' to reset player position
	{
		Player.position.x = 0.0f;
		Player.position.y = 10.0f;
		Player.velocity.y = 0.0f;
		Player.velocity.x = 0.0f;
	}

	// code that allows the player to get affected by gravity (might need to look back at it to improve)
	float terminalVelocity{ 2.f * e_gravity / dragCoeff };
	if (terminalVelocity < Player.velocity.y) {
		Player.velocity.y += static_cast<float>(vertMod * e_gravity * AEFrameRateControllerGetFrameTime());
	}
	if (Player.velocity.y) {
		Player.velocity.y -= static_cast<float>(dragCoeff * Player.velocity.y * AEFrameRateControllerGetFrameTime());
	}
	if (abs(Player.velocity.x) < 2.f) {
		Player.velocity.x = 0;
	}
	if (Player.velocity.x && friction != fullStopFriction) {
		Player.velocity.x -= static_cast<float>(friction * Player.velocity.x * AEFrameRateControllerGetFrameTime());
	}
	else if (Player.velocity.x && friction == fullStopFriction) {
		Player.velocity.x -= static_cast<float>(Player.velocity.x);
	}

	Player.position.y += static_cast<float>(Player.velocity.y * AEFrameRateControllerGetFrameTime());
	Player.position.x += static_cast<float>(Player.velocity.x * AEFrameRateControllerGetFrameTime());

	AEGfxSetCamPosition(Player.position.x, cam.Y); //set camera to follow player
	//cam shake
	if (!Player.collideBotton) //set shake and shaketime
	{
		shake = 1;
		shaketime = 0;
		e_shakeStrength = NO_SHAKE;
	}

	if (shake == 1 && (Player.collideBotton) && (shaketime < 0.2f)) //shake conditions
	{	
		shakespeed = 1.0f;
		shaketime += AEFrameRateControllerGetFrameTime();
		float distance = cam.Y - Player.position.y;
		if (shakespeed >= 0)
		{
			if (e_shakeStrength == HEAVY_SHAKE)
			{
				shakespeed = 500.0f;
			}
			else if (e_shakeStrength == MEDIUM_SHAKE)
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

	float gridWidth = WINDOW_WIDTH / BINARY_MAP_WIDTH;
	float gridHeight = WINDOW_HEIGHT / BINARY_MAP_HEIGHT;
	//draws the platform
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++) {
		for (int j = 0; j < BINARY_MAP_WIDTH; j++) {
			if (platform[i][j].GetPlatformType()) {
				platform[i][j].DrawObj();
			}
		}
	}
	//draws the player
	Player.DrawObj();
	//draws the arrow direction
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.collideBotton && e_jumpForce <= min_jumpForce) {
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
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++) {
		delete[] platform[i];
	}
	delete[] platform;

}

// ----------------------------------------------------------------------------
// This function dumps all loaded during Level1_Load()
// It is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{
	std::cout << "Level 1:Unload\n";
}
