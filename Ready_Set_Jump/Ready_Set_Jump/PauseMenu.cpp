/**
  *  \file PauseMenu.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\\digipen.edu
  *  \par Course: csd1451
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
*/
#include "PauseMenu.hpp"
#include "UI.hpp"
#include "GameStateManager.hpp"
namespace PauseMenu {
	UIText* buttonText[4];

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
	}
	void PauseMenuBehaviour(mousePos mouse) {
		//sets behaviour what each button does
		AEGfxSetCamPosition(0.f, 0.f);
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			if (buttonText[1]->MouseCollision(mouse)) level_state = PLAYING;// return to gaming
			if (buttonText[2]->MouseCollision(mouse)) e_next_state = GS_MAINMENU;// return to main menu
			if (buttonText[3]->MouseCollision(mouse)) e_next_state = GS_QUIT;// quits the game
		}

		/* text box animation to fade in/out on hover*/
		if (buttonText[1]->MouseCollision(mouse) && buttonText[1]->GetTextBoxAlpha() < 1.f) {
			buttonText[1]->TextBoxFadeIn();
		}else if (!(buttonText[1]->MouseCollision(mouse))) buttonText[1]->TextBoxFadeOut();

		if (buttonText[2]->MouseCollision(mouse) && buttonText[2]->GetTextBoxAlpha() < 1.f) {
			buttonText[2]->TextBoxFadeIn();
		}else if (!(buttonText[2]->MouseCollision(mouse))) buttonText[2]->TextBoxFadeOut();

		if (buttonText[3]->MouseCollision(mouse) && buttonText[3]->GetTextBoxAlpha() < 1.f) {
			buttonText[3]->TextBoxFadeIn();
		}else if (!(buttonText[3]->MouseCollision(mouse))) buttonText[3]->TextBoxFadeOut();

	}
	void DrawPauseMenu() {//draws the buttons and text
		backGround->DrawObj();

		for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i)
			buttonText[i]->DrawObj();
	}
	void FreePauseMenu() {
		for (size_t i{}; i < sizeof buttonText / sizeof buttonText[0]; ++i)
			delete buttonText[i];

		delete backGround;
	}
}