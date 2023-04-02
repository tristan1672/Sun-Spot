/*
  *  \file LevelSelect.cpp
  *  \author(s) : Xiao Jun Yu, (junyu.xiao)
  *					 -Main Author
  *					 -CreateLevelSelectUI()
  *						creates UI in level select
  *					-ButtonSelectBehaviour(mousePos mouse)
  *						when player pressed the level numbers in level select, players will bring up UI showing stats regarding that level
  *					-LSButtonAnimation(mousePos mouse)
  *						when player hovers over the numbers in level select, individual text box will fade in
  *					-DrawLevelButton()
  *						draws all buttons in level select
  *					-FreeLevelButton()
  *						frees memories allocated from CreateLevelSelectUI
  *					-SetLevelSelectActive()
  *						make all level select button to be active
  *					-SetLevelSelectInActive()
  *						make all level select button to be inactive
  *					-BackButtonBehaviour(mousePos mouse)
  *						when the back button is pressed, it will return player back to the main menu
  *					-StartButtonBehaviour(mousePos mouse)
  *						when the start button is pressed, it will bring the player to the actual level
  * 
  *				: Tristan Tham Rui Hong 
  *					-Sub Author
  *					-StagingScreen(int levelcount)
  *					 
  *					-InitLSTexture()
  *		
  *					-LoadLSTexture()
  *						Loads texture in level select
  *				    -UnloadLSTexture()
  *						frees memories allocated from LoadLSTexture
  *					-DrawLSTexture()
  *						draws textures in level select
  * 
  *  \brief
  *  Defination file for LevelSelect.hpp
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
*/
#include "LevelSelect.hpp"
#include "SaveManager.hpp"

namespace LevelSelect {
	UIText** levels{ nullptr };
	UIText* button[2]{nullptr};
	UIText* levelnumber;
	
	char leveltext[15];
	char jumpCount[5];
	char minCount[5];
	char secCount[5];
	char collectibleCount[7];
	char totalScore[10];

	AEGfxTexture* timeTexture;
	AEGfxTexture* frameTexture;
	AEGfxTexture* collectibleTexture;
	AEGfxTexture* jumpTexture;

	GameObject Frame, Time, Collectible, Jumps;

	int jump{}, collc{}, difficulty{}, totalscore{}, totalcollectibles{}, minutes{}, seconds{};
	float time{};
	bool attempt{};

	Vector2D jumpPos, collectiblePos, timePos, framePos, startPos, backPos, titlePos, scorePos;

	void CreateLevelSelectUI() {
		//creates the initial level UI
		levels = new UIText * [LEVEL_ARRAY_SIZE] {};
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			levels[i] = new UIText[4]{};
		}

		float gapSize = LEVEL_BUTTON_GAP * 2 / (LEVEL_ARRAY_SIZE - 1.0f);

		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {// the level table
			for (int j = 0; j < LEVEL_ARRAY_SIZE; ++j) {
				int levelcount = i * LEVEL_ARRAY_SIZE + j + 1;
				levels[i][j] = UIText(std::to_string(levelcount), { (j * gapSize - LEVEL_BUTTON_GAP), (-i * 0.3f + 0.4f) }, { 1.f,1.f }, White, true, GreenTea);// sets each button at their location
				levels[i][j].TextBoxActive = false;
				levels[i][j].Active = false;

				AEVec2 size{};
				AEGfxGetPrintSize(e_fontID, levels[i][j].GetText(), levels[i][j].GetScale().x, size.x, size.y);
				levels[i][j].SetPosition({ -0.5f * size.x + levels[i][j].GetPosition().x, levels[i][j].GetPosition().y });
			}
		}

		button[0] = new UIText{ UIText("Back", { -0.7f, -0.7f },{1.f,1.f},White, true, GreenTea) };// makes the back button
		button[1] = new UIText{ UIText("Start", { 0.6f, -0.7f },{1.f,1.f},White, true, GreenTea) };// makes the start button

		for (unsigned int i{}; i < 2; ++i) {
			AEVec2 size{};
			AEGfxGetPrintSize(e_fontID, button[i]->GetText(), button[i]->GetScale().x, size.x, size.y);
			button[i]->SetPosition({ -0.5f * size.x + button[i]->GetPosition().x, button[i]->GetPosition().y});
		}

		button[1]->TextBoxActive = false;
		button[1]->Active = false;

		button[0]->TextBoxActive = false;
		button[0]->Active = false;
	}

	void ButtonSelectBehaviour(mousePos mouse) {// what will happen when the level button was pressed
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			for (int j = 0; j < LEVEL_ARRAY_SIZE; ++j) {
				if (levels[i][j].MouseCollision(mouse)) {
					levelNumber = i * LEVEL_ARRAY_SIZE + j + 1;
					SetLevelSelectInActive();// sets the whole level grid to inactive
					e_uiState = STAGE;
					StagingScreen(levelNumber);// shows the level info 
				}
			}
		}
	}

	void LSButtonAnimation(mousePos mouse) {// text box fade animation
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			for (int j = 0; j < LEVEL_ARRAY_SIZE; ++j) {
				if (levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY }) && levels[i][j].GetTextBoxAlpha() < 1.f) {
					levels[i][j].TextBoxFadeIn();// for level grid
				}
				else if (!(levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY }))) levels[i][j].TextBoxFadeOut();
			}
		}
		if (button[0]->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && button[0]->GetTextBoxAlpha() < 1.f) {// for back button
			button[0]->TextBoxFadeIn();
		}
		else if (!button[0]->MouseCollision({ mouse.ClickX ,mouse.ClickY })) button[0]->TextBoxFadeOut();

		if (button[1]->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && button[1]->GetTextBoxAlpha() < 1.f) {// for start button
			button[1]->TextBoxFadeIn();
		}
		else if (!button[1]->MouseCollision({ mouse.ClickX ,mouse.ClickY })) button[1]->TextBoxFadeOut();
	}
	void DrawLevelButton() {// draws all level buttons
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			for (int j = 0; j < LEVEL_ARRAY_SIZE; ++j) {
				levels[i][j].DrawObj();
			}
		}
		button[0]->DrawObj();
		button[1]->DrawObj();
	}
	void FreeLevelButton() {// frees memory allocated for level grids
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			delete[] levels[i];
		}
		delete[] levels;
		delete button[0];
		delete button[1];
	}
	void SetLevelSelectActive() {// sets all level select object to active
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			for (int j = 0; j < LEVEL_ARRAY_SIZE; ++j) {
				LevelSelect::levels[i][j].TextBoxActive = true;
				LevelSelect::levels[i][j].Active = true;
			}
		}
		button[0]->TextBoxActive = true;
		button[0]->Active = true;
		button[1]->TextBoxActive = false;
		button[1]->Active = false;
	}
	void SetLevelSelectInActive() {// sets all level select object to inactive
		for (int i = 0; i < LEVEL_ARRAY_SIZE; ++i) {
			for (int j = 0; j < LEVEL_ARRAY_SIZE; ++j) {
				LevelSelect::levels[i][j].TextBoxActive = false;
				LevelSelect::levels[i][j].Active = false;
			}
		}
		button[0]->TextBoxActive = false;
		button[0]->Active = false;

		button[1]->TextBoxActive = false;
		button[1]->Active = false;
	}
	bool BackButtonBehaviour(mousePos mouse) {
		if (button[0]->MouseCollision(mouse))
		{
			Frame.SetTexture(nullptr);
			Time.SetTexture(nullptr);
			Collectible.SetTexture(nullptr);
			Jumps.SetTexture(nullptr);

			*leveltext			= NULL;
			*jumpCount			= NULL;
			*collectibleCount	= NULL;
			*minCount			= NULL;
			*secCount			= NULL;

			return true;
		}
		return false;
	}

	bool StartButtonBehaviour(mousePos mouse)
	{
		if (button[1]->MouseCollision(mouse))
		{
			return true;
		}
		return false;
	}

	void StagingScreen(int levelcount)
	{
		button[1]->TextBoxActive = true;
		button[1]->Active = true;
		button[0]->TextBoxActive = true;
		button[0]->Active = true;
		Frame.SetTexture(frameTexture);
		Time.SetTexture(timeTexture);
		Collectible.SetTexture(collectibleTexture);
		Jumps.SetTexture(jumpTexture);

		fileToLoad = "Assets/Script/Level";
		fileToLoad += std::to_string(levelcount);
		fileToLoad += ".txt";

		Save::GetSaveValue(levelcount, difficulty, jump, collc, totalcollectibles, time, totalscore, attempt);

		minutes = (int)time / 60; //extract minute
		seconds = (int)time % 60; //extract seconds
		
		snprintf(leveltext,			sizeof leveltext,			"Level %d",		levelcount);
		snprintf(jumpCount,			sizeof jumpCount,			"%d",			jump);
		snprintf(collectibleCount,	sizeof collectibleCount,	"%d/%d",		collc, totalcollectibles);
		snprintf(minCount,			sizeof minCount,			"%d:",			minutes);
		snprintf(secCount, 			sizeof secCount,			"%02d",			seconds);
		snprintf(totalScore,		sizeof totalScore,			"%d",			totalscore);

		if (!attempt)
		{
			*jumpCount = '-';
			*collectibleCount = '-';
		}

		std::cout << "Level:dsa " << levelNumber << std::endl;
		std::cout << "Jumps: " << jump << std::endl;
		std::cout << "Collectibles: " << collc << std::endl;
		std::cout << "TotalCollectibles: " << totalcollectibles << std::endl;
		std::cout << "Time: " << time << std::endl;
		std::cout << "Attempted: " << attempt << std::endl;
		
	}

	void InitLSTexture()
	{
		//Non-Normalized Coordinates
		framePos			= { 0.0f, 0.0f };
		jumpPos				= {-(HALVE_WINDOW_WIDTH * 0.3f),   (HALVE_WINDOW_HEIGHT * 0.3f)};
		collectiblePos		= {-(HALVE_WINDOW_WIDTH * 0.3f),   (0.0f) };
		timePos				= {-(HALVE_WINDOW_WIDTH * 0.3f),  -(HALVE_WINDOW_HEIGHT * 0.3f)};
		titlePos			= {-0.15f, 0.55f};

		//Normalized Coordinates
		backPos				= { - 0.9f,  -0.8f};
		startPos			= {  0.65f,  -0.8f};

		Frame				= GameObject(framePos,		{ HALVE_WINDOW_WIDTH, HALVE_WINDOW_HEIGHT }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
		Jumps				= GameObject(jumpPos,		{ 80.0f, 70.0f },	{ 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
		Collectible			= GameObject(collectiblePos,{ 60.0f, 70.0f },	{ 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
		Time				= GameObject(timePos,		{ 70.0f, 80.0f },	{ 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);

		*leveltext			= NULL;
		*jumpCount			= NULL;
		*collectibleCount	= NULL;
		*minCount			= NULL;
		*secCount			= NULL;
	}

	void LoadLSTexture()
	{	
		timeTexture			= AEGfxTextureLoad("Assets/Images/Time.png");
		frameTexture		= AEGfxTextureLoad("Assets/Images/ScoreFrame.png");
		collectibleTexture	= AEGfxTextureLoad("Assets/Images/Collectible.png");
		jumpTexture			= AEGfxTextureLoad("Assets/Images/Player_3.png");
	}

	void UnloadLSTexture()
	{
		AEGfxTextureUnload(timeTexture);
		AEGfxTextureUnload(frameTexture);
		AEGfxTextureUnload(collectibleTexture);
		AEGfxTextureUnload(jumpTexture);
	}

	void DrawLSTexture()
	{
		Frame.DrawObj();
		Time.DrawObj();
		Collectible.DrawObj();
		Jumps.DrawObj();

		AEGfxPrint(e_fontID, leveltext,			 (titlePos.x),																(titlePos.y),																1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, jumpCount,			 (jumpPos.x			+ HALVE_WINDOW_WIDTH * 0.325f) / HALVE_WINDOW_WIDTH,	(jumpPos.y		  - HALVE_WINDOW_HEIGHT * 0.025f) / HALVE_WINDOW_HEIGHT,	1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, collectibleCount,	 (collectiblePos.x	+ HALVE_WINDOW_WIDTH * 0.3f)   / HALVE_WINDOW_WIDTH,	(collectiblePos.y - HALVE_WINDOW_HEIGHT * 0.025f) / HALVE_WINDOW_HEIGHT,	1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, minCount,			 (timePos.x			+ HALVE_WINDOW_WIDTH * 0.275f)   / HALVE_WINDOW_WIDTH,	(timePos.y)  / HALVE_WINDOW_HEIGHT,											1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, secCount,			 (timePos.x			+ HALVE_WINDOW_WIDTH * 0.35f)  / HALVE_WINDOW_WIDTH,	(timePos.y)  / HALVE_WINDOW_HEIGHT,											1.0f, 1.0f, 1.0f, 1.0f);
	}
}