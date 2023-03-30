/*
  *  \file SaveManager.hpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  Declearation file for SaveManager.cpp, use for managing save files
  *
*/
#pragma once
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
namespace Save {
	void ReadFile()/*
		\brief run once when the game starts, checks if the save file already exists, if not uses the template and create a save file
		*/;
	void PrintSaveValue(int level)/*
		\brief use for printing the save data, for debug only
		\param level which will get printed to console
		*/;
	void GetSaveValue(int level, int& difficulty, int& jumps, int& collectibles,int&totalCollectibles, float& time, int& totalScore, bool& haveAttempted)/*
		\brief get the save file info
		\param[in] level which level to get the info
		\param[in] difficulty the difficulty of level
		\param[out] jumps jumps made previously
		\param[out] collectibles total collectibles collected previously
		\param[out] totalCollectibles 
		\param[out] time time took previously
		\param[out] totalScore the total score got previously
		\param[out] haveAttempted check if the level was attempted before
		*/;
	void SetSaveValue(int level, int jumps, int collectibles, float time, int totalScore, bool haveAttempted)/*
		\brief set the save file info
		\param[in] level which level to get the info
		\param[in] difficulty the difficulty of level
		\param[in] jumps jumps made previously
		\param[in] collectibles total collectibles collected previously
		\param[in] time time took previously
		\param[in] totalScore the total score got previously
		\param[in] haveAttempted check if the level was attempted before
		*/;
	void WriteFile()/*
		\brief writes the save file
		*/;
}