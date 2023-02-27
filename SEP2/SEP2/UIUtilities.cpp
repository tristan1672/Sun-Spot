/*
  *  \file UIUtilities.cpp
  *  \author      : Tristan Tham
  *  \par DP Email: t.tham@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *	 Contains functions for creating UI elements:
  *   IsAreaClicked			-Function to check for button collision with player clicks
  *   PrintScore			-Function for printing score evaluations at win screen
  *   calculateScore		-Function for evaluating score based on a extracted variable count
  *
  */

#include "UIUtilities.hpp"
#include <string>

static int counter, counter_2, counter_3, counter_4;
static float timegrade_x = -1.0f, jumpgrade_x = -1.0f, string_x = -1.0f, jumpcount_x = -1.0f;

// Button collisions
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float minX, maxX, minY, maxY;
	minX = area_center_x - static_cast<float>(0.5 * area_width);
	maxX = area_center_x + static_cast<float>(0.5 * area_width);
	minY = area_center_y - static_cast<float>(0.5 * area_height);
	maxY = area_center_y + static_cast<float>(0.5 * area_height);

	if (((click_x > minX) && (click_x < maxX)) && ((click_y > minY) && (click_y < maxY))) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

/*!************************************************************************

	\brief
	evaluates player numerical score and score grade, then prints the scores
	on win screen  
	
	\param COLLECTIBLE_COUNT
	the number of collectibles the player collected

	\param JUMP_COUNT
	the number of times the player jumped

	\param DIFFICULTY
	difficulty of current level, affects the evaluation conditions

***************************************************************************/
void PrintScore(int COLLECTIBLE_COUNT, int JUMP_COUNT, int DIFFICULTY)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	char tempStr[50];
	char timegrade[5];
	char jumpgrade[5];
	char jumpcount[10];
	int minute = static_cast<int>(e_levelTime / 60.0f);
	float second = e_levelTime * 100;
	struct Score time = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	struct Score jump = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	switch (DIFFICULTY) //Score conditions based on level difficulty
	{
	case EASY:
		time.S = 20.0f;
		time.A = 35.0f;
		time.B = 50.0f;
		time.C = 65.0f;
		time.F = 150.0f;

		jump.S = 10;
		jump.A = 20;
		jump.B = 30;
		jump.C = 40;
		jump.F = 100;
		break;
	case MEDIUM:
		time.S = 120.0f;
		time.A = 140.0f;
		time.B = 160.0f;
		time.C = 190.0f;
		time.F = 400.0f;

		jump.S = 45;
		jump.A = 60;
		jump.B = 70;
		jump.C = 80;
		break;
	}

	//Grade evaluations
	if (e_levelTime <= time.S)
	{
		time.grade = 'S';
		time.red = 1.0f;
		time.green = 0.4f;
		time.blue = 0.0f;
	}
	else if ((e_levelTime > time.S) && (e_levelTime <= time.A))
	{
		time.grade = 'A';
		time.red = 1.0f;
		time.green = 0.0f;
		time.blue = 0.0f;
	}
	else if ((e_levelTime > time.A) && (e_levelTime <= time.B))
	{
		time.grade = 'B';
		time.red = 0.4f;
		time.green = 1.0f;
		time.blue = 0.4f;
	}
	else if ((e_levelTime > time.B) && (e_levelTime <= time.C))
	{
		time.grade = 'C';
		time.red = 1.0f;
		time.green = 1.0f;
		time.blue = 0.6f;
	}
	else
	{
		time.grade = 'D';
		time.red = 0.5f;
		time.green = 0.25f;
		time.blue = 0.0f;
	}

	if (JUMP_COUNT <= jump.S)
	{
		jump.grade = 'S';
		jump.red = 1.0f;
		jump.green = 0.4f;
		jump.blue = 0.0f;
	}
	else if ((JUMP_COUNT > jump.S) && (JUMP_COUNT <= jump.A))
	{
		jump.grade = 'A';
		jump.red = 1.0f;
		jump.green = 0.0f;
		jump.blue = 0.0f;
	}
	else if ((JUMP_COUNT > jump.A) && (JUMP_COUNT <= jump.B))
	{
		jump.grade = 'B';
		jump.red = 0.4f;
		jump.green = 1.0f;
		jump.blue = 0.4f;
	}
	else if ((JUMP_COUNT > jump.B) && (JUMP_COUNT <= jump.C))
	{
		jump.grade = 'C';
		jump.red = 1.0f;
		jump.green = 1.0f;
		jump.blue = 0.6f;
	}
	else
	{
		jump.grade = 'D';
		jump.red = 0.5f;
		jump.green = 0.25f;
		jump.blue = 0.0f;
	}

	time.score = calculateScore(e_levelTime, time.F);
	jump.score = calculateScore(JUMP_COUNT, jump.F);

	//Animations
	if (counter < time.score)
	{
		counter += 3000 * GetTime();

		if (AEInputCheckCurr(AEVK_LBUTTON)) //Left click to skip 
		{
			counter = time.score;
		}
	
	}

	if (counter_2 < jump.score)
	{
		counter_2 += 3000 * GetTime();

		if (AEInputCheckCurr(AEVK_LBUTTON)) //Left click to skip 
		{
			counter_2 = jump.score;
		}
	}

	if (counter_3 < JUMP_COUNT)
	{
		counter_3 += 100 * GetTime();
	}

	if (timegrade_x < -0.225f)
	{
		timegrade_x += GetTime();
	}

	if (string_x < -0.8f)
	{
		string_x += GetTime();
	}

	if (jumpgrade_x < 0.625f)
	{
		jumpgrade_x += 2 * GetTime();
	}

	if (jumpcount_x < 0.02f)
	{
		jumpcount_x += 2 * GetTime();
	}

	//Print scores on win screen
	snprintf(jumpcount, sizeof jumpcount, "jumps: %d", counter_3);
	snprintf(timegrade, sizeof timegrade, "%c", time.grade);
	snprintf(jumpgrade, sizeof timegrade, "%c", jump.grade);
	snprintf(tempStr, sizeof tempStr, "time score: %-13djump score: %d", counter, counter_2);

	AEGfxPrint(e_fontID, tempStr, string_x, -0.3f, 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, timegrade, timegrade_x, -0.3f, 3.0f, time.red, time.green, time.blue);
	AEGfxPrint(e_fontID, jumpgrade, jumpgrade_x, -0.3f, 3.0f, jump.red, jump.green, jump.blue);
	AEGfxPrint(e_fontID, jumpcount, jumpcount_x, -0.15f, 0.7f, 1.0f, 1.0f, 1.0f);
} 

/*!************************************************************************

	\brief
	evaluates a score for a count against its maximum, the lower the count the higher the score

	\param count
	count for the variable to be evaluated

	\param max
	the max count for the variable that is evaluated

	\return int score
	returns the evaluated score in an int type

***************************************************************************/
int calculateScore(float count, float max)
{
	float initialScore = 10000.0f;
	float minScore = 0.0f;
	float maxScoreDecrement = initialScore / max;

	float countLeft = max - count;
	int score = initialScore - countLeft * maxScoreDecrement;
	score = initialScore - score;

	if (score < minScore)
	{
		score = minScore;
	}

	return score;
}