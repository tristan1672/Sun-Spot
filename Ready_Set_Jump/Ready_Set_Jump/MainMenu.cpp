#include "MainMenu.hpp"
UIText* selectLevelText;
UIText* quitText;
UIText* guideText;

void Menu_Load() {
	MakeMesh();
	AEGfxSetCamPosition(0.f, 0.f);
}

void Menu_Initialize() {
	std::cout << "init\n";
	selectLevelText = new UIText{ UIText("Select Level", { -0.26f, 0.3f },{1.f,1.f},White, true, GreenTea) };
	quitText = new UIText {UIText("Quit", { -0.09f, -0.5f }, { 1.f,1.f }, White, true, GreenTea)};
	guideText = new UIText{ UIText("How To Play", { -0.23f, -0.1f }, { 1.f,1.f }, White, true, GreenTea) };
	LevelSelect::CreateLevelSelectUI();

}

void Menu_Update() {
	mousePos mouse{};
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
	// UI button checks
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {

		if ( selectLevelText->MouseCollision({ mouse.ClickX ,mouse.ClickY})) {
			LevelSelect::SetLevelSelectActive();
			selectLevelText->TextBoxActive = false; selectLevelText->Active = false;
			quitText->TextBoxActive = false; quitText->Active = false;
			guideText->TextBoxActive = false; guideText->Active = false;
		}

		LevelSelect::ButtonSelectBehaviour(mouse);

		if (quitText->MouseCollision({ mouse.ClickX ,mouse.ClickY })) {
			next = GS_QUIT;
		}
	}

	/*
		Fade animation calls
	*/
	LevelSelect::LSButtonAnimation(mouse);
	if (selectLevelText->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && selectLevelText->GetTextBoxAlpha() < 1.f) {
		selectLevelText->TextBoxFadeIn();
	}else if(!(selectLevelText->MouseCollision({ mouse.ClickX ,mouse.ClickY }))) selectLevelText->TextBoxFadeOut();

	if (quitText->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && quitText->GetTextBoxAlpha() < 1.f) {
		quitText->TextBoxFadeIn();
	}else if(!(quitText->MouseCollision({ mouse.ClickX ,mouse.ClickY }))) quitText->TextBoxFadeOut();

	if (guideText->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && guideText->GetTextBoxAlpha() < 1.f) {
		guideText->TextBoxFadeIn();
	}else if(!(guideText->MouseCollision({ mouse.ClickX ,mouse.ClickY }))) guideText->TextBoxFadeOut();



}

void Menu_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	selectLevelText->DrawObj();
	quitText->DrawObj();
	guideText->DrawObj();
	LevelSelect::DrawLevelButton();
}

void Menu_Free() {
	LevelSelect::FreeLevelButton();
	delete selectLevelText;
	delete quitText;
	delete guideText;
}

void Menu_Unload() {

	AEGfxMeshFree(pMesh);
}