/**
  *  \file MainMenu.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  * Main Menu Scene
  *
*/
#include "MainMenu.hpp"
#include "SaveManager.hpp"
#include "Credits.hpp"

UIText* selectLevelText;
UIText* quitText;
UIText* guideText;
UIText* titleText[3];
UIText* creditText;

int e_uiState;

void Menu_Load() {// loads in the mesh
	MakeMesh();
	AEGfxSetCamPosition(0.f, 0.f);
	LevelSelect::LoadLSTexture();
}

void Menu_Initialize() {
	isTutorial = false;
	e_uiState = MAIN;
	e_move = 0;
	e_skip = 0;
	// allocate memory for game title text
	titleText[0] = new UIText{UIText("Ready?", {-0.5f, 0.65f}, {1.4f,1.f}, Red)};
	titleText[1] = new UIText{UIText("Set.", {-0.07f, 0.65f}, {1.4f,1.f}, Yellow)};
	titleText[2] = new UIText{UIText("Jump!", {0.2f, 0.65f}, {1.4f,1.f}, GreenTea)};

	//allocate memory for button
	selectLevelText = new UIText{ UIText("Select Level", { -0.26f, 0.3f },{1.f,1.f},White, true, GreenTea) };
	guideText = new UIText{ UIText("How To Play", { -0.23f, -0.0f }, { 1.f,1.f }, White, true, GreenTea) };
	creditText = new UIText{ UIText("Credits", { -0.15f, -0.3f }, { 1.f,1.f }, White, true, GreenTea) };
	quitText = new UIText {UIText("Quit", { -0.09f, -0.6f }, { 1.f,1.f }, White, true, GreenTea)};
	
	//calls level select and allocate its memory
	LevelSelect::InitLSTexture();
	LevelSelect::CreateLevelSelectUI();
}

void Menu_Update() {
	mousePos mouse{};
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);//get current mouse position
	// UI button checks
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {// check if lmb is pressed

		if (creditText->MouseCollision(mouse)) {// checks if credit button was clicked, loads the credit scene
			for (unsigned int i{}; i < 3; ++i) {
				titleText[i]->Active = false;
			}
			selectLevelText->TextBoxActive = false; selectLevelText->Active = false;
			quitText->TextBoxActive = false; quitText->Active = false;
			guideText->TextBoxActive = false; guideText->Active = false;
			creditText->TextBoxActive = false; creditText->Active = false;
			e_next_state = GS_CREDITS;
		}

		if (selectLevelText->MouseCollision(mouse)) // checks if level select button was pressed, shows the level select menu
		{
			e_uiState = LS;
			LevelSelect::SetLevelSelectActive();

			selectLevelText->TextBoxActive = false; selectLevelText->Active = false;
			quitText->TextBoxActive = false; quitText->Active = false;
			guideText->TextBoxActive = false; guideText->Active = false;
			creditText->TextBoxActive = false; creditText->Active = false;

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
				selectLevelText->TextBoxActive = true; selectLevelText->Active = true;
				quitText->TextBoxActive = true; quitText->Active = true;
				guideText->TextBoxActive = true; guideText->Active = true;
				creditText->TextBoxActive = true; creditText->Active = true;

				for (unsigned int i{}; i < 3; ++i) 
				{
					titleText[i]->Active = true;
				}
			}
			if (e_uiState == STAGE)
			{
				e_uiState = LS;
				LevelSelect::SetLevelSelectActive();
				selectLevelText->TextBoxActive = false; selectLevelText->Active = false;
				quitText->TextBoxActive = false; quitText->Active = false;
				guideText->TextBoxActive = false; guideText->Active = false;
				creditText->TextBoxActive = false; creditText->Active = false;
			}
			
		}
		if (guideText->MouseCollision(mouse))// if guide button was pressed, loads tutorial level
		{
			fileToLoad = "Assets/Script/LevelTutorial.txt";
			levelNumber = 0;
			isTutorial = true;
			e_next_state = GS_LEVEL;
		}
		

		LevelSelect::ButtonSelectBehaviour(mouse);

		if (quitText->MouseCollision(mouse)) // quits the game if quit button is pressed
		{
			e_next_state = GS_QUIT;
		}
		if (LevelSelect::StartButtonBehaviour(mouse))// goes to said level when level button is pressed
		{
			e_next_state = GS_LEVEL;
		}
	}

	/*
		Fade animation for text box on hover
	*/
	LevelSelect::LSButtonAnimation(mouse);

	if (selectLevelText->MouseCollision(mouse) && selectLevelText->GetTextBoxAlpha() < 1.f) {
		selectLevelText->TextBoxFadeIn();
	}else if(!(selectLevelText->MouseCollision(mouse))) selectLevelText->TextBoxFadeOut();

	if (quitText->MouseCollision(mouse) && quitText->GetTextBoxAlpha() < 1.f) {
		quitText->TextBoxFadeIn();
	}else if(!(quitText->MouseCollision(mouse))) quitText->TextBoxFadeOut();

	if (guideText->MouseCollision(mouse) && guideText->GetTextBoxAlpha() < 1.f) {
		guideText->TextBoxFadeIn();
	}else if(!(guideText->MouseCollision(mouse))) guideText->TextBoxFadeOut();

	if (creditText->MouseCollision(mouse) && creditText->GetTextBoxAlpha() < 1.f) {
		creditText->TextBoxFadeIn();
	}else if (!(creditText->MouseCollision(mouse))) creditText->TextBoxFadeOut();

}

void Menu_Draw() {// draws the UI buttons
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	LevelSelect::DrawLSTexture();
	selectLevelText->DrawObj();
	quitText->DrawObj();
	guideText->DrawObj();
	creditText->DrawObj();
	for (size_t i{}; i < sizeof titleText / sizeof titleText[0]; ++i) titleText[i]->DrawObj();
	LevelSelect::DrawLevelButton();
}

void Menu_Free() {// frees allocated memory on free
	LevelSelect::FreeLevelButton();
	delete selectLevelText;
	delete quitText;
	delete guideText;
	delete creditText;
	for (size_t i{}; i < sizeof titleText / sizeof titleText[0]; ++i) delete titleText[i];
}

void Menu_Unload() {// frees allocated memory on unload
	
	LevelSelect::UnloadLSTexture();
	AEGfxMeshFree(pMesh);
}