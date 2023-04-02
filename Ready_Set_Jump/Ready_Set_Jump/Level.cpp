/*****************************************************************
* \file Level.cpp
* \project name : Ready ? Set.Jump!
*\author(s) : Peh Zong Lin Adrian(p.zonglinadrian) (50%)
*             - Bitmap reading and storing
*             - Made majority of the levels
*			  - Texture setting for objects and platforms in bitmap
*             - Reset player if out of play area
*             - Collision check 
*             - Object collision update
*			  - Added particles
*            : Xiao Jun Yu(junyu.xiao)             (30%)
*			  - Loaded textures
*             - Save file
*             - Game physics
*           : Tristan Tham (t.tham)                (20%)
*             - Cam
*             - Win scene
*\brief
* the basic logics to our levels and the game states, loops for our game
* All content © 2023 DigiPen Institute of Technology Singapore.All rights reserved.
* ***************************************************************/
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
Vector2D goalPos;

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

// Textures
AEGfxTexture* ptex{ nullptr };
AEGfxTexture* playerTexture[10]{ nullptr };
AEGfxTexture* normalBlockTexture[16]{ nullptr };
AEGfxTexture* iceBlockTexture[16]{ nullptr };
AEGfxTexture* stickyBlockTexture[16]{ nullptr };
AEGfxTexture* slimeBlockTexture[16]{ nullptr };
AEGfxTexture* goalTexture[20]{ nullptr };
AEGfxTexture* collectibleTexture{ nullptr };
AEGfxTexture* checkPointTexture1{ nullptr };
AEGfxTexture* checkPointTexture2{ nullptr };
AEGfxTexture* arrowTexture{ nullptr };

// Particles
GameObject *levelParticleList;

// Audio
AEAudio gameBackgroud;
AEAudioGroup gameBackgroundSoundGroup;


int ImportMapDataFromFile(const char* FileName);

// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level_Load()
{
	MakeMesh();
	MakeArrowMesh();

	// Texture
	ptex = AEGfxTextureLoad("Assets/Images/Cleared.png");
	arrowTexture = AEGfxTextureLoad("Assets/Images/Arrow.png");
	checkPointTexture1 = AEGfxTextureLoad("Assets/Images/Checkpoint_Off.png");
	checkPointTexture2 = AEGfxTextureLoad("Assets/Images/Checkpoint_On.png");
	collectibleTexture = AEGfxTextureLoad("Assets/Images/Collectible.png");
	
	MultiTextureLoad(playerTexture, sizeof(playerTexture) / sizeof(playerTexture[0]), "Assets/Images/Player_");
	MultiTextureLoad(normalBlockTexture, sizeof(normalBlockTexture) / sizeof(normalBlockTexture[0]), "Assets/Images/Basic_Platform_");
	MultiTextureLoad(iceBlockTexture, sizeof(iceBlockTexture) / sizeof(iceBlockTexture[0]), "Assets/Images/Ice_Platform_");
	MultiTextureLoad(stickyBlockTexture, sizeof(stickyBlockTexture) / sizeof(stickyBlockTexture[0]), "Assets/Images/Sticky_Platform_");
	MultiTextureLoad(slimeBlockTexture, sizeof(slimeBlockTexture) / sizeof(slimeBlockTexture[0]), "Assets/Images/Slime_Platform_");
	MultiTextureLoad(goalTexture, sizeof(goalTexture) / sizeof(goalTexture[0]), "Assets/Images/Portal_");

	Cleared = GameObject({ 0.0f, 0.0f }, { 500.0f, 500.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
	Cleared.SetTexture(ptex);

	// File data storing
	if (!ImportMapDataFromFile(fileToLoad.c_str())) {
		std::cout << "Level File opened\n";
	}
	PauseMenu::CreatePauseMenu();
	if (isTutorial) Tutorial::MakeTutorialText();


	// Particle
	levelParticleList = new GameObject[MAX_PARTICLE_NUMBER];

	// Audio
	gameBackgroud = AEAudioLoadMusic("Assets/Sound/GameBackground.mp3");
	gameBackgroundSoundGroup = AEAudioCreateGroup();
}
// ----------------------------------------------------------------------------
// This function initialize game object instances
// It is called once at the start of the state
// ----------------------------------------------------------------------------
void Level_Initialize()
{
	AEAudioPlay(gameBackgroud, gameBackgroundSoundGroup, 0.2, 1, -1);

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
				TextureSetAll(i, j, normalBlockTexture, NORMAL_BLOCK);
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
				TextureSetAll(i, j, stickyBlockTexture, STICKY_BLOCK);
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
				goalPos = { GRID_WIDTH_SIZE / 2.0f - HALVE_WINDOW_WIDTH + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + HALVE_WINDOW_HEIGHT - i * GRID_HEIGHT_SIZE };
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
	//Player.SetColour({ 0.f,1.f,1.f,1.f });
	Player.SetRenderMode(AE_GFX_RM_TEXTURE);
	Player.SetTexture(playerTexture[0]);
	Player.SetScale({ PLAYER_SIZE_X , PLAYER_SIZE_Y });
	Player.jumpReady = false;
	jump_counter = 0;
#pragma endregion
	//sets the ui indicator for where the character is about to jump
	jumpArrow = GameObject({ 0.f,0.f }, { 10.f,100.f },
		{ 0.f,1.f,0.f,0.5f }, 0.f, AE_GFX_RM_TEXTURE, arrMesh);
	jumpArrow.SetTexture(arrowTexture);
	jumpArrow.SetScale({ 40.f,100.f });
	jumpArrow.SetColour({ 1.f,1.f,1.f,0.8f });
	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;
	airCheck = false;
	shake = false;

	Cam(airCheck, { 0.0f,0.0f });

	// Warm up time for particles
	unsigned int waves = 20;
	unsigned int numPerWave = 5;
	float intervalWidth = 1.f / static_cast<float>(waves - 1) * static_cast<float>(WINDOW_WIDTH) * 2.f;

	unsigned int setsOfWaves = static_cast<int>((e_binaryMapWidth * GRID_WIDTH_SIZE) / WINDOW_WIDTH) + 1;

	for (unsigned int i{}; i < setsOfWaves; ++i) {
		for (unsigned int j{}; j < waves; ++j) {
			for (unsigned int k{}; k < numPerWave; ++k) {
				AEVec2 particalPosition = { static_cast<float>(Player.GetPosition().x - HALVE_WINDOW_WIDTH + (i * WINDOW_WIDTH) + (j * intervalWidth)), static_cast<float>(rand() % static_cast<int>(e_binaryMapHeight * GRID_HEIGHT_SIZE) - static_cast<float>(e_binaryMapHeight * GRID_HEIGHT_SIZE) + HALVE_WINDOW_HEIGHT) };
				AEVec2 particleVelocity = { -static_cast<float>(rand() % 5 + 2) , 0.0f };
				int randScale = rand() % 8 + 2;

				*(levelParticleList + MAX_PARTICLE_NUMBER - 1 - (j * numPerWave + k) - (i * waves * numPerWave)) = CreateParticle(particalPosition.x, particalPosition.y, particleVelocity.x, particleVelocity.y, static_cast<float>(randScale));
			}
		}
	}
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level_Update()
{
	AEAudioResumeGroup(gameBackgroundSoundGroup);

	// No check for dead elements as it takes 136.5 sec for the entire array to be cycled through. By then the 1st particle would have been killed.
	if (frameCounter % 4) {
		
		AEVec2 particalPosition = { static_cast<float>(e_binaryMapWidth * GRID_WIDTH_SIZE), static_cast<float>(rand() % static_cast<int>(e_binaryMapHeight * GRID_HEIGHT_SIZE) - static_cast<float>(e_binaryMapHeight * GRID_HEIGHT_SIZE) + HALVE_WINDOW_HEIGHT) };
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
		AEAudioPauseGroup(gameBackgroundSoundGroup);

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
		AEAudioPauseGroup(gameBackgroundSoundGroup);
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
		Player.SetColFlag(0);
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
		

		// code that allows the player to get affected by gravity
		Player.PhysicsUpdate();



		if (followMouseCheat) {
			mousePos temp{};
			AEInputGetCursorPosition(&temp.ClickX, &temp.ClickY);
			Vector2D mouseQuadPos = { static_cast<float>(temp.ClickX) - HALVE_WINDOW_WIDTH + cam.X, -(static_cast<float>(temp.ClickY) - HALVE_WINDOW_HEIGHT) + cam.Y };
			Player.position = mouseQuadPos;
		}

		//Cam effects
		Cam(airCheck, goalPos);

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
	AnimationUpdate();

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
		WinScreen.SetScale({static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)});
		WinScreen.SetColour({ 0.f,0.0f,0.f,0.9f });
		WinScreen.DrawObj();

		Cleared.SetPosition({ cam.X , cam.Y + 100.0f });
		Cleared.DrawObj();
		PrintScore(jump_counter);

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
		//Save::SetSaveValue(levelNumber, jump_counter, e_numOfcollectibleCollected, e_levelTime, temp,true);
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

	MultiTextureUnload(playerTexture, sizeof(playerTexture) / sizeof(playerTexture[0]));
	MultiTextureUnload(normalBlockTexture, sizeof(normalBlockTexture) / sizeof(normalBlockTexture[0]));
	MultiTextureUnload(iceBlockTexture, sizeof(iceBlockTexture) / sizeof(iceBlockTexture[0]));
	MultiTextureUnload(stickyBlockTexture, sizeof(stickyBlockTexture) / sizeof(stickyBlockTexture[0]));
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

void AnimationUpdate(void) {
	for (int i = 0; i < e_binaryMapHeight; i++) {
		for (int j = 0; j < e_binaryMapWidth; j++) {

			if (platform[i][j].GetPlatformType() == GOAL) {
				int frame = frameCounter % 20;
				platform[i][j].SetTexture(goalTexture[frame]);
			}
		}
	}

	s32 cursorX, cursorY;
	AEInputGetCursorPosition(&cursorX, &cursorY);
	Vector2D mouseClickQuadPos = { static_cast<float>(cursorX) - HALVE_WINDOW_WIDTH + cam.X, -(static_cast<float>(cursorY) - HALVE_WINDOW_HEIGHT) + cam.Y };
	if (/*Player.velocity.x != 0 && */abs(Player.velocity.y) > 12.f) {
		if (Player.velocity.x >= 0) { // Moving left
			if(Player.velocity.y >= 0) 
				Player.SetTexture(playerTexture[2]); // Upwards
			else 
				Player.SetTexture(playerTexture[3]); // Downwards
		}
		else { // Moving right
			if (Player.velocity.y >= 0)
				Player.SetTexture(playerTexture[7]); // Upwards
			else
				Player.SetTexture(playerTexture[8]); // Downwards
		}
	}
	else  {
		if (AEInputCheckCurr(AEVK_LBUTTON)) {
			if (Player.GetPosition().x < mouseClickQuadPos.x)
				Player.SetTexture(playerTexture[1]); // Face right
			else
				Player.SetTexture(playerTexture[6]); // Face left
		}
		else if(Player.GetColFlag() & COLLISION_BOTTOM) {
			if (Player.GetPosition().x < mouseClickQuadPos.x)
				Player.SetTexture(playerTexture[0]); // Face right
			else
				Player.SetTexture(playerTexture[5]); // Face left
		}
	}
	if (Player.velocity.y != 0) {
		if (Player.GetColFlag() & COLLISION_LEFT) 
			Player.SetTexture(playerTexture[4]);
		else if(Player.GetColFlag() & COLLISION_RIGHT)
			Player.SetTexture(playerTexture[9]);
	
	}
}
