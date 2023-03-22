#include "LevelSelect.hpp"
namespace LevelSelect {
	UIText** levels{ nullptr };
	UIText* backButton{nullptr};
	void CreateLevelSelectUI() {
		levels = new UIText * [4] {};
		for (int i = 0; i < 4; ++i) {
			levels[i] = new UIText[4]{};
		}

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				int levelcount = i * 4 + j + 1;
				levels[i][j] = UIText(std::to_string(levelcount), { (j * 0.2f - 0.3f), (-i * 0.3f + 0.4f) }, { 1.f,1.f }, White, true, GreenTea);
				levels[i][j].TextBoxActive = false;
				levels[i][j].Active = false;
			}
		}
		backButton = new UIText{ UIText("Back", { -0.8f, -0.7f },{1.f,1.f},White, true, GreenTea) };
		backButton->TextBoxActive = false;
		backButton->Active = false;
	}

	void ButtonSelectBehaviour(mousePos mouse) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (levels[i][j].MouseCollision(mouse)) {
					int levelcount = i * 4 + j + 1;
					fileToLoad = "Assets/Script/Level";
					fileToLoad += std::to_string(levelcount);
					fileToLoad += ".txt";
					next = GS_LEVEL;
				}
			}
		}
	}
	void LSButtonAnimation(mousePos mouse) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY }) && levels[i][j].GetTextBoxAlpha() < 1.f) {
					levels[i][j].TextBoxFadeIn();
				}
				else if (!(levels[i][j].MouseCollision({ mouse.ClickX ,mouse.ClickY }))) levels[i][j].TextBoxFadeOut();
			}
		}
		if (backButton->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && backButton->GetTextBoxAlpha() < 1.f) {
			backButton->TextBoxFadeIn();
		}
		else if (!backButton->MouseCollision({ mouse.ClickX ,mouse.ClickY })) backButton->TextBoxFadeOut();
	}
	void DrawLevelButton() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				levels[i][j].DrawObj();
			}
		}
		backButton->DrawObj();
	}
	void FreeLevelButton() {
		for (int i = 0; i < 4; ++i) {
			delete[] levels[i];
		}
		delete[] levels;
		delete backButton;
	}
	void SetLevelSelectActive() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				LevelSelect::levels[i][j].TextBoxActive = true;
				LevelSelect::levels[i][j].Active = true;
			}
		}
		backButton->TextBoxActive = true;
		backButton->Active = true;
	}
	void SetLevelSelectInActive() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				LevelSelect::levels[i][j].TextBoxActive = false;
				LevelSelect::levels[i][j].Active = false;
			}
		}
		backButton->TextBoxActive = false;
		backButton->Active = false;
	}
	bool BackButtonBehaviour(mousePos mouse) {
		if (backButton->MouseCollision(mouse)) {
			SetLevelSelectInActive();
			return true;
		}
		return false;
	}
}