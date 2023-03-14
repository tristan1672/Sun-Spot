#include "MainMenu.hpp"
UIText selectLevelText;
UIText quitText;
UIText guideText;
UIText **levels;

void Menu_Load() {
	MakeMesh();
	levels = new UIText * [4] {};
	for (int i = 0; i < 4; ++i) {
		levels[i] = new UIText[4]{};
	}
}

void Menu_Initialize() {
	selectLevelText = UIText("Select Level", { -0.26f, 0.3f },{1.f,1.f},White, true, GreenTea);
	quitText = UIText("Quit", { -0.09f, -0.5f }, { 1.f,1.f }, White, true, GreenTea);
	guideText= UIText("How To Play", { -0.23f, -0.1f }, { 1.f,1.f }, White, true, GreenTea);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int levelcount = i * 4 + j + 1;
			levels[i][j] = UIText(std::to_string(levelcount), { (j * 0.2f - 0.3f), (-i * 0.3f + 0.4f) }, { 1.f,1.f }, White,true, GreenTea);
			levels[i][j].TextBoxActive = false;
			levels[i][j].Active = false;
		}
	}
}

void Menu_Update() {
	mousePos mouse{};
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
	// UI button checks
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {

		if ( selectLevelText.MouseCollision({ mouse.ClickX ,mouse.ClickY})) {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					levels[i][j].TextBoxActive = true;
					levels[i][j].Active = true;
				}
			}
			selectLevelText.TextBoxActive = false; selectLevelText.Active = false;
			quitText.TextBoxActive = false; quitText.Active = false;
			guideText.TextBoxActive = false; guideText.Active = false;
		}
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY })) {
					int levelcount = i * 4 + j + 1;
					fileToLoad = "Assets/Script/Level";
					fileToLoad += std::to_string(levelcount);
					fileToLoad += ".txt";
					next = GS_LEVEL;
				}
			}
		}

		if (quitText.MouseCollision({ mouse.ClickX ,mouse.ClickY })) {
			next = GS_QUIT;
		}
	}

	/*
		Fade animation calls
	*/
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY }) && levels[i][j].GetTextBoxAlpha() <1.f) {
				levels[i][j].TextBoxFadeIn();
			}else if(!(levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY }))) levels[i][j].TextBoxFadeOut();
		}
	}
	if (selectLevelText.MouseCollision({ mouse.ClickX ,mouse.ClickY }) && selectLevelText.GetTextBoxAlpha() < 1.f) {
		selectLevelText.TextBoxFadeIn();
	}else if(!(selectLevelText.MouseCollision({ mouse.ClickX ,mouse.ClickY }))) selectLevelText.TextBoxFadeOut();

	if (quitText.MouseCollision({ mouse.ClickX ,mouse.ClickY }) && quitText.GetTextBoxAlpha() < 1.f) {
		quitText.TextBoxFadeIn();
	}else if(!(quitText.MouseCollision({ mouse.ClickX ,mouse.ClickY }))) quitText.TextBoxFadeOut();

	if (guideText.MouseCollision({ mouse.ClickX ,mouse.ClickY }) && guideText.GetTextBoxAlpha() < 1.f) {
		guideText.TextBoxFadeIn();
	}else if(!(guideText.MouseCollision({ mouse.ClickX ,mouse.ClickY }))) guideText.TextBoxFadeOut();



}

void Menu_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	selectLevelText.DrawObj();
	quitText.DrawObj();
	guideText.DrawObj();

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			levels[i][j].DrawObj();
		}
	}
}

void Menu_Free() {

}

void Menu_Unload() {
	for (int i = 0; i < 4; ++i) {
		delete[] levels[i];
	}
	delete[] levels;
	AEGfxMeshFree(pMesh);
}