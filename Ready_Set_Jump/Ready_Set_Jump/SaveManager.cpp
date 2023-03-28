#include "SaveManager.hpp"
namespace Save {
		nlohmann::json save;
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
		std::cout<< "Jumps: "<< save[level]["Jumps"] << std::endl;
		std::cout<< "Collectibles: "<< save[level]["Collectibles"] << std::endl;
		std::cout<< "Time: "<< save[level]["Time"] << std::endl;
		std::cout<< "Attempted: "<< save[level]["Attempted"] << std::endl;
	}

	void GetSaveValue(int level, int& jumps, int& collectibles, float& time, bool& haveAttempted) {
		jumps = save[level]["Jumps"];
		collectibles = save[level]["Collectibles"];
		time = save[level]["Time"];
		haveAttempted = save[level]["Attempted"];
	}

	void SetSaveValue(int level, int jumps, int collectibles, float time, bool haveAttempted) {
		save[level]["Jumps"] = jumps;
		save[level]["Collectibles"] = collectibles;
		save[level]["Time"] = time;
		save[level]["Attempted"] = haveAttempted;
	}
	void WriteFile() {
		size_t maxlevel{ 17 };
		std::fstream saveFile("Assets/Save/Save.json",std::fstream::out);
		if (saveFile.is_open()) {
			saveFile << '['<<std::endl;
			for (size_t i{}; i < maxlevel; ++i) {
				saveFile << " {";
				saveFile << "\"Level\": "<<save[i]["Level"] << ',';
				saveFile << "\"Jumps\": "<<save[i]["Jumps"] << ',';
				saveFile << "\"Collectibles\": "<<save[i]["Collectibles"] << ',';
				saveFile << "\"Time\": "<<save[i]["Time"]<<',';
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