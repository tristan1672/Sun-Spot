#pragma once
#include "UI.hpp"
#include "Level.hpp"
namespace LevelSelect {
	void CreateLevelSelectUI();
	void SetLevelSelectActive();
	void SetLevelSelectInActive();
	void ButtonSelectBehaviour(mousePos mouse);
	void LSButtonAnimation(mousePos mouse);
	void DrawLevelButton();
	void FreeLevelButton();
	bool BackButtonBehaviour(mousePos mouse);
	bool StartButtonBehaviour(mousePos mouse);
	void StagingScreen(int levelcount);
	void InitLSTexture();
	void LoadLSTexture();
	void UnloadLSTexture();
	void DrawLSTexture();
}
