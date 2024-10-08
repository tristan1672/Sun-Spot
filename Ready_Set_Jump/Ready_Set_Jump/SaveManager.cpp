/*****************************************************************
  *  \file SaveManager.cpp
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
  *  All content � 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/
#include "SaveManager.hpp"
#include <sstream>
namespace Save {
	//start of namespace Save
		nlohmann::json save;// the save file
		size_t maxlevel{ 17 };// the total level we can have

/* This is the template save file, only used if there is no save file already*/
#pragma region Default Save
		std::string Template = "["
			"{ \"Level\":  0,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false},"
			"{ \"Level\":  1,\"Difficulty\" : 0,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 6,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  2,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 20,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  3,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 4,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  4,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 2,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  5,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 5,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  6,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 3,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  7,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 5,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  8,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 3,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\":  9,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 17,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 10,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 11,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 12,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 13,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 14,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 15,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false },"
			"{ \"Level\": 16,\"Difficulty\" : 1,\"Jumps\" : 0,\"Collectibles\" : 0,\"TotalCollectibles\" : 0,\"Time\" : 0,\"TotalScore\" : 0,\"Attempted\" : false }"
			"]";

#pragma endregion

	void ReadFile() {
		std::fstream saveFile("Assets/Save/Save.json");// the save file path and attempts to load the file

		if (saveFile.good() && saveFile.is_open()) {// checks if the save file exists, if yes, loads the the save file in to the save vaiable
			save = nlohmann::json::parse(saveFile);
		}
		else// loads the save file template and create the save file
		{
			std::istringstream temp{ Template };
			save = nlohmann::json::parse(temp);
			WriteFile();
		}
		saveFile.close();
	}

	void PrintSaveValue(int level) {// use for debuggin
		std::cout<< "Level: "<< save[level]["Level"] << std::endl;
		std::cout<< "Difficulty: "<< save[level]["Difficulty"] << std::endl;
		std::cout<< "Jumps: "<< save[level]["Jumps"] << std::endl;
		std::cout<< "Collectibles: "<< save[level]["Collectibles"] << std::endl;
		std::cout<< "TotalCollectibles: "<< save[level]["TotalCollectibles"] << std::endl;
		std::cout<< "Time: "<< save[level]["Time"] << std::endl;
		std::cout<< "TotalScore: "<< save[level]["TotalScore"] << std::endl;
		std::cout<< "Attempted: "<< save[level]["Attempted"] << std::endl;
	}

	void GetSaveValue(int level, int& difficulty, int& jumps, int& collectibles, int& totalCollectibles, float& time, int& totalScore, bool& haveAttempted) {
		//gets the values from save file
		jumps = save[level]["Jumps"];
		difficulty = save[level]["Difficulty"];
		collectibles = save[level]["Collectibles"];
		totalCollectibles = save[level]["TotalCollectibles"];
		time = save[level]["Time"];
		totalScore = save[level]["TotalScore"];
		haveAttempted = save[level]["Attempted"];
	}

	void SetSaveValue(int level, int jumps, int collectibles, float time, int totalScore, bool haveAttempted) {
		//set the save file based on stats from in game
		save[level]["Jumps"] = jumps;
		save[level]["Collectibles"] = collectibles;
		save[level]["Time"] = time;
		save[level]["TotalScore"] = totalScore;
		save[level]["Attempted"] = haveAttempted;
	}

	void WriteFile() {
		// writes save file from the save variable
		std::fstream saveFile("Assets/Save/Save.json",std::fstream::out);
		if (saveFile.is_open()) {
			saveFile << '['<<std::endl;
			for (size_t i{}; i < maxlevel; ++i) {
				saveFile << " {";
				saveFile << "\"Level\": "<<save[i]["Level"] << ',';
				saveFile << "\"Difficulty\": "<<save[i]["Difficulty"] << ',';
				saveFile << "\"Jumps\": "<<save[i]["Jumps"] << ',';
				saveFile << "\"Collectibles\": "<<save[i]["Collectibles"] << ',';
				saveFile << "\"TotalCollectibles\": "<<save[i]["TotalCollectibles"] << ',';
				saveFile << "\"Time\": "<<save[i]["Time"]<<',';
				saveFile << "\"TotalScore\": "<<save[i]["TotalScore"]<<',';
				saveFile << "\"Attempted\": "<<save[i]["Attempted"];
				if (i < maxlevel-1) {
					saveFile << "},"<<std::endl;
				}
				else
				{
					saveFile << '}' << std::endl;
				}

			}
			saveFile << ']';
		}
		saveFile.close();
	}
}