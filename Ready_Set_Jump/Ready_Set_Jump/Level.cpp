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

#include "Level.hpp"
#include "Collision.hpp"
#include "Timer.hpp"
#include "UI.hpp"
#include "Score.hpp"
#include "Cam.hpp"
//#include <vector>
#include<string>

// ---------------------------------------------------------------------------


#define GROUND_LEVEL 20
extern CameraPos cam;
mousePos mouse;
DynamicObj Player;
Platform** platform;
GameObject jumpArrow;
GameObject WinScreen;
GameObject Cleared;
std::string fileToLoad{"Assets/Script/Level2.txt"};

float e_deltaTime;
float e_levelTime;

Vector2D playerSpawnPoint;

int** e_levelGrid;
int e_binaryMapWidth;
int e_binaryMapHeight;
int e_totalNumOfCollectable;

int level1_state;
int level1_difficulty;

int gGameRunning = 1;
bool flick = false;
int jump_counter;

bool airCheck;

AEGfxTexture* ptex = nullptr;
AEGfxTexture* normalBlockTexture{ nullptr };
AEGfxTexture* iceBlockTexture{ nullptr };


int ImportMapDataFromFile(const char* FileName);

// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level_Load()
{
	MakeMesh();
	MakeArrowMesh();
	//MakeCircle();

	ptex = AEGfxTextureLoad("Assets/Images/Cleared.png");
	normalBlockTexture = AEGfxTextureLoad("Assets/Images/Basic_Platform.png");
	iceBlockTexture = AEGfxTextureLoad("Assets/Images/Ice_Platform.png");
	Cleared = GameObject({ 0.0f, 0.0f }, { 500.0f, 500.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
	Cleared.SetTexture(ptex);
	playerSpawnPoint.x = -520.f;
	playerSpawnPoint.y = 100.f;

	/*playerSpawnPoint.x = -570.f;
	playerSpawnPoint.y = 300.f;*/

	//playerSpawnPoint.x = -510.f;
	//playerSpawnPoint.y = 300.f;

	if (!ImportMapDataFromFile(fileToLoad.c_str())) {
		std::cout << "Level File opened\n";
	}

}
// ----------------------------------------------------------------------------
// This function initialize game object instances
// It is called once at the start of the state
// ----------------------------------------------------------------------------
void Level_Initialize()
{

	level1_state = PLAYING;
	level1_difficulty = EASY;
	e_levelTime = 0.0f;
	e_numOfCollectableCollected = 0;
	scoreInitialize();

#if DEBUG
	std::cout << "Total number of collectables: " << e_totalNumOfCollectable << "\n";
#endif

	// sets the array with informations needed for the platform's property
#pragma region set platform objects

	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {
			switch (platform[i][j].GetPlatformType())
			{
			case NORMAL_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(normalBlockTexture);
				break;
			case ICE_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(iceBlockTexture);
				break;
			case STICKY_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE }, { 1.f,0.98f,0.63f,1.f });
				break;
			case SLIME_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE }, { 0.19f,0.8f,0.19f,1.f });
				break;
			case COLLECTABLES:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ COLLECTABLE_SIZE_X, COLLECTABLE_SIZE_Y }, { 0.65f, 0.39f, 0.65f,1.f }, 0, AE_GFX_RM_COLOR, circleMesh);
				break;
			case CHECKPOINT:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y }, { 1.f, 0.65f, 0.f,1.f });
				break;
			case GOAL:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y }, { 0.9f, 0.2f, 0.2f,1.f });
				break;
			default:
				break;
			}
		}
	}

	Player = DynamicObj();
	Player.position = { playerSpawnPoint.x,playerSpawnPoint.y };
	Player.SetColour({ 0.f,1.f,1.f,1.f });
	Player.SetScale({ PLAYER_SIZE_X , PLAYER_SIZE_Y });
	jump_counter = 0;
#pragma endregion
	//sets the ui indicator for where the character is about to jump
	jumpArrow = GameObject({ 0.f,0.f }, { 10.f,100.f },
		{ 0.f,1.f,0.f,0.5f }, 0.f, AE_GFX_RM_COLOR, arrMesh);
	jumpArrow.SetScale({ 10.f,100.f });
	jumpArrow.SetColour({ 0.f,1.f,0.f,0.5f });
	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;
	airCheck = false;
	shake = false;
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level_Update()
{
	if (level1_state == PLAYING)
	{
		// Checks the current pos of the mouse when initially clicked
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
		}
		// Shows the direction of the player will initially jump on mouse release
		if (AEInputCheckCurr(AEVK_LBUTTON) && Player.jumpReady) {
			Input_Handle_HoldCheck();
		}
		// The player jumps in according to the direction previously specified, then resets all the rotations and click pos to 0;
		if (AEInputCheckReleased(AEVK_LBUTTON) && Player.jumpReady) {
			AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
			Input_Handle_Jump();
			jumpArrow.SetRotation(0);
			if (Player.velocity.x && Player.velocity.y) 	jump_counter++;
			mouse = { 0,0,0,0 };
		}
		if (AEInputCheckTriggered(AEVK_ESCAPE)) {
			next = GS_MAINMENU;
		}
	}

	if (level1_state == WIN)
	{
		if (AEInputCheckTriggered(AEVK_ESCAPE)) 
		{
			next = GS_MAINMENU;
		}
	}

	// Prev collesion flag check
	airCheck = Player.GetColFlag();

	// Collision function
	Player.LevelCollision();
	Player.SnapToGrid();
	ObjectiveCollision();

	std::cout << Player.velocity.y << "\n";


	//std::cout << Player.position.y <<'\n';
	//if (Player.position.x <  (-GRID_WIDTH_SIZE * e_binaryMapWidth * 0.5) || Player.position.x >(GRID_WIDTH_SIZE * e_binaryMapWidth * 0.5) || Player.position.y < (-GRID_HEIGHT_SIZE * e_binaryMapHeight * 0.5) || AEInputCheckTriggered(AEVK_Q)) //press 'q' to reset player position
	//{
	//	Player.position = { playerSpawnPoint.x,playerSpawnPoint.y };
	//	 = 0.0f;
	//	Player.velocity.x = 0.0f;
	//}

	// code that allows the player to get affected by gravity (might need to look back at it to improve)

	if (level1_state == PLAYING) {
		Player.PhysicsUpdate();
	}

	// Cam shake
	Cam(airCheck);

	// Update total time taken for level
	if (level1_state == PLAYING) {
		LevelTime();
		//if (e_levelTime > 60 * 60) {
			// Over 1 hr = lose/restart
		//}
	}

//#if DEBUG
//	std::cout << "\nShake Strength: " << e_shakeStrength << "\n";
//	std::cout << "Delta Time: " << e_deltaTime << "\n";
//	std::cout << "Level Time: " << e_levelTime << "\n\n";
//#endif
}

// ----------------------------------------------------------------------------
// This function sends data that needs to be drawn to the graphic engine
// It is called after update to show animation/movement
// ----------------------------------------------------------------------------
void Level_Draw()
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
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.jumpReady && currHoldTime >= MAX_HOLD_TIME) {
		jumpArrow.DrawObj();
	}

	if (level1_state == WIN) //draw win screen
	{

		WinScreen = GameObject();
		WinScreen.position = { cam.X, cam.Y };
		WinScreen.SetScale({ 1270.f, 720.f });
		WinScreen.SetColour({ 0.f,0.0f,0.f,0.9f });
		WinScreen.DrawObj();

		Cleared.SetPosition({ cam.X , cam.Y + 100.0f });
		Cleared.DrawObj();
		PrintScore(jump_counter, level1_difficulty);

	}
	else {
		// Draws total time in current level
		DisplayTime(0.58f, 0.86f);
	}
}

// ----------------------------------------------------------------------------
// This function frees objects instances
// It is called after to prepare the state to be unloaded or initialized again
// ----------------------------------------------------------------------------
void Level_Free()
{

}

// ----------------------------------------------------------------------------
// This function dumps all loaded during Level1_Load()
// It is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level_Unload()
{
	for (int i = 0; i < e_binaryMapHeight; i++) {
		delete[] platform[i];
	}
	delete[] platform;
	AEGfxTextureUnload(normalBlockTexture);
	AEGfxTextureUnload(ptex);
	AEGfxMeshFree(pMesh);
	AEGfxMeshFree(arrMesh);
}


// Functions

int ImportMapDataFromFile(const char* FileName) {

	std::fstream levelMap(FileName, std::ios_base::in);

	if (levelMap.is_open()) {
#if DEBUG
		std::cout << FileName << " is opened\n";
#endif

		std::string temp;
		std::getline(levelMap, temp);
		std::string::size_type start = temp.find_first_of("0123456789");
		std::string::size_type end = temp.find_first_of('\n');
		std::string subStr = temp.substr(start, end - start);
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
	}
	else {
#if DEBUG
		std::cout << "File Cannot be opened\n";
#endif
		return 0;
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
	return 1;
}