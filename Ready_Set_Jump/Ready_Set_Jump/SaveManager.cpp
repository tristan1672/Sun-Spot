#include "SaveManager.hpp"
namespace Save {
		nlohmann::json save;
		size_t maxlevel{ 17 };

	void ReadFile() {
		std::fstream saveFile("Assets/Save/Save.json");
		if (saveFile.good() && saveFile.is_open()) {
			save = nlohmann::json::parse(saveFile);
		}
		else
		{
			std::fstream defualtSave("Assets/Save/DefaultSave.json");
			if (defualtSave.is_open()) {
				save = nlohmann::json::parse(defualtSave);
				WriteFile();
			}
			defualtSave.close();
		}
		saveFile.close();
	}

	void PrintSaveValue(int level) {
		std::cout<< "Level: "<< save[level]["Level"] << std::endl;
		std::cout<< "Difficulty: "<< save[level]["Difficulty"] << std::endl;
		std::cout<< "Jumps: "<< save[level]["Jumps"] << std::endl;
		std::cout<< "Collectibles: "<< save[level]["Collectibles"] << std::endl;
		std::cout<< "Time: "<< save[level]["Time"] << std::endl;
		std::cout<< "TotalScore: "<< save[level]["TotalScore"] << std::endl;
		std::cout<< "Attempted: "<< save[level]["Attempted"] << std::endl;
	}

	void GetSaveValue(int level, int& difficulty, int& jumps, int& collectibles, float& time,int& totalScore, bool& haveAttempted) {
		jumps = save[level]["Jumps"];
		difficulty = save[level]["Difficulty"];
		collectibles = save[level]["Collectibles"];
		time = save[level]["Time"];
		totalScore = save[level]["TotalScore"];
		haveAttempted = save[level]["Attempted"];
	}

	void SetSaveValue(int level, int jumps, int collectibles, float time, int totalScore, bool haveAttempted) {
		save[level]["Jumps"] = jumps;
		save[level]["Collectibles"] = collectibles;
		save[level]["Time"] = time;
		save[level]["TotalScore"] = totalScore;
		save[level]["Attempted"] = haveAttempted;
	}
	void WriteFile() {
		std::fstream saveFile("Assets/Save/Save.json",std::fstream::out);
		if (saveFile.is_open()) {
			saveFile << '['<<std::endl;
			for (size_t i{}; i < maxlevel; ++i) {
				saveFile << " {";
				saveFile << "\"Level\": "<<save[i]["Level"] << ',';
				saveFile << "\"Difficulty\": "<<save[i]["Difficulty"] << ',';
				saveFile << "\"Jumps\": "<<save[i]["Jumps"] << ',';
				saveFile << "\"Collectibles\": "<<save[i]["Collectibles"] << ',';
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