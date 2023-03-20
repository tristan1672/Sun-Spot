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
static int frameCounter;

Vector2D playerSpawnPoint;

int** e_levelGrid;
int e_binaryMapWidth;
int e_binaryMapHeight;
int e_totalNumOfcollectible;

int level1_state;
int level1_difficulty;

int gGameRunning = 1;
bool flick = false;
int jump_counter;

bool airCheck;

AEGfxTexture* ptex{ nullptr };
AEGfxTexture* normalBlockTexture{ nullptr };
AEGfxTexture* iceBlockTexture{ nullptr };
AEGfxTexture* stickyBlockTexture{ nullptr };
AEGfxTexture* slimeBlockTexture1{ nullptr };
AEGfxTexture* slimeBlockTexture2{ nullptr };
AEGfxTexture* slimeBlockTexture3{ nullptr };
AEGfxTexture* slimeBlockTextureFlipped1{ nullptr };
AEGfxTexture* slimeBlockTextureFlipped2{ nullptr };
AEGfxTexture* slimeBlockTextureFlipped3{ nullptr };

AEGfxTexture* collectibleTexture{ nullptr };
AEGfxTexture* goalTexture1{ nullptr };
AEGfxTexture* goalTexture2{ nullptr };
AEGfxTexture* goalTexture3{ nullptr };
AEGfxTexture* goalTexture4{ nullptr };
AEGfxTexture* goalTexture5{ nullptr };
AEGfxTexture* goalTexture6{ nullptr };
AEGfxTexture* goalTexture7{ nullptr };
AEGfxTexture* goalTexture8{ nullptr };
AEGfxTexture* goalTexture9{ nullptr };
AEGfxTexture* goalTexture10{ nullptr };
AEGfxTexture* goalTexture11{ nullptr };
AEGfxTexture* goalTexture12{ nullptr };
AEGfxTexture* goalTexture13{ nullptr };
AEGfxTexture* goalTexture14{ nullptr };
AEGfxTexture* goalTexture15{ nullptr };
AEGfxTexture* goalTexture16{ nullptr };
AEGfxTexture* goalTexture17{ nullptr };
AEGfxTexture* goalTexture18{ nullptr };
AEGfxTexture* goalTexture19{ nullptr };
AEGfxTexture* goalTexture20{ nullptr };


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
	stickyBlockTexture = AEGfxTextureLoad("Assets/Images/Sticky_Platform.png");
	slimeBlockTexture1 = AEGfxTextureLoad("Assets/Images/Slime_Platform_1.png");
	slimeBlockTexture2 = AEGfxTextureLoad("Assets/Images/Slime_Platform_2.png");
	slimeBlockTexture3 = AEGfxTextureLoad("Assets/Images/Slime_Platform_3.png");
	slimeBlockTextureFlipped1 = AEGfxTextureLoad("Assets/Images/Slime_Platform_1(Flipped).png");
	slimeBlockTextureFlipped2 = AEGfxTextureLoad("Assets/Images/Slime_Platform_2(Flipped).png");
	slimeBlockTextureFlipped3 = AEGfxTextureLoad("Assets/Images/Slime_Platform_3(Flipped).png");

	collectibleTexture = AEGfxTextureLoad("Assets/Images/Collectible.png");
	goalTexture1 = AEGfxTextureLoad("Assets/Images/Portal_1.png");
	goalTexture2 = AEGfxTextureLoad("Assets/Images/Portal_2.png");
	goalTexture3 = AEGfxTextureLoad("Assets/Images/Portal_3.png");
	goalTexture4 = AEGfxTextureLoad("Assets/Images/Portal_4.png");
	goalTexture5 = AEGfxTextureLoad("Assets/Images/Portal_5.png");
	goalTexture6 = AEGfxTextureLoad("Assets/Images/Portal_6.png");
	goalTexture7 = AEGfxTextureLoad("Assets/Images/Portal_7.png");
	goalTexture8 = AEGfxTextureLoad("Assets/Images/Portal_8.png");
	goalTexture9 = AEGfxTextureLoad("Assets/Images/Portal_9.png");
	goalTexture10 = AEGfxTextureLoad("Assets/Images/Portal_10.png");
	goalTexture11 = AEGfxTextureLoad("Assets/Images/Portal_11.png");
	goalTexture12 = AEGfxTextureLoad("Assets/Images/Portal_12.png");
	goalTexture13 = AEGfxTextureLoad("Assets/Images/Portal_13.png");
	goalTexture14 = AEGfxTextureLoad("Assets/Images/Portal_14.png");
	goalTexture15 = AEGfxTextureLoad("Assets/Images/Portal_15.png");
	goalTexture16 = AEGfxTextureLoad("Assets/Images/Portal_16.png");
	goalTexture17 = AEGfxTextureLoad("Assets/Images/Portal_17.png");
	goalTexture18 = AEGfxTextureLoad("Assets/Images/Portal_18.png");
	goalTexture19 = AEGfxTextureLoad("Assets/Images/Portal_19.png");
	goalTexture20 = AEGfxTextureLoad("Assets/Images/Portal_20.png");


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
	e_numOfcollectibleCollected = 0;
	scoreInitialize();

#if DEBUG
	std::cout << "Total number of COLLECTIBLES: " << e_totalNumOfcollectible << "\n";
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
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(stickyBlockTexture);
				break;

			case SLIME_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });

				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				if (platform[i][j - 1].GetPlatformType() != SLIME_BLOCK && platform[i][j + 1].GetPlatformType() != SLIME_BLOCK) {
					platform[i][j].SetTexture(slimeBlockTexture2);
				}
				else if (platform[i][j - 1].GetPlatformType() != SLIME_BLOCK) {
					platform[i][j].SetTexture(slimeBlockTexture1);
				}
				else {
					platform[i][j].SetTexture(slimeBlockTexture3);
				}

				break;

			case COLLECTIBLES:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ collectible_SIZE_X, collectible_SIZE_Y }, { 0.65f, 0.39f, 0.65f,1.f }, 0, AE_GFX_RM_COLOR, circleMesh);
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(collectibleTexture);
				break;

			case CHECKPOINT:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y }, { 1.f, 0.65f, 0.f,1.f });
				break;

			case GOAL:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(goalTexture1);
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


	PlatformAnimationUpdate();
	++frameCounter;



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
	
	AEGfxTextureUnload(ptex);
	AEGfxTextureUnload(normalBlockTexture);
	AEGfxTextureUnload(iceBlockTexture);
	AEGfxTextureUnload(stickyBlockTexture);
	AEGfxTextureUnload(slimeBlockTexture1);
	AEGfxTextureUnload(slimeBlockTexture2);
	AEGfxTextureUnload(slimeBlockTexture3);
	AEGfxTextureUnload(slimeBlockTextureFlipped1);
	AEGfxTextureUnload(slimeBlockTextureFlipped2);
	AEGfxTextureUnload(slimeBlockTextureFlipped3);

	AEGfxTextureUnload(collectibleTexture);
	AEGfxTextureUnload(goalTexture1);
	AEGfxTextureUnload(goalTexture2);
	AEGfxTextureUnload(goalTexture3);
	AEGfxTextureUnload(goalTexture4);
	AEGfxTextureUnload(goalTexture5);
	AEGfxTextureUnload(goalTexture6);
	AEGfxTextureUnload(goalTexture7);
	AEGfxTextureUnload(goalTexture8);
	AEGfxTextureUnload(goalTexture9);
	AEGfxTextureUnload(goalTexture10);
	AEGfxTextureUnload(goalTexture11);
	AEGfxTextureUnload(goalTexture12);
	AEGfxTextureUnload(goalTexture13);
	AEGfxTextureUnload(goalTexture14);
	AEGfxTextureUnload(goalTexture15);
	AEGfxTextureUnload(goalTexture16);
	AEGfxTextureUnload(goalTexture17);
	AEGfxTextureUnload(goalTexture18);
	AEGfxTextureUnload(goalTexture19);
	AEGfxTextureUnload(goalTexture20);



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
				++e_totalNumOfcollectible;
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

void PlatformAnimationUpdate(void) {
	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {

			if (platform[i][j].GetPlatformType() == SLIME_BLOCK) {
				int frame = frameCounter % 30;
				switch (frame) {
				case 0:
					if (platform[i][j - 1].GetPlatformType() != SLIME_BLOCK && platform[i][j + 1].GetPlatformType() != SLIME_BLOCK) {
						platform[i][j].SetTexture(slimeBlockTexture2);
					}
					else if (platform[i][j - 1].GetPlatformType() != SLIME_BLOCK) {
						platform[i][j].SetTexture(slimeBlockTexture1);
					}
					else {
						platform[i][j].SetTexture(slimeBlockTexture3);
					}
					break;

				case 15:
					if (platform[i][j - 1].GetPlatformType() != SLIME_BLOCK && platform[i][j + 1].GetPlatformType() != SLIME_BLOCK) {
						platform[i][j].SetTexture(slimeBlockTextureFlipped2);
					}
					else if (platform[i][j - 1].GetPlatformType() != SLIME_BLOCK) {
						platform[i][j].SetTexture(slimeBlockTextureFlipped3);
					}
					else {
						platform[i][j].SetTexture(slimeBlockTextureFlipped1);
					}
					break;
				}
			}

			if (platform[i][j].GetPlatformType() == GOAL) {
				int frame = frameCounter % 20;
				switch (frame) {
				case 0:
					platform[i][j].SetTexture(goalTexture1);
					break;

				case 1:
					platform[i][j].SetTexture(goalTexture2);
					break;

				case 2:
					platform[i][j].SetTexture(goalTexture3);
					break;

				case 3:
					platform[i][j].SetTexture(goalTexture4);
					break;

				case 4:
					platform[i][j].SetTexture(goalTexture5);
					break;

				case 5:
					platform[i][j].SetTexture(goalTexture6);
					break;

				case 6:
					platform[i][j].SetTexture(goalTexture7);
					break;

				case 7:
					platform[i][j].SetTexture(goalTexture8);
					break;

				case 8:
					platform[i][j].SetTexture(goalTexture9);
					break;

				case 9:
					platform[i][j].SetTexture(goalTexture10);
					break;

				case 10:
					platform[i][j].SetTexture(goalTexture11);
					break;

				case 11:
					platform[i][j].SetTexture(goalTexture12);
					break;

				case 12:
					platform[i][j].SetTexture(goalTexture13);
					break;

				case 13:
					platform[i][j].SetTexture(goalTexture14);
					break;

				case 14:
					platform[i][j].SetTexture(goalTexture15);
					break;

				case 15:
					platform[i][j].SetTexture(goalTexture16);
					break;

				case 16:
					platform[i][j].SetTexture(goalTexture17);
					break;

				case 17:
					platform[i][j].SetTexture(goalTexture18);
					break;

				case 18:
					platform[i][j].SetTexture(goalTexture19);
					break;

				case 19:
					platform[i][j].SetTexture(goalTexture20);
					break;
				}
			}
		}
	}
}