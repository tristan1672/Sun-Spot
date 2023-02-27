/*
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
#include "Timer.hpp"
#include "UIUtilities.hpp"
//#include <vector>
#include<string>

// ---------------------------------------------------------------------------


#define GROUND_LEVEL 20

mousePos mouse;
extern DynamicObj Player;
extern Platform **platform;
GameObject jumpArrow;
GameObject WinScreen;
GameObject Cleared;

float e_deltaTime;
float e_levelTime;

int** e_levelGrid;
int e_binaryMapWidth;
int e_binaryMapHeight;
int e_totalNumOfCollectable;

int level1_state;
int level1_difficulty;

int gGameRunning = 1;
bool flick = false;
int jump_counter;

CameraPos cam;
bool shake;
short e_shakeStrength;
float shakespeed;
float shakedistance;
f64 shaketime;

AEGfxTexture* ptex = nullptr;

// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level1_Load()
{
	MakeMesh();
	MakeArrowMesh();
	MakeCircle();

	ptex = AEGfxTextureLoad("Assets/Cleared.png");
	Cleared = GameObject({ 0.0f, 0.0f }, { 500.0f, 500.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.0f, AE_GFX_RM_TEXTURE);
	Cleared.SetTexture(ptex);

	e_totalNumOfCollectable = 0;

	std::cout << "Level 1:Load\n";
	std::fstream levelMap("Assets/Script/Level1.txt", std::ios_base::in);
	//std::fstream levelMap("Assets/Script/Testing.txt", std::ios_base::in);

	if (levelMap.is_open()) {
		std::cout << "Level File opened\n";
		std::string temp;

		std::getline(levelMap, temp);
		std::string::size_type start = temp.find_first_of("0123456789");
		std::string::size_type end = temp.find_first_of('\n');
		std::string subStr = temp.substr(start,end-start);
		e_binaryMapWidth = std::stoi(subStr);

		std::getline(levelMap, temp);
		start = temp.find_first_of("0123456789");
		end = temp.find_first_of('\n');
		subStr = temp.substr(start, end - start);
		e_binaryMapHeight = std::stoi(subStr);

#if DEBUG
		std::cout << "Width :" << e_binaryMapWidth << '\n';
		std::cout << "Height :" << e_binaryMapHeight << '\n';
#endif

		platform = new Platform * [e_binaryMapHeight] {};
		for (int i = 0; i < e_binaryMapHeight; i++) {
			platform[i] = new Platform[e_binaryMapWidth]{};
		}

		char character = 0;
		int i = 0, j = 0;
		while (levelMap.get(character)) {

			if (character >= '0' && character <= '9')
			{
				if (character == '9') {
					++e_totalNumOfCollectable;
				}

				platform[i][j].SetPlatformType(static_cast<int>(character) - '0');
#if DEBUG
				std::cout << platform[i][j].GetPlatformType();
#endif

				j++;

				if (j == e_binaryMapWidth) {
#if DEBUG
					std::cout << "	Row " << i << "\n";
#endif
					j = 0;
					i++;

					if (i == e_binaryMapHeight) {
						break;
					}
				}
			}
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

	level1_state = PLAYING;
	level1_difficulty = EASY;
	e_levelTime = 0.0f;

	Player = DynamicObj();
	Player.position = { 0,PLAYER_SIZE_Y/2 };
	Player.SetColour({ 0.f,1.f,1.f,1.f });
	Player.SetScale({ PLAYER_SIZE_X , PLAYER_SIZE_Y });
	jump_counter = 0;

	float s_gridWidth = WINDOW_WIDTH / e_binaryMapWidth;
	float s_gridHeight = WINDOW_HEIGHT / e_binaryMapHeight;

//#if DEBUG
	std::cout << "Total number of collectables: " << e_totalNumOfCollectable << "\n";
//#endif

	// sets the array with informations needed for the platform's property
#pragma region set platform objects

	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {
			switch (platform[i][j].GetPlatformType())
			{
			case NORMAL_BLOCK:
				platform[i][j] = Platform(
					{ s_gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * s_gridWidth, -s_gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * s_gridHeight },
					{ s_gridWidth, s_gridHeight });
				break;
			case ICE_BLOCK:
				platform[i][j] = Platform(
					{ s_gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * s_gridWidth, -s_gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * s_gridHeight },
					{ s_gridWidth, s_gridHeight }, {0.47f,0.76f,0.93f,1.f});
				break;
			case STICKY_BLOCK:
				platform[i][j] = Platform(
					{ s_gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * s_gridWidth, -s_gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * s_gridHeight },
					{ s_gridWidth, s_gridHeight }, { 1.f,0.98f,0.63f,1.f });
				break;
			case SLIME_BLOCK:
				platform[i][j] = Platform(
					{ s_gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * s_gridWidth, -s_gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * s_gridHeight },
					{ s_gridWidth, s_gridHeight }, { 0.19f,0.8f,0.19f,1.f });
				break;
			case COLLECTABLES:
				platform[i][j] = Platform(
					{ s_gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * s_gridWidth, -s_gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * s_gridHeight },
					{ COLLECTABLE_SIZE_X, COLLECTABLE_SIZE_Y }, { 0.65f, 0.39f, 0.65f,1.f },0,AE_GFX_RM_COLOR,circleMesh);
				break;
			case GOAL:
				platform[i][j] = Platform(
					{ s_gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * s_gridWidth, -s_gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * s_gridHeight },
					{ GOAL_SIZE_X, GOAL_SIZE_Y }, { 0.9f, 0.2f, 0.2f,1.f });
				break;
			default:
				break;
			}
		}
	}
#pragma endregion
	//sets the ui indicator for where the character is about to jump
	jumpArrow = GameObject({ 0.f,0.f }, { 10.f,100.f }, 
		{ 0.f,1.f,0.f,0.5f },0.f, AE_GFX_RM_COLOR,arrMesh);
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
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level1_Update()
{
	if (level1_state == PLAYING)
	{
		// Checks the current pos of the mouse when initially clicked
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);

		}
		// Shows the direction of the player will initially jump on mouse release(will have to revise this part as it is based off jump force, might want to change it later to base off time held)
		if (AEInputCheckCurr(AEVK_LBUTTON) && Player.jumpReady) {
			Input_Handle_HoldCheck();
			AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
			Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ReleaseX) - WINDOW_WIDTH / 2.f + Player.position.x, -(static_cast<float>(mouse.ReleaseY) - WINDOW_HEIGHT / 2.f) + Player.position.y };
			Vector2D nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
			float angle = atan2f(-nDirection.x, nDirection.y);
			if (currHoldTime >= maxHoldTime) {
				jumpArrow.position = { Player.position.x,Player.position.y };
				nDirection = normalDirection(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
				angle = atan2f(-nDirection.x, -nDirection.y);
				currHoldDistance = Distance(Player.position.x, Player.position.y, mouseClickQuadPos.x, mouseClickQuadPos.y);
				if (currHoldDistance > maxHoldDistance) {
					currHoldDistance = maxHoldDistance;
				}
				if (currHoldDistance < minHoldDistance) {
					currHoldDistance = minHoldDistance;
				}
				currHoldDistance *= e_jumpForceMod;
				jumpArrow.SetScale({ jumpArrow.GetScale().x,currHoldDistance });
				jumpArrow.SetRotation(angle);
			}
		}
		// The player jumps in according to the direction previously specified, then resets all the rotations and click pos to 0;
		if (AEInputCheckReleased(AEVK_LBUTTON) && Player.jumpReady) {
			AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
			Input_Handle_Jump();
			jumpArrow.SetRotation(0);
			if (Player.velocity.x && Player.velocity.y) 	jump_counter++;
			mouse = { 0,0,0,0 };
		}
	}

	// Collision function
	LevelCollision();
	ObjectiveCollision();

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
	if (level1_state == PLAYING) {
		if (terminalVelocity < Player.velocity.y) {
			Player.velocity.y += static_cast<float>(vertMod * e_gravity * e_deltaTime);
		}
		if (Player.velocity.y) {
			Player.velocity.y -= static_cast<float>(dragCoeff * Player.velocity.y * e_deltaTime);
		}
		if (abs(Player.velocity.x) < 2.f) {
			Player.velocity.x = 0;
		}
		if (Player.velocity.x && friction != fullStopFriction) {
			Player.velocity.x -= static_cast<float>(friction * Player.velocity.x * e_deltaTime);
		}
		else if (Player.velocity.x && friction == fullStopFriction) {
			Player.velocity.x -= static_cast<float>(Player.velocity.x);
		}

		Player.position.y += static_cast<float>(Player.velocity.y * e_deltaTime);
		Player.position.x += static_cast<float>(Player.velocity.x * e_deltaTime);
	}

	// Set camera to follow player
	AEGfxSetCamPosition(Player.position.x, cam.Y);

	// Cam shake
	if (!Player.jumpReady) // set shake and shaketime
	{
		shake = 1;
		shaketime = 0;
		e_shakeStrength = NO_SHAKE;
	}

	// shake conditions
	if (shake == 1 && (Player.jumpReady) && (shaketime < 0.2f)) 
	{
		shakespeed = 1.0f;
		shaketime += e_deltaTime;
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
	
	cam.Y = Player.position.y + shakespeed * e_deltaTime;

	// Update total time taken for level
	if (level1_state == PLAYING) {
		LevelTime();
	}

#if DEBUG
		std::cout << "\nShake Strength: " << e_shakeStrength << "\n";
		std::cout << "Delta Time: " << e_deltaTime << "\n";
		std::cout << "Level Time: " << e_levelTime << "\n\n";
#endif
}

// ----------------------------------------------------------------------------
// This function sends data that needs to be drawn to the graphic engine
// It is called after update to show animation/movement
// ----------------------------------------------------------------------------
void Level1_Draw()
{

	// Set the background to black.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Draws the platform
	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {
			if (platform[i][j].GetPlatformType()) {
				platform[i][j].DrawObj();
			}
		}
	}
	// Draws the player
	Player.DrawObj();
	// Draws the arrow direction
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.jumpReady && currHoldTime >= maxHoldTime) {
		jumpArrow.DrawObj();
	}

	if (level1_state == WIN) //draw win screen
	{

		WinScreen = GameObject();
		WinScreen.position = { 0.0f, 0.0f };
		WinScreen.SetScale({ 1270.f, 720.f });
		WinScreen.SetColour({ 0.f,0.0f,0.f,0.7f });
		WinScreen.DrawObj();

		Cleared.SetPosition({ Player.position.x , Player.position.y });
		Cleared.DrawObj();
		PrintScore(e_numOfCollectableCollected, jump_counter, level1_difficulty);

	}
	else {
		// Draws total time in current level
		DisplayTime();
	}
}

// ----------------------------------------------------------------------------
// This function frees objects instances
// It is called after to prepare the state to be unloaded or initialized again
// ----------------------------------------------------------------------------
void Level1_Free()
{
	std::cout << "Level 1:Free\n";
	for (int i = 0; i < e_binaryMapHeight; i++) {
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
	AEGfxTextureUnload(ptex);
	AEGfxMeshFree(pMesh);
	AEGfxMeshFree(arrMesh);
}
