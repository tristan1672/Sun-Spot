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
int e_totalNumOfcollectible;

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
AEGfxTexture* iceBlockTexture{ nullptr };
AEGfxTexture* stickyBlockTexture{ nullptr };
AEGfxTexture* slimeBlockTexture1{ nullptr };
AEGfxTexture* slimeBlockTexture2{ nullptr };
AEGfxTexture* slimeBlockTexture3{ nullptr };
AEGfxTexture* slimeBlockTextureFlipped1{ nullptr };
AEGfxTexture* slimeBlockTextureFlipped2{ nullptr };
AEGfxTexture* slimeBlockTextureFlipped3{ nullptr };

AEGfxTexture* collectibleTexture{ nullptr };
AEGfxTexture* checkPointTexture1{ nullptr };
AEGfxTexture* checkPointTexture2{ nullptr };
AEGfxTexture* goalTexture[20]{nullptr};

GameObject *particleList;


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
	iceBlockTexture = AEGfxTextureLoad("Assets/Images/Ice_Platform.png");
	stickyBlockTexture = AEGfxTextureLoad("Assets/Images/Sticky_Platform.png");
	slimeBlockTexture1 = AEGfxTextureLoad("Assets/Images/Slime_Platform_1.png");
	slimeBlockTexture2 = AEGfxTextureLoad("Assets/Images/Slime_Platform_2.png");
	slimeBlockTexture3 = AEGfxTextureLoad("Assets/Images/Slime_Platform_3.png");
	slimeBlockTextureFlipped1 = AEGfxTextureLoad("Assets/Images/Slime_Platform_1(Flipped).png");
	slimeBlockTextureFlipped2 = AEGfxTextureLoad("Assets/Images/Slime_Platform_2(Flipped).png");
	slimeBlockTextureFlipped3 = AEGfxTextureLoad("Assets/Images/Slime_Platform_3(Flipped).png");

	checkPointTexture1 = AEGfxTextureLoad("Assets/Images/Flag_Down.png");
	checkPointTexture2 = AEGfxTextureLoad("Assets/Images/Flag_Up.png");

	collectibleTexture = AEGfxTextureLoad("Assets/Images/Collectible.png");
	for (int i{}; i < sizeof(goalTexture)/sizeof(goalTexture[0]); ++i) {
		std::string location{"Assets/Images/Portal_"};
		location += std::to_string(i + 1)+".png" ;
		goalTexture[i] = AEGfxTextureLoad(location.c_str());
	}

	Cleared = GameObject({ 0.0f, 0.0f }, { 500.0f, 500.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
	Cleared.SetTexture(ptex);

	if (!ImportMapDataFromFile(fileToLoad.c_str())) {
		std::cout << "Level File opened\n";
	}
	PauseMenu::CreatePauseMenu();
	if (isTutorial) Tutorial::MakeTutorialText();

	particleList = new GameObject[MAX_PARTICLE_NUMBER];


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
				if (platform[i][j - 1].GetPlatformType() == SLIME_BLOCK && platform[i][j + 1].GetPlatformType() == SLIME_BLOCK) {
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
					{ collectible_SIZE_X, collectible_SIZE_Y }, White, 0, AE_GFX_RM_COLOR, circleMesh);
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(collectibleTexture);
				break;

			case CHECKPOINT:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(checkPointTexture2);
				break;

			case GOAL:
				platform[i][j] = Platform(
					{ GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE },
					{ GOAL_SIZE_X, GOAL_SIZE_Y });
				platform[i][j].SetRenderMode(AE_GFX_RM_TEXTURE);
				platform[i][j].SetTexture(goalTexture[0]);
				break;
			case PLAYER_SPAWN:
				playerSpawnPoint = { GRID_WIDTH_SIZE / 2.0f - (WINDOW_WIDTH / 2.0f) + j * GRID_WIDTH_SIZE, -GRID_HEIGHT_SIZE / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * GRID_HEIGHT_SIZE };
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
		{ 0.f,1.f,0.f,0.5f }, 0.f, AE_GFX_RM_COLOR, arrMesh);
	jumpArrow.SetScale({ 10.f,100.f });
	jumpArrow.SetColour({ 0.f,1.f,0.f,0.5f });
	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;
	airCheck = false;
	shake = false;

	Cam(airCheck);
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level_Update()
{
	// Background particle effect
	AEVec2 particalPosition = { static_cast<float>(e_binaryMapWidth*GRID_WIDTH_SIZE + 20), static_cast<float>(rand() % WINDOW_HEIGHT - WINDOW_HEIGHT_OFFSET) };

	int randScale = rand() % 10 + 5;
	AEVec2 particalScale = { static_cast<float>(randScale), static_cast<float>(randScale) };
	
	int randLifeTime = rand() % 70 + e_binaryMapWidth;
	AEVec2 particleVelocity = { -static_cast<float>(rand() % 30 + 10) , 0.0f};

	*(particleList + (frameCounter % MAX_PARTICLE_NUMBER)) = GameObject({ particalPosition.x, particalPosition.y }, { particalScale.x, particalScale.y }, { 255.f, 255.f, 255.f, 255.f },
					static_cast<float>(randLifeTime), AE_GFX_RM_COLOR, pMesh, { particleVelocity.x , particleVelocity.y });


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
			next = GS_MAINMENU;
		}

		// Mouse click to return to menu
		if (e_scoreAnimation && AEInputCheckTriggered(AEVK_LBUTTON)) {
			next = GS_MAINMENU;
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
		PauseMenu::PauseMenuBehaviour(mouse); }

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
	ObjectiveCollision();

	// code that allows the player to get affected by gravity
	Player.PhysicsUpdate();


	if (followMouseCheat) {
		mousePos temp{};
		AEInputGetCursorPosition(&temp.ClickX, &temp.ClickY);
		Vector2D mouseQuadPos = { static_cast<float>(temp.ClickX) - WINDOW_WIDTH / 2.f + cam.X, -(static_cast<float>(temp.ClickY) - WINDOW_HEIGHT / 2.f) + cam.Y };
		Player.position = mouseQuadPos;
	}

	// Cam shake
	Cam(airCheck);

	// Update total time taken for level
	LevelTime();
	}	

	// Update particle effect for background
	for (unsigned int i{}; i < MAX_PARTICLE_NUMBER; ++i) {

		GameObject* pInst = particleList + i;

		// Rotation is resued as lifetime
		if (pInst->GetRotation() > 0) {
			pInst->SetPosition( {pInst->GetPosition().x + pInst->GetDirection().x, pInst->GetPosition().y + pInst->GetDirection().y} );
			pInst->SetRotation(pInst->GetRotation() - 1.0f);
		}

	}

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

	for (unsigned int i{}; i < MAX_PARTICLE_NUMBER; ++i) {

		GameObject* pInst = particleList + i;

		// Rotation is resued as lifetime
		if (pInst->GetRotation() > 0) {
			pInst->DrawObj();

			//std::cout << "Partical " << i << "\n";
			//std::cout << "Particle Drawn, Lifetime: " << pInst->GetRotation() << "\n";
			//std::cout << "Particle Velocity X " << pInst->GetDirection().x << "\n";
		}

	}



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

	PauseMenu::FreePauseMenu();

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
	AEGfxTextureUnload(checkPointTexture1);
	AEGfxTextureUnload(checkPointTexture2);

	for (int i{}; i < sizeof(goalTexture) / sizeof(goalTexture[0]); ++i) {
		if(goalTexture[i])
		AEGfxTextureUnload(goalTexture[i]);
	}



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

			if (platform[i][j].GetPlatformType() == SLIME_BLOCK) {
				int frame = frameCounter % 30;
				switch (frame) {
				case 0:
					if (platform[i][j - 1].GetPlatformType() == SLIME_BLOCK && platform[i][j + 1].GetPlatformType() == SLIME_BLOCK) {
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
					if (platform[i][j - 1].GetPlatformType() == SLIME_BLOCK && platform[i][j + 1].GetPlatformType() == SLIME_BLOCK) {
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
				platform[i][j].SetTexture(goalTexture[frame]);
			}
		}
	}
}