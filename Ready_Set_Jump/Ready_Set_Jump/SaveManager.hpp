#pragma once
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
namespace Save {
	void ReadFile();
	void PrintSaveValue(int level);
	void GetSaveValue(int level, int& difficulty, int& jumps, int& collectibles, float& time, int& totalScore, bool& haveAttempted);
	void SetSaveValue(int level, int jumps, int collectibles, float time, int totalScore, bool haveAttempted);
	void WriteFile();
}