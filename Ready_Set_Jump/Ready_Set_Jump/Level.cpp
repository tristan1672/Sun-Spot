/*
  *  \file Level.cpp 
  *  \author Xiao Jun Yu, 
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  the basic logics to our levels and the game states, loops for our game
  *  All content � 2023 DigiPen Institute of Technology Singapore. All rights reserved.
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
#include "PauseMenu.hpp"
#include<string>
#include "Tutorial.hpp"
#include "SaveManager.hpp"

// ---------------------------------------------------------------------------


#define GROUND_LEVEL 20
extern CameraPos cam;
mousePos mouse;
DynamicObj Player;
Platform** platform;
GameObject jumpArrow;
GameObject WinScreen;
GameObject Cleared;
std::string fileToLoad;
bool isTutorial;

float e_deltaTime;
float e_levelTime;
static int frameCounter;

Vector2D playerSpawnPoint;

int** e_levelGrid;
int e_binaryMapWidth;
int e_binaryMapHeight;
unsigned int e_totalNumOfcollectible;

int level_state;
int level1_difficulty;
bool e_scoreAnimation;
int levelNumber;

int gGameRunning = 1;
bool flick = false;
int jump_counter;

bool airCheck;
bool followMouseCheat;

float sceneSwitchBufferTimer = 0.1f;

AEGfxTexture* ptex{ nullptr };
AEGfxTexture* normalBlockTexture{ nullptr };
AEGfxTexture* stickyBlockTexture{ nullptr };

AEGfxTexture* iceBlockTexture[16]{ nullptr };
AEGfxTexture* slimeBlockTexture[16]{ nullptr };
AEGfxTexture* goalTexture[20]{ nullptr };

AEGfxTexture* collectibleTexture{ nullptr };
AEGfxTexture* checkPointTexture1{ nullptr };
AEGfxTexture* checkPointTexture2{ nullptr };


AEGfxTexture* arrowTexture{ nullptr };

GameObject *levelParticleList;


int ImportMapDataFromFile(const char* FileName);

// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level_Load()
{
	MakeMesh();
	MakeArrowMesh();

	ptex = AEGfxTextureLoad("Assets/Images/Cleared.png");
	normalBlockTexture = AEGfxTextureLoad("Assets/Images/Basic_Platform.png");
	stickyBlockTexture = AEGfxTextureLoad("Assets/Images/Sticky_Platform.png");

	arrowTexture = AEGfxTextureLoad("Assets/Images/Arrow.png");

	checkPointTexture1 = AEGfxTextureLoad("Assets/Images/Checkpoint_Off.png");
	checkPointTexture2 = AEGfxTextureLoad("Assets/Images/Checkpoint_On.png");

	collectibleTexture = AEGfxTextureLoad("Assets/Images/Collectible.png");

	MultiTextureLoad(iceBlockTexture, sizeof(iceBlockTexture) / sizeof(iceBlockTexture[0]), "Assets/Images/Ice_Platform_");
	MultiTextureLoad(slimeBlockTexture, sizeof(slimeBlockTexture) / sizeof(slimeBlockTexture[0]), "Assets/Images/Slime_Platform_");
	MultiTextureLoad(goalTexture, sizeof(goalTexture) / sizeof(goalTexture[0]), "Assets/Images/Portal_");

	Cleared = GameObject({ 0.0f, 0.0f }, { 500.0f, 500.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
	Cleared.SetTexture(ptex);

	if (!ImportMapDataFromFile(fileToLoad.c_str())) {
		std::cout << "Level File opened\n";
	}
	PauseMenu::CreatePauseMenu();
	if (isTutorial) Tutorial::MakeTutorialText();

	levelParticleList = new GameObject[MAX_PARTICLE_NUMBER];
}
// ----------------------------------------------------------------------------
// This function initialize game object instances
// It is called once at the start of the state
// ----------------------------------------------------------------------------
void Level_Initialize()
{

	level_state = SCENE_SWITCH_BUFFER;
	level1_difficulty = EASY;
	e_levelTime = 0.0f;
	e_numOfcollectibleCollected = 0;
	followMouseCheat = false;
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
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(normalBlockTexture);
				break;

			case ICE_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });

				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				TextureSetAll(i, j, iceBlockTexture, ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(stickyBlockTexture);
				break;

			case SLIME_BLOCK:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ GRID_WIDTH_SIZE, GRID_HEIGHT_SIZE });

				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				TextureSetAll(i, j, slimeBlockTexture, SLIME_BLOCK);
				break;

			case COLLECTIBLES:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ collectible_SIZE_X, collectible_SIZE_Y }, White, 0, AE_GFX_RM_COLOR, circleMesh);
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(collectibleTexture);
				break;

			case CHECKPOINT:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(checkPointTexture1);
				break;

			case GOAL:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(goalTexture[0]);
				break;
			case PLAYER_SPAWN:
				playerSpawnPoint = { GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE };
				platform[i][j].SetPlatformType(0);
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
	Player.jumpReady = false;
	jump_counter = 0;
#pragma endregion
	//sets the ui indicator for where the character is about to jump
	jumpArrow = GameObject({ 0.f,0.f }, { 10.f,100.f },
		{ 0.f,1.f,0.f,0.5f }, 0.f, AE_GFX_RM_TEXTURE, arrMesh);
	jumpArrow.SetTexture(arrowTexture);
	jumpArrow.SetScale({ 40.f,100.f });
	jumpArrow.SetColour({ 1.f,1.f,1.f,1.f });
	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;
	airCheck = false;
	shake = false;

	Cam(airCheck);

	// Warm up time for particles
	unsigned int waves = 20;
	unsigned int numPerWave = 5;
	float intervalWidth =  1.f / static_cast<float>(waves - 1) * static_cast<float>(WINDOW_WIDTH) * 2.f;

	for (unsigned int i{}; i < waves; ++i) {

		for (unsigned int j{}; j < numPerWave; ++j) {
			AEVec2 particalPosition = { static_cast<float>(Player.GetPosition().x - 0.5f * WINDOW_WIDTH + i * intervalWidth), static_cast<float>(rand() % static_cast<int>(e_binaryMapHeight * GRID_HEIGHT_SIZE) - static_cast<float>(e_binaryMapHeight * GRID_HEIGHT_SIZE) + HALVE_WINDOW_HEIGHT) };
			AEVec2 particleVelocity = { -static_cast<float>(rand() % 5 + 2) , 0.0f };
			int randScale = rand() % 8 + 2;

			*(levelParticleList + MAX_PARTICLE_NUMBER - 1 - (i * numPerWave + j)) = CreateParticle(particalPosition.x, particalPosition.y, particleVelocity.x, particleVelocity.y, static_cast<float>(randScale));
		}
	}
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level_Update()
{

	// No check for dead elements as it takes 136.5 sec for the entire array to be cycled through. By then the 1st particle would have been killed.
	if (frameCounter % 4) {
		
		AEVec2 particalPosition = { static_cast<float>(Player.GetPosition().x + WINDOW_WIDTH), static_cast<float>(rand() % static_cast<int>(e_binaryMapHeight * GRID_HEIGHT_SIZE) - static_cast<float>(e_binaryMapHeight * GRID_HEIGHT_SIZE) + HALVE_WINDOW_HEIGHT) };
		AEVec2 particleVelocity = { -static_cast<float>(rand() % 5 + 2) , 0.0f };
		int randScale = rand() % 8 + 2;

		* (levelParticleList + (static_cast<int>(frameCounter * 0.25) % MAX_PARTICLE_NUMBER)) = CreateParticle(particalPosition.x, particalPosition.y, particleVelocity.x, particleVelocity.y, static_cast<float>(randScale));
	}


	/*
	* this part is to prevent the player from moving due to input from previous scene
	*/
	if (level_state == SCENE_SWITCH_BUFFER) {
		sceneSwitchBufferTimer -= e_deltaTime;
		if (sceneSwitchBufferTimer <= 0) level_state = PLAYING;
	}
	if (level_state == WIN)
	{
		if (AEInputCheckTriggered(AEVK_ESCAPE))
		{
			e_next_state = GS_MAINMENU;
		}

		// Mouse click to return to menu
		if (e_scoreAnimation) {
			e_next_state = GS_MAINMENU;
		}
	}
	if (AEInputCheckTriggered(AEVK_ESCAPE)) {
		if (level_state != PAUSED)level_state = PAUSED;
		else
		{
			level_state = PLAYING;
		}
	}
	if (level_state == PAUSED) { 
		AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
		PauseMenu::PauseMenuBehaviour(mouse); 
	}

	if (level_state == PLAYING)
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
			if (Player.velocity.x && Player.velocity.y)jump_counter++;
			mouse = { 0,0,0,0 };
		}
		if (AEInputCheckTriggered(AEVK_1)) {
			followMouseCheat = !followMouseCheat;
		}


		// Prev collesion flag check
		airCheck = Player.GetColFlag();

		// Collision function
		Player.LevelCollision();
		Player.SnapToGrid();
		ObjectCollision();

		// If out of play area // This not running cause the 1 in level 1 running (SHIFT OUT IF GOT TIME)
		if (e_outOfMap) {
			Player.velocity.x = 0.0f;
			Player.velocity.y = 0.0f;
			Player.jumpReady = false;
			Player.position = { playerSpawnPoint.x,playerSpawnPoint.y };
			e_outOfMap = false;

		}

		if (e_collidedObjectType == GOAL) {
			level_state = WIN;
			Player.velocity.x = 0.0f;
			Player.velocity.y = 0.0f;
			e_collidedObjectType = 0;
		}
		else if (e_collidedObjectType == CHECKPOINT) {
			playerSpawnPoint = platform[e_collidedObjectXPosY][e_collidedObjectXPosX].GetPosition();
			
			// Update Checkpoints to now display active
			for (int i = 0; i < e_binaryMapHeight; i++) {
				for (int j = 0; j < e_binaryMapWidth; j++) {
					if (platform[i][j].GetPlatformType() == CHECKPOINT) {
						platform[i][j].SetTexture(checkPointTexture1);
					}
				}
			}

			platform[e_collidedObjectXPosY][e_collidedObjectXPosX].SetTexture(checkPointTexture2);
			e_collidedObjectType = 0;
		}
		else if (e_collidedObjectType == COLLECTIBLES) {
			platform[e_collidedObjectXPosY][e_collidedObjectXPosX].SetPlatformType(EMPTY_SPACE);
			++e_numOfcollectibleCollected;
			e_collidedObjectType = 0;
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

		// code that allows the player to get affected by gravity
		Player.PhysicsUpdate();


		if (followMouseCheat) {
			mousePos temp{};
			AEInputGetCursorPosition(&temp.ClickX, &temp.ClickY);
			Vector2D mouseQuadPos = { static_cast<float>(temp.ClickX) - HALVE_WINDOW_WIDTH + cam.X, -(static_cast<float>(temp.ClickY) - HALVE_WINDOW_HEIGHT) + cam.Y };
			Player.position = mouseQuadPos;
		}

		// Cam shake
		Cam(airCheck);

		// Update total time taken for level
		LevelTime();
	}	

	// Update particle effect for background
	UpdateParticle(levelParticleList);

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

	DrawParticle(levelParticleList);

	if(level_state == PLAYING)
	PlatformAnimationUpdate();

	// Draws the platform
	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {
			if (platform[i][j].GetPlatformType()) {
				platform[i][j].DrawObj();
			}
		}
	}
	if (isTutorial) Tutorial::RenderTutorialText();
	// Draws the arrow direction
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.jumpReady && currHoldTime >= MAX_HOLD_TIME) {
		jumpArrow.DrawObj();
	}
	// Draws the player
	Player.DrawObj();

	if (level_state == WIN) //draw win screen
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

	if (level_state == PAUSED)PauseMenu::DrawPauseMenu();

}

// ----------------------------------------------------------------------------
// This function frees objects instances
// It is called after to prepare the state to be unloaded or initialized again
// ----------------------------------------------------------------------------
void Level_Free()
{
	int temp{}; // this is a temp variable that should not be used once total score have been implemented
	if (level_state == WIN) {
		Save::SetSaveValue(levelNumber, jump_counter, e_numOfcollectibleCollected, e_levelTime, temp,true);
		Save::WriteFile();
	}
}

// ----------------------------------------------------------------------------
// This function dumps all loaded during Level1_Load()
// It is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level_Unload()
{
	if (isTutorial) Tutorial::FreeTutorialtext();

	for (int i = 0; i < e_binaryMapHeight; i++) {
		delete[] platform[i];
	}
	delete[] platform;

	UnloadPArticle(levelParticleList);

	PauseMenu::FreePauseMenu();

	AEGfxTextureUnload(ptex);
	AEGfxTextureUnload(normalBlockTexture);
	AEGfxTextureUnload(stickyBlockTexture);

	MultiTextureUnload(iceBlockTexture, sizeof(iceBlockTexture) / sizeof(iceBlockTexture[0]));
	MultiTextureUnload(slimeBlockTexture, sizeof(slimeBlockTexture) / sizeof(slimeBlockTexture[0]));
	MultiTextureUnload(goalTexture, sizeof(goalTexture) / sizeof(goalTexture[0]));

	AEGfxTextureUnload(collectibleTexture);
	AEGfxTextureUnload(checkPointTexture1);
	AEGfxTextureUnload(checkPointTexture2);

	AEGfxTextureUnload(arrowTexture);

	AEGfxMeshFree(pMesh);
	AEGfxMeshFree(arrMesh);
}


// Functions

int ImportMapDataFromFile(const char* FileName) {
	e_totalNumOfcollectible = 0;
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

			if (platform[i][j].GetPlatformType() == GOAL) {
				int frame = frameCounter % 20;
				platform[i][j].SetTexture(goalTexture[frame]);
			}
		}
	}
}
