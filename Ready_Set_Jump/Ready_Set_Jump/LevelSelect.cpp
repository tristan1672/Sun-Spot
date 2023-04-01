/*
  *  \file LevelSelect.cpp
  *  \author Xiao Jun Yu,
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
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
	
	char leveltext[25];
	char jumpCount[25];
	char timeCount[25];
	char collectibleCount[25];
	char totalScore[25];

	AEGfxTexture* timeTexture;
	AEGfxTexture* frameTexture;
	AEGfxTexture* collectibleTexture;

	GameObject Frame, Time, collectible;

	int jump{}, collc{}, difficulty{}, totalscore{}, totalcollectibles{};
	float time{};
	bool attempt{};

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
		//backButton = new UIText{ UIText("Back", { -0.8f, -0.7f },{1.f,1.f},White, true, GreenTea) };// makes the back button
		//startButton = new UIText{ UIText("Start", { 0.6f, -0.7f },{1.f,1.f},White, true, GreenTea) };// makes the start button

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
			collectible.SetTexture(nullptr);

			*leveltext = NULL;
			*jumpCount = NULL;
			*collectibleCount = NULL;
			*timeCount = NULL;

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
		collectible.SetTexture(collectibleTexture);

		fileToLoad = "Assets/Script/Level";
		fileToLoad += std::to_string(levelcount);
		fileToLoad += ".txt";

		Save::GetSaveValue(levelcount, difficulty, jump, collc, totalcollectibles, time, totalscore, attempt);
		
		snprintf(leveltext,			sizeof leveltext,			"Level %d", levelcount);
		snprintf(jumpCount,			sizeof jumpCount,			"%d", jump);
		snprintf(collectibleCount,	sizeof collectibleCount,	"%d / %d", collc, totalcollectibles);
		snprintf(timeCount,			sizeof timeCount,			"0%.2f", time);
		snprintf(totalScore,		sizeof totalScore,			"%d", totalscore);

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
		Frame = GameObject({ 25.f, 0.0f }, { 700.0f, 400.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
		Time  = GameObject({ -180.f, -100.f }, { 70.0f, 80.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
		collectible  = GameObject({ -180.0f, 5.0f }, { 60.0f, 70.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);

		*leveltext = NULL;
		*jumpCount = NULL;
		*collectibleCount = NULL;
		*timeCount = NULL;
	}

	void LoadLSTexture()
	{
		timeTexture = AEGfxTextureLoad("Assets/Images/Time.png");
		frameTexture = AEGfxTextureLoad("Assets/Images/ScoreFrame.png");
		collectibleTexture = AEGfxTextureLoad("Assets/Images/Collectible.png");
	}

	void UnloadLSTexture()
	{
		AEGfxTextureUnload(timeTexture);
		AEGfxTextureUnload(frameTexture);
		AEGfxTextureUnload(collectibleTexture);
	}

	void DrawLSTexture()
	{
		Frame.DrawObj();
		Time.DrawObj();
		collectible.DrawObj();

		AEGfxPrint(e_fontID, leveltext,			 -0.15f,    0.6f, 1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, jumpCount,			 0.035f,    0.27f, 1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, collectibleCount,	 0.035f,    0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxPrint(e_fontID, timeCount,			 0.035f,   -0.3f, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}