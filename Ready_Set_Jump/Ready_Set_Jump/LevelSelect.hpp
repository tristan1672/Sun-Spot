/*****************************************************************
  *  \file LevelSelect.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu, (junyu.xiao)
  *					 -Main Author
  *					 -CreateLevelSelectUI()
  *						creates UI in level select
  *					-ButtonSelectBehaviour(mousePos mouse)
  *						when player pressed the level numbers in level select, players will bring up UI showing stats regarding that level
  *					-LSButtonAnimation(mousePos mouse)
  *						when player hovers over the numbers in level select, individual text box will fade in
  *					-DrawLevelButton()
  *						draws all buttons in level select
  *					-FreeLevelButton()
  *						frees memories allocated from CreateLevelSelectUI
  *					-SetLevelSelectActive()
  *						make all level select button to be active
  *					-SetLevelSelectInActive()
  *						make all level select button to be inactive
  *					-BackButtonBehaviour(mousePos mouse)
  *						when the back button is pressed, it will return player back to the main menu
  *					-StartButtonBehaviour(mousePos mouse)
  *						when the start button is pressed, it will bring the player to the actual level
  *
  *				   : Tristan Tham Rui Hong (t.tham)
  *					-Sub Author
  *					-StagingScreen(int levelcount)
  *
  *					-InitLSTexture()
  *
  *					-LoadLSTexture()
  *						Loads texture in level select
  *				    -UnloadLSTexture()
  *						frees memories allocated from LoadLSTexture
  *					-DrawLSTexture()
  *						draws textures in level select
  *
  *  \brief
  *  Defination file for LevelSelect.hpp
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/

#pragma once
#include "UI.hpp"
#include "Level.hpp"

#ifndef LEVEL_SELECT_HPP
#define LEVEL_SELECT_HPP

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

#endif // LEVEL_SELECT_HPP