/*
  *  \file LevelSelect.hpp
  *  \author Xiao Jun Yu,
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  Declearation file for LevelSelect.cpp
  *
*/
#pragma once
#include "UI.hpp"
#include "Level.hpp"
namespace LevelSelect {
	void CreateLevelSelectUI()/*
		\brief alloate memory for level select UI
		*/;
	void SetLevelSelectActive()/*
		\brief sets the buttons for level select to active
		*/;
	void SetLevelSelectInActive()/*
		\brief sets the buttons for level select to inctive
		*/;
	void ButtonSelectBehaviour(mousePos mouse)/*
		\brief when the button is pressed for each level, level info pops up
		\param mouse the mouse position
		*/;
	void LSButtonAnimation(mousePos mouse)/*
		\brief when mouse collides with the textbox ,it will fade in
		\param mouse the mouse position
		*/;
	void DrawLevelButton()/*
		\brief draws all buttons in level select
		*/;
	void FreeLevelButton()/*
		\brief frees the buttons and memory allocated
		*/;
	bool BackButtonBehaviour(mousePos mouse);
	bool StartButtonBehaviour(mousePos mouse);
	void StagingScreen(int levelcount);
	void InitLSTexture();
	void LoadLSTexture();
	void UnloadLSTexture();
	void DrawLSTexture();
}
