#include "LevelSelect.hpp"
#include "SaveManager.hpp"

namespace LevelSelect {
	UIText** levels{ nullptr };
	UIText* backButton{ nullptr };
	UIText* startButton{ nullptr };

	AEGfxTexture* timeTexture;
	AEGfxTexture* frameTexture;

	GameObject Frame, Time;

	int jump{}, collc{}, difficulty{},totalscore{};
	float time{};
	bool attempt{};

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
		startButton = new UIText{ UIText("Start", { 0.6f, -0.7f },{1.f,1.f},White, true, GreenTea) };

		startButton->TextBoxActive = false;
		startButton->Active = false;

		backButton->TextBoxActive = false;
		backButton->Active = false;
	}

	void ButtonSelectBehaviour(mousePos mouse) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (levels[i][j].MouseCollision(mouse)) {
					levelNumber = i * 4 + j + 1;
					e_uiState = STAGE;
					SetLevelSelectInActive();
					StagingScreen(levelNumber);
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

		if (startButton->MouseCollision({ mouse.ClickX ,mouse.ClickY }) && startButton->GetTextBoxAlpha() < 1.f) {
			startButton->TextBoxFadeIn();
		}
		else if (!startButton->MouseCollision({ mouse.ClickX ,mouse.ClickY })) startButton->TextBoxFadeOut();
	}
	void DrawLevelButton() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				levels[i][j].DrawObj();
			}
		}
		backButton->DrawObj();
		startButton->DrawObj();
	}
	void FreeLevelButton() {
		for (int i = 0; i < 4; ++i) {
			delete[] levels[i];
		}
		delete[] levels;
		delete backButton;
		delete startButton;
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

		startButton->TextBoxActive = false;
		startButton->Active = false;
	}
	bool BackButtonBehaviour(mousePos mouse) {
		if (backButton->MouseCollision(mouse)) 
		{
			Frame.SetTexture(nullptr);
			Time.SetTexture(nullptr);
			return true;
		}
		return false;
	}

	bool StartButtonBehaviour(mousePos mouse)
	{
		if (startButton->MouseCollision(mouse))
		{
			return true;
		}
		return false;
	}

	void StagingScreen(int levelcount)
	{
		startButton->TextBoxActive = true;
		startButton->Active = true;
		backButton->TextBoxActive = true;
		backButton->Active = true;
		Frame.SetTexture(frameTexture);
		Time.SetTexture(timeTexture);

		fileToLoad = "Assets/Script/Level";
		fileToLoad += std::to_string(levelcount);
		fileToLoad += ".txt";

		Save::GetSaveValue(levelNumber, difficulty, jump, collc, time, totalscore, attempt);

		std::cout << "Level:dsa " << levelNumber << std::endl;
		std::cout << "Jumps: " << jump << std::endl;
		std::cout << "Collectibles: " << collc << std::endl;
		std::cout << "Time: " << time << std::endl;
		std::cout << "Attempted: " << attempt << std::endl;
		
	}

	void InitLSTexture()
	{
		Frame = GameObject({ 0.0f, 0.0f }, { 700.0f, 400.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
		Time = GameObject({ -220.f, -100.f }, { 70.0f, 80.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.f, AE_GFX_RM_TEXTURE);
	}

	void LoadLSTexture()
	{
		timeTexture = AEGfxTextureLoad("Assets/Images/Time.png");
		frameTexture = AEGfxTextureLoad("Assets/Images/ScoreFrame.png");
	}

	void UnloadLSTexture()
	{
		AEGfxTextureUnload(timeTexture);
		AEGfxTextureUnload(frameTexture);
	}

	void DrawLSTexture()
	{
		Frame.DrawObj();
		Time.DrawObj();
	}
}