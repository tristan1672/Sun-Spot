#include "PauseMenu.hpp"
#include "UI.hpp"
#include "GameStateManager.hpp"
namespace PauseMenu {
	UIText* pauseText;
	UIText* resumeText;
	UIText* mainMenuText;
	UIText* quitText;
	GameObject* backGround;
	void CreatePauseMenu() {
		pauseText = new UIText{ UIText("Paused", { -0.15f, 0.6f }, { 1.f,1.f }, White) };

		resumeText = new UIText{ UIText("Resume", { -0.15f, 0.3f }, { 1.f,1.f }, White, true, GreenTea) };
		mainMenuText = new UIText{ UIText("Main Menu", { -0.2f, 0.f }, { 1.f,1.f }, White, true, GreenTea) };
		quitText = new UIText{ UIText("Quit", { -0.09f, -0.3f }, { 1.f,1.f }, White, true, GreenTea) };

		backGround = new GameObject{ GameObject({-0.1f,0.f},{2000,1000},Black) };
	}
	void PauseMenuBehaviour(mousePos mouse) {
		AEGfxSetCamPosition(0.f, 0.f);
		if (AEInputCheckTriggered(AEVK_LBUTTON)) {
			if (resumeText->MouseCollision(mouse)) level_state = PLAYING;
			if (mainMenuText->MouseCollision(mouse)) next = GS_MAINMENU;
			if (quitText->MouseCollision(mouse)) next = GS_QUIT;
		}

		if (resumeText->MouseCollision(mouse) && resumeText->GetTextBoxAlpha() < 1.f) {
			resumeText->TextBoxFadeIn();
		}else if (!(resumeText->MouseCollision(mouse))) resumeText->TextBoxFadeOut();

		if (mainMenuText->MouseCollision(mouse) && mainMenuText->GetTextBoxAlpha() < 1.f) {
			mainMenuText->TextBoxFadeIn();
		}else if (!(mainMenuText->MouseCollision(mouse))) mainMenuText->TextBoxFadeOut();

		if (quitText->MouseCollision(mouse) && quitText->GetTextBoxAlpha() < 1.f) {
			quitText->TextBoxFadeIn();
		}else if (!(quitText->MouseCollision(mouse))) quitText->TextBoxFadeOut();

	}
	void DrawPauseMenu() {
		backGround->DrawObj();
		pauseText->DrawObj();
		quitText->DrawObj();
		resumeText->DrawObj();
		mainMenuText->DrawObj();
	}
	void FreePauseMenu() {
		delete pauseText;
		delete quitText;
		delete resumeText;
		delete mainMenuText;
		delete backGround;
	}
}