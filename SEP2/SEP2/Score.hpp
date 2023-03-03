#pragma once
#include "Ultilities.hpp"
#include "Timer.hpp"
#include <iostream>

#ifndef SCORE_HPP
#define SCORE_HPP


struct Score
{
	Vector2D count_pos, grade_pos, score_pos;
	float S, A, B, C, F, red, green, blue;
	int  count, score, scoreDisplay, countDisplay;
	char grade;
};

void PrintScore(int JUMP_COUNT, int DIFFICULTY);
int	 calculateScore(float timer, float maxTime, float maxScore, bool inverse = false);
void calculateGrades();
void scoreAnimations();

#endif // SCORE_HPP