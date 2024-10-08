/*****************************************************************
  *  \file MainMenu.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)              (50%)
  *				     - Main Author  
  *                : Peh Zong Lin Adrian (p.zonglinadrian) (50%)
  *                  - Sub Author
  *					 - Added particles 
  *                  - Automated text position and cleaned it up
  *                : Tristan Tham Rui Hong (t.tham)         (10%)
  *                   - Sub Author
  *                   - Added Audio
  *
  *  \brief
  * Main Menu Scene
  * All content � 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/
#include "MainMenu.hpp"

UIText* titleText[3];

UIText* buttonText[4];

UIText* exitConfirmation[3];

int e_uiState;

static int frameCounter;
GameObject* menuParticleList;

AEAudio e_backgroudAudio;
AEAudioGroup e_backgroundAudioGroup;

AEAudio buttonAudio;

void Menu_Load() {// loads in the mesh
	MakeMesh();
	AEGfxSetCamPosition(0.f, 0.f);
	LevelSelect::LoadLSTexture();

	menuParticleList = new GameObject[MAX_PARTICLE_NUMBER];

	e_backgroudAudio = AEAudioLoadMusic("Assets/Sound/MenuBackground.mp3");
	e_backgroundAudioGroup = AEAudioCreateGroup();
	AEAudioPlay(e_backgroudAudio, e_backgroundAudioGroup, 0.2f, 1, -1);
	AEAudioPauseGroup(e_backgroundAudioGroup);

	buttonAudio = AEAudioLoadMusic("Assets/Sound/Button_Click.mp3");
}

void Menu_Initialize() {

	AEAudioResumeGroup(e_backgroundAudioGroup);

	isTutorial = false;
	e_uiState = MAIN;
	e_move = 0;
	e_skip = 0;
	// allocate memory for game title text
	titleText[0] = new UIText{UIText("Ready?", {0.f, 0.65f}, {1.4f,1.f}, Red)};
	titleText[1] = new UIText{UIText("Set.", {0.f, 0.65f}, {1.4f,1.f}, Yellow)};
	titleText[2] = new UIText{UIText("Jump!", {0.f, 0.65f}, {1.4f,1.f}, GreenTea)};

	AEVec2 titleSize{};
	AEVec2 firstWordSize{};
	AEVec2 secondWordSize{};
	char title[] = "Ready?Set.Jump!";
	char word1[] = "Ready?";
	char word2[] = "Set.";
	AEGfxGetPrintSize(e_fontID, title, 1.4f, titleSize.x, titleSize.y);
	AEGfxGetPrintSize(e_fontID, word1, 1.4f, firstWordSize.x, firstWordSize.y);
	AEGfxGetPrintSize(e_fontID, word2, 1.4f, secondWordSize.x, secondWordSize.y);

	titleText[0]->SetPosition({ -0.5f * titleSize.x + titleText[0]->GetPosition().x, titleText[0]->GetPosition().y });
	titleText[1]->SetPosition({ -0.5f * titleSize.x + firstWordSize.x + titleText[1]->GetPosition().x, titleText[1]->GetPosition().y });
	titleText[2]->SetPosition({ -0.5f * titleSize.x + firstWordSize.x + secondWordSize.x + titleText[2]->GetPosition().x, titleText[2]->GetPosition().y });

	//allocate memory for button
	buttonText[0] = new UIText{ UIText("Select Level", { 0.f, 0.3f },{1.f,1.f},White, true, GreenTea) };
	buttonText[1] = new UIText{ UIText("How To Play", { 0.f, -0.0f }, { 1.f,1.f }, White, true, GreenTea) };
	buttonText[2] = new UIText{ UIText("Credits", { 0.f, -0.3f }, { 1.f,1.f }, White, true, GreenTea) };
	buttonText[3] = new UIText{ UIText("Quit", { 0.f, -0.6f }, { 1.f,1.f }, White, true, GreenTea) };

	exitConfirmation[0] = new UIText{ UIText("Are You Sure?", { 0.f, 0.3f }, { 1.f,1.f }, White) };
	exitConfirmation[1] = new UIText{ UIText("Yes", {-0.2f, -0.2f }, { 1.f,1.f }, White, true, GreenTea) };
	exitConfirmation[2] = new UIText{ UIText("No", { 0.2f, -0.2f }, { 1.f,1.f }, White, true, GreenTea) };

	for (unsigned int i{}; i < 3; ++i) {
		AEVec2 size{};
		AEGfxGetPrintSize(e_fontID, exitConfirmation[i]->GetText(), exitConfirmation[i]->GetScale().x, size.x, size.y);
		exitConfirmation[i]->SetPosition({ -0.5f * size.x + exitConfirmation[i]->GetPosition().x, exitConfirmation[i]->GetPosition().y });
	}


	for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
		exitConfirmation[i]->Active = false;
		exitConfirmation[i]->TextBoxActive = false;
	}


	for (unsigned int i{}; i < 4; ++i) {
		AEVec2 size{};
		AEGfxGetPrintSize(e_fontID, buttonText[i]->GetText(), buttonText[i]->GetScale().x, size.x, size.y);
		buttonText[i]->SetPosition({ -0.5f * size.x + buttonText[i]->GetPosition().x, buttonText[i]->GetPosition().y });
	}
	
	//calls level select and allocate its memory
	LevelSelect::InitLSTexture();
	LevelSelect::CreateLevelSelectUI();

	unsigned int waves = 20;
	unsigned int numPerWave = 5;
	float intervalWidth = 1.f / static_cast<float>(waves - 1) * static_cast<float>(WINDOW_WIDTH) * 2.f;

	for (unsigned int i{}; i < waves; ++i) {

		for (unsigned int j{}; j < numPerWave; ++j) {
			AEVec2 particalPosition = { static_cast<float>( - 0.5f * WINDOW_WIDTH + i * intervalWidth), static_cast<float>(rand() % WINDOW_HEIGHT - HALVE_WINDOW_HEIGHT) };
			AEVec2 particleVelocity = { -static_cast<float>(rand() % 5 + 2) , 0.0f };
			int randScale = rand() % 8 + 2;

			*(menuParticleList + MAX_PARTICLE_NUMBER - 1 - (i * numPerWave + j)) = CreateParticle(particalPosition.x, particalPosition.y, particleVelocity.x, particleVelocity.y, static_cast<float>(randScale));
		}
	}
}

void Menu_Update() {

	// No check for dead elements as it takes 136.5 sec for the entire array to be cycled through. By then the 1st particle would have been killed.
	if (frameCounter % 4) {

		AEVec2 particalPosition = { static_cast<float>(WINDOW_WIDTH), static_cast<float>(rand() % WINDOW_HEIGHT - HALVE_WINDOW_HEIGHT) };
		AEVec2 particleVelocity = { -static_cast<float>(rand() % 5 + 2) , 0.0f };
		int randScale = rand() % 8 + 2;

		*(menuParticleList + (static_cast<int>(frameCounter * 0.25) % MAX_PARTICLE_NUMBER)) = CreateParticle(particalPosition.x, particalPosition.y, particleVelocity.x, particleVelocity.y, static_cast<float>(randScale));
	}

	mousePos mouse{};
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);//get current mouse position
	// UI button checks
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {// check if lmb is pressed

		if (buttonText[2]->MouseCollision(mouse)) {// checks if credit button was clicked, loads the credit scene
			AEAudioPlay(buttonAudio, e_platformAudioGroup, 0.3f, 1, 0);

			for (unsigned int i{}; i < 3; ++i) {
				titleText[i]->Active = false;
			}

			for (unsigned int i{}; i < 4; ++i) {
				buttonText[i]->TextBoxActive = false; 
				buttonText[i]->Active = false;
			}
			e_next_state = GS_CREDITS;
		}

		if (buttonText[0]->MouseCollision(mouse)) // checks if level select button was pressed, shows the level select menu
		{
			AEAudioPlay(buttonAudio, e_platformAudioGroup, 0.3f, 1, 0);
			e_uiState = LS;
			LevelSelect::SetLevelSelectActive();

			for (unsigned int i{}; i < 4; ++i) {
				buttonText[i]->TextBoxActive = false;
				buttonText[i]->Active = false;
			}

			for (unsigned int i{}; i < 3; ++i) 
			{
				titleText[i]->Active = false;
			}
		}
		if (LevelSelect::BackButtonBehaviour(mouse)) // back button behaviour
		{
			if (e_uiState == LS)
			{
				e_uiState = MAIN;
				LevelSelect::SetLevelSelectInActive();
				for (unsigned int i{}; i < 4; ++i) {
					buttonText[i]->TextBoxActive = true;
					buttonText[i]->Active = true;
				}

				for (unsigned int i{}; i < 3; ++i) 
				{
					titleText[i]->Active = true;
				}
			}
			if (e_uiState == STAGE)
			{
				e_uiState = LS;
				LevelSelect::SetLevelSelectActive();
				for (unsigned int i{}; i < 4; ++i) {
					buttonText[i]->TextBoxActive = false;
					buttonText[i]->Active = false;
				}
			}
			
		}
		if (buttonText[1]->MouseCollision(mouse))// if tutorial button was pressed, loads tutorial level
		{
			fileToLoad = "Assets/Script/LevelTutorial.txt";
			levelNumber = 0;
			isTutorial = true;
			e_next_state = GS_LEVEL;
		}
		

		LevelSelect::ButtonSelectBehaviour(mouse);

		if (buttonText[3]->MouseCollision(mouse)) // quits the game if quit button is pressed
		{
			for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
				exitConfirmation[i]->Active = true;
				exitConfirmation[i]->TextBoxActive = true;
			}
			for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
				buttonText[i]->Active = false;
				buttonText[i]->TextBoxActive = false;
			}
			for (size_t i{}; i < sizeof titleText / sizeof titleText[0]; ++i) {
				titleText[i]->Active = false;
			}

			exitConfirmation[0]->TextBoxActive = false;
		}

		if (exitConfirmation[1]->MouseCollision(mouse)) {
			e_next_state = GS_QUIT;
		}

		if (exitConfirmation[2]->MouseCollision(mouse)) {
			for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
				exitConfirmation[i]->Active = false;
				exitConfirmation[i]->TextBoxActive = false;
			}
			for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
				buttonText[i]->Active = true;
				buttonText[i]->TextBoxActive = true;
			}
			for (size_t i{}; i < sizeof titleText / sizeof titleText[0]; ++i) {
				titleText[i]->Active = true;
			}
		}

		if (LevelSelect::StartButtonBehaviour(mouse))// goes to said level when level button is pressed
		{
			//AEAudioStopGroup(e_backgroundAudioGroup);
			e_next_state = GS_LEVEL;
		}
	}

	/*
		Fade animation for text box on hover
	*/
	LevelSelect::LSButtonAnimation(mouse);
	for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
		if (buttonText[i]->MouseCollision(mouse) && buttonText[i]->GetTextBoxAlpha() < 1.f) {
			buttonText[i]->TextBoxFadeIn();
		}else if(!(buttonText[i]->MouseCollision(mouse))) buttonText[i]->TextBoxFadeOut();
	}
	for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
		if (exitConfirmation[i]->MouseCollision(mouse) && exitConfirmation[i]->GetTextBoxAlpha() < 1.f) {
			exitConfirmation[i]->TextBoxFadeIn();
		}else if(!(exitConfirmation[i]->MouseCollision(mouse))) exitConfirmation[i]->TextBoxFadeOut();
	}

	// Update particle effect for background
	UpdateParticle(menuParticleList);

	++frameCounter;
}

void Menu_Draw() {// draws the UI buttons
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	LevelSelect::DrawLSTexture();
	DrawParticle(menuParticleList);

	for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) buttonText[i]->DrawObj();
	for (size_t i{}; i < sizeof titleText / sizeof titleText[0]; ++i) titleText[i]->DrawObj();
	LevelSelect::DrawLevelButton();
	for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) exitConfirmation[i]->DrawObj();
}

void Menu_Free() {// frees allocated memory on free
	LevelSelect::FreeLevelButton();
	UnloadPArticle(menuParticleList);
	for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) delete buttonText[i];
	for (size_t i{}; i < sizeof titleText / sizeof titleText[0]; ++i) delete titleText[i];
	for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) delete exitConfirmation[i];
	AEAudioPauseGroup(e_backgroundAudioGroup);
}

void Menu_Unload() {// frees allocated memory on unload
	
	LevelSelect::UnloadLSTexture();
	AEGfxMeshFree(pMesh);
}