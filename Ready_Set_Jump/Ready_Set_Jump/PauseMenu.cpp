/*****************************************************************
  *  \file PauseMenu.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)              (90%)
  *					 - Main Author
  *                : Peh Zong Lin Adrian (p.zonglinadrian) (10%)
  *                  - Sub Author
  *                  - Automated text position and cleaned it up
  *
  *  \brief
  *  Defination of functions that will make the pause menu draw
  *  -CreatePauseMenu()
  *		creates and allocates memories for pasue menu objs
  * -PauseMenuBehaviour(mousePos mouse)
  *		when resume button was pressed, the game will resume
  *		when main menu is pressed, goes to the main menu
  *		when quit button was pressed, quit the game
  * -DrawPauseMenu()
  *		draws all objects in pause menu
  * -FreePauseMenu()
  *		frees memories allocated
  * 
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include "PauseMenu.hpp"
#include "UI.hpp"
#include "GameStateManager.hpp"

namespace PauseMenu {
	UIText* buttonText[4];
	UIText* exitConfirmation[3];
	int nextState{};

	GameObject* backGround;
	void CreatePauseMenu() {
		// allocate memory for each button and text
		buttonText[0] = new UIText{ UIText("PAUSED", { 0.f, 0.5f }, { 1.f,1.f }, White) };
		buttonText[1] = new UIText{ UIText("Resume", { 0.f, 0.25f }, { 1.f,1.f }, White, true, GreenTea) };
		buttonText[2] = new UIText{ UIText("Main Menu", { 0.f, 0.05f }, { 1.f,1.f }, White, true, GreenTea) };
		buttonText[3] = new UIText{ UIText("Quit", { 0.f, -0.15f }, { 1.f,1.f }, White, true, GreenTea) };

		for (unsigned int i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
			AEVec2 size{};
			AEGfxGetPrintSize(e_fontID, buttonText[i]->GetText(), buttonText[i]->GetScale().x, size.x, size.y);
			buttonText[i]->SetPosition({ -0.5f * size.x + buttonText[i]->GetPosition().x, buttonText[i]->GetPosition().y });
		}

		backGround = new GameObject{ GameObject({-0.1f,0.f},{2000,1000},Black) };

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
	}
	void PauseMenuBehaviour(mousePos mouse) {
		//sets behaviour what each button does
		AEGfxSetCamPosition(0.f, 0.f);
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			if (buttonText[1]->MouseCollision(mouse)) level_state = PLAYING;// return to gaming
			if (buttonText[2]->MouseCollision(mouse)) {//shows exit confirmation
				for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
					exitConfirmation[i]->Active = true;
					exitConfirmation[i]->TextBoxActive = true;
				}
				exitConfirmation[0]->TextBoxActive = false;
				for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
					buttonText[i]->Active = false;
					buttonText[i]->TextBoxActive = false;
				}
				nextState = GS_MAINMENU;
			}

			if (buttonText[3]->MouseCollision(mouse)) {//shows exit confirmation
				for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
					exitConfirmation[i]->Active = true;
					exitConfirmation[i]->TextBoxActive = true;
				}
				exitConfirmation[0]->TextBoxActive = false;
				for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
					buttonText[i]->Active = false;
					buttonText[i]->TextBoxActive = false;
				}
				nextState = GS_QUIT;
			}

			if (exitConfirmation[1]->MouseCollision(mouse)) {
				e_next_state = nextState;
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
				buttonText[0]->TextBoxActive = false;
			}
		}

		/* text box animation to fade in/out on hover*/
		for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i) {
			if (buttonText[i]->MouseCollision(mouse) && buttonText[i]->GetTextBoxAlpha() < 1.f) {
				buttonText[i]->TextBoxFadeIn();
			}else if (!(buttonText[i]->MouseCollision(mouse))) buttonText[i]->TextBoxFadeOut();
		}
		for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) {
			if (exitConfirmation[i]->MouseCollision(mouse) && exitConfirmation[i]->GetTextBoxAlpha() < 1.f) {
				exitConfirmation[i]->TextBoxFadeIn();
			}
			else if (!(exitConfirmation[i]->MouseCollision(mouse))) exitConfirmation[i]->TextBoxFadeOut();
		}

	}
	void DrawPauseMenu() {//draws the buttons and text
		backGround->DrawObj();

		for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i)
			buttonText[i]->DrawObj();
		for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i)
			exitConfirmation[i]->DrawObj();
	}
	void FreePauseMenu() {
		for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i)
			delete buttonText[i];

		delete backGround;
		for (size_t i{}; i < sizeof exitConfirmation / sizeof exitConfirmation[0]; ++i) delete exitConfirmation[i];
	}
}