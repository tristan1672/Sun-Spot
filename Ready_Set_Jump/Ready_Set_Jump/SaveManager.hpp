/*****************************************************************
  *  \file SaveManager.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)
  *
  *  \brief
  *  Defination file for SaveManager.cpp, use for managing save files
  *
  *  -ReadFile()
  *		reads the save file, if the save file exists, reads the file save stores read value into nlohmann::json save, otherwise, reads from default save
  *		and makes a new save file
  *  -PrintSaveValue(int level)
  *		for debug use, prints save info to console
  * -GetSaveValue(int level, int& difficulty, int& jumps, int& collectibles, int& totalCollectibles, float& time, int& totalScore, bool& haveAttempted)
  *		gets all value from save
  * -SetSaveValue(int level, int jumps, int collectibles, float time, int totalScore, bool haveAttempted)
  *		sets all value to save
  * -WriteFile()
  *		writes the data into save.json
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>

namespace Save {
	extern nlohmann::json save;// the save file
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

	template <typename T>
	T GetSpecificSaveValue(int level, std::string data) {/*
			\brief get the value for a specific data
			\param [in] level which level to get the info
			\param [in] the data to access
			\return the value of the data
		*/
		return save[level][data];
	}

	template <typename T>
	void SetSpecificSaveValue(int level, std::string data, T value) {/*
			\brief set the value for a specific data
			\param [in] level which level to get the info
			\param [in] the data to write to
			\param [in] the value to write into the data
		*/
		save[level][data] = value;
	}

	void WriteFile()/*
		\brief writes the save file
		*/;
}