/*****************************************************************
  *  \file Score.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Tristan Tham Rui Hong (t.tham)
  *
  *  \brief
  *	 Contains functions for Score calculations and display:
  *
  *   PrintScore			-Function for printing score evaluations at win screen
  *   calculateScore		-Function for evaluating score based on extracted variable count
  *	  calculateGrade		-Function for evaluating grade based on extracted variable count
  *	  scoreAnimations		-Function for setting animation algorithm
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "Utilities.hpp"
#include "Timer.hpp"
#include "SaveManager.hpp"
#include "Level.hpp"
#include <iostream>

#ifndef SCORE_HPP
#define SCORE_HPP


struct Score
{
	Vector2D count_pos, grade_pos, score_pos;
	float S, A, B, C, F, red, green, blue, maxScore, size, mono;
	int  count, score, scoreDisplay, countDisplay;
	char grade;
};

void PrintScore(int JUMP_COUNT);
int	 calculateScore(float timer, float maxTime, float maxScore, bool inverse = false);
void calculateGrades();
bool scoreAnimations();
void scoreInitialize();

#endif // SCORE_HPP