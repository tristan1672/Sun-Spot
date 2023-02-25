#pragma once
#include "Ultilities.hpp"
#include "Timer.hpp"
#include <iostream>

#ifndef UIUTILITIES_HPP
#define UIUTILITIES_HPP

struct Score
{
	float S, A, B, C, F;
	int score;
	char grade;
	float red, green, blue;
};


int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

void PrintScore(int COLLECTIBLE_COUNT, int JUMP_COUNT, int DIFFICULTY);

int calculateScore(float timer, float maxTime);

#endif // UIUTILITIES_HPP