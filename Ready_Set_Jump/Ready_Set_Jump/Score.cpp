/*
  *  \file Score.cpp
  *  \author      : Tristan Tham
  *  \par DP Email: t.tham@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *	 Contains functions for Score calculations and display:
  *   
  *   PrintScore			-Function for printing score evaluations at win screen
  *   calculateScore		-Function for evaluating score based on extracted variable count
  *	  calculateGrade		-Function for evaluating grade based on extracted variable count 
  *	  scoreAnimations		-Function for setting animation algorithm
  * 
  */

#include "Score.hpp"

//Structs
/***********************************************************************************************************************/
struct Score timer;
struct Score jump;
struct Score collectible;
/***********************************************************************************************************************/

/*!****************************************************************************

	\brief
	Driver function that calls score calculation functions & animation functions  
	then prints prints all scores in a format

	\param JUMP_COUNT
	the number of times the player jumped

	\param DIFFICULTY
	difficulty of current level, affects the evaluation conditions

******************************************************************************/
void PrintScore(int JUMP_COUNT, int DIFFICULTY)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	char timerscore[25];
	char timergrade[2];
	char timercount[15];
	char jumpscore[25];
	char jumpgrade[2];
	char jumpcount[10];
	char COLLECTIBLEScore[25];
	char collectiblegrade[2];
	char collectiblecount[25];
	jump.count = JUMP_COUNT;



	switch (DIFFICULTY) //Set Score conditions based on level difficulty
	{
	case EASY:
		timer.S = 20.0f;
		timer.A = 35.0f;
		timer.B = 50.0f;
		timer.C = 65.0f;
		timer.F = 150.0f;

		jump.S = 10;
		jump.A = 20;
		jump.B = 30;
		jump.C = 40;
		jump.F = 80;
		break;

	case MEDIUM:
		timer.S =  80.0f;
		timer.A = 100.0f;
		timer.B = 120.0f;
		timer.C = 140.0f;
		timer.F = 200.0f;

		jump.S = 40;
		jump.A = 50;
		jump.B = 60;
		jump.C = 75;
		jump.F = 120;
		break;
	}

	//Score Calculation 
	collectible.score	= calculateScore(e_numOfcollectibleCollected, e_totalNumOfcollectible, e_totalNumOfcollectible * 1000.0f);
	timer.score			= calculateScore(e_levelTime, timer.F, 10000.0f, true);
	jump.score			= calculateScore(jump.count, jump.F, 10000.0f, true);

	//Grade Calculation
	calculateGrades();

	//Setting Animation 
	e_scoreAnimation = scoreAnimations();

	//Store variables to string buffer
	snprintf(collectiblegrade, sizeof collectiblegrade, "%c",						collectible.grade);
	snprintf(COLLECTIBLEScore, sizeof COLLECTIBLEScore, "collectible score: %d",	collectible.score);
	snprintf(collectiblecount, sizeof collectiblecount, "collected: %d/%d",			e_numOfcollectibleCollected, e_totalNumOfcollectible);
	snprintf(timercount,	   sizeof timercount,		"time taken: ");
	snprintf(timergrade,	   sizeof timergrade,		"%c",						timer.grade);
	snprintf(timerscore,       sizeof timerscore,		"time score: %d",			timer.scoreDisplay);
	snprintf(jumpgrade ,	   sizeof timergrade,		"%c",						jump.grade);
	snprintf(jumpscore ,	   sizeof jumpscore,		"jump score: %d",			jump.scoreDisplay);
	snprintf(jumpcount ,	   sizeof jumpcount,		"jumps: %d",				jump.countDisplay);

	//Print string buffer 
	AEGfxPrint(e_fontID, COLLECTIBLEScore, collectible.score_pos.x, collectible.score_pos.y, 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, collectiblegrade, collectible.grade_pos.x, collectible.grade_pos.y, 3.0f, collectible.red, collectible.green, collectible.blue);
	AEGfxPrint(e_fontID, collectiblecount, collectible.count_pos.x, collectible.count_pos.y, 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, timerscore,	   timer.score_pos.x,		timer.score_pos.y,		 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, timergrade,	   timer.grade_pos.x,		timer.grade_pos.y,		 3.0f, timer.red, timer.green, timer.blue);
	AEGfxPrint(e_fontID, timercount,	   timer.count_pos.x,		timer.count_pos.y,		 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, jumpscore ,	   jump.score_pos.x ,		jump.score_pos.y ,		 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, jumpgrade ,	   jump.grade_pos.x ,		jump.grade_pos.y ,		 3.0f, jump.red, jump.green, jump.blue);
	AEGfxPrint(e_fontID, jumpcount ,	   jump.count_pos.x ,		jump.count_pos.y ,		 0.7f, 1.0f, 1.0f, 1.0f);

	//Print Time Taken
	if (e_levelTime > 60.0f)
	{
		DisplayTime(timer.count_pos.x + 0.35f, -0.05f); //Shift Right if include Minutes
	}
	else
	{
		DisplayTime(timer.count_pos.x + 0.25f, -0.05f);
	}
	
} 

/*!************************************************************************

	\brief
	evaluates a score for a count against its maximum, depending on output 
	desired can be set to display an inverse calculation

	\param count
	extracted count for the variable to be evaluated

	\param max
	the max count for the variable that is evaluated

	\param inverse
	determines the nature of calculation 
	If true, output goes higher as count goes lower against max
	Default set to false

	\return int score
	returns the evaluated score in an int type

***************************************************************************/
int calculateScore(float count, float max, float maxScore, bool inverse)
{
	float minScore = 0.0f;
	float maxScoreDecrement = maxScore / max;

	float countLeft = max - count;
	int score = maxScore - countLeft * maxScoreDecrement;

	if (inverse == true)
	{
		score = maxScore - score;
	}

	if (score < minScore)
	{
		score = minScore;
	}

	return score;
}

/*!*************************************************************************

	\brief
	evaluates a grade based on extern variables against conditions set by
	intially passed variable DIFFICULTY

***************************************************************************/
void calculateGrades()
{
// Time Taken Grade Evaluation
	if (e_levelTime <= timer.S)
	{
		timer.grade = 'S';
		timer.red = 1.0f;
		timer.green = 0.4f;
		timer.blue = 0.0f;
	}
	else if ((e_levelTime > timer.S) && (e_levelTime <= timer.A))
	{
		timer.grade = 'A';
		timer.red = 1.0f;
		timer.green = 0.0f;
		timer.blue = 0.0f;
	}
	else if ((e_levelTime > timer.A) && (e_levelTime <= timer.B))
	{
		timer.grade = 'B';
		timer.red = 0.4f;
		timer.green = 1.0f;
		timer.blue = 0.4f;
	}
	else if ((e_levelTime > timer.B) && (e_levelTime <= timer.C))
	{
		timer.grade = 'C';
		timer.red = 1.0f;
		timer.green = 1.0f;
		timer.blue = 0.6f;
	}
	else if (e_levelTime > timer.F)
	{
		timer.grade = 'F';
		timer.red = 0.3f;
		timer.green = 0.3f;
		timer.blue = 0.3f;
	}
	else
	{
		timer.grade = 'D';
		timer.red = 0.25f;
		timer.green = 0.25f;
		timer.blue = 0.0f;
	}
	

//Jump Count Grade Evaluation
	if (jump.count <= jump.S)
	{
		jump.grade = 'S';
		jump.red = 1.0f;
		jump.green = 0.4f;
		jump.blue = 0.0f;
	}
	else if ((jump.count > jump.S) && (jump.count <= jump.A))
	{
		jump.grade = 'A';
		jump.red = 1.0f;
		jump.green = 0.0f;
		jump.blue = 0.0f;
	}
	else if ((jump.count > jump.A) && (jump.count <= jump.B))
	{
		jump.grade = 'B';
		jump.red = 0.4f;
		jump.green = 1.0f;
		jump.blue = 0.4f;
	}
	else if ((jump.count > jump.B) && (jump.count <= jump.C))
	{
		jump.grade = 'C';
		jump.red = 1.0f;
		jump.green = 1.0f;
		jump.blue = 0.6f;
	}
	else if (jump.count > jump.F)
	{
		jump.grade = 'F';
		jump.red = 0.25f;
		jump.green = 0.25f;
		jump.blue = 0.25f;
	}
	else
	{
		jump.grade = 'D';
		jump.red = 0.25f;
		jump.green = 0.25f;
		jump.blue = 0.0f;
	}

//COLLECTIBLES Grade Evaluation
	float collectiblePercent = static_cast<float>(e_numOfcollectibleCollected) / static_cast<float>(e_totalNumOfcollectible);
	if (collectiblePercent > 0.8f)
	{
		collectible.grade = 'S';
		collectible.red = 1.0f;
		collectible.green = 0.4f;
		collectible.blue = 0.0f;
	}
	else if (collectiblePercent > 0.6f && collectiblePercent <= 0.8f)
	{
		collectible.grade = 'A';
		collectible.red = 1.0f;
		collectible.green = 0.0f;
		collectible.blue = 0.0f;
	}
	else if (collectiblePercent > 0.4f && collectiblePercent <= 0.6f)
	{
		collectible.grade = 'B';
		collectible.red = 0.4f;
		collectible.green = 1.0f;
		collectible.blue = 0.4f;
	}
	else if (collectiblePercent > 0.2f && collectiblePercent <= 0.4f)
	{
		collectible.grade = 'C';
		collectible.red = 1.0f;
		collectible.green = 1.0f;
		collectible.blue = 0.6f;
	}
	else if (collectiblePercent == 0.0f)
	{
		collectible.grade = 'F';
		collectible.red = 0.25f;
		collectible.green = 0.25f;
		collectible.blue = 0.25f;
	}
	else 
	{
		collectible.grade = 'D';
		collectible.red = 0.25f;
		collectible.green = 0.25f;
		collectible.blue = 0.0f;
	}
}

/*!*************************************************************************

	\brief
	Sets Score Display Animations:
	-Number incrementing from 0 to final score	  (Counting)
	-Display fonts moving laterally into position (Lateral Sliding)

***************************************************************************/
bool scoreAnimations()
{
//Counting Animation
//*******************************************************************************
	//timer.scoreDisplay			= 0;
	//jump.scoreDisplay			= 0;
	//collectible.scoreDisplay	= 0;

	if (timer.scoreDisplay < timer.score) //Timer Score Counting Animation
	{
		timer.scoreDisplay += 3000 * e_deltaTime;
	}

	if (jump.scoreDisplay < jump.score) //Jump Score Counting Animation
	{
		jump.scoreDisplay += 3000 * e_deltaTime;
	}

	if (jump.countDisplay < jump.count) //Jump Count Counting Animation
	{
		jump.countDisplay += 100 * e_deltaTime;
	}

	if (collectible.scoreDisplay < collectible.score) //collectible Score Counting Animation
	{
		collectible.scoreDisplay += 3000 * e_deltaTime;
	}

	if (timer.scoreDisplay >= timer.score && jump.scoreDisplay >= jump.score && jump.countDisplay >= jump.count && collectible.scoreDisplay >= collectible.score) {
		return true;
	}
//*******************************************************************************


//Lateral sliding Animations 
//*******************************************************************************

	if (timer.grade_pos.x < -0.175f) //Timer Grade Sliding Animation
	{
		timer.grade_pos.x += e_deltaTime;
	}

	if (timer.score_pos.x < -0.9f) //Timer Score Sliding Animation
	{	
		timer.score_pos.x += e_deltaTime;
	}

	if (timer.count_pos.x < -0.9f) //Timer Score Sliding Animation
	{
		timer.count_pos.x += e_deltaTime;
	}

	if (jump.grade_pos.x < 0.725f) //Jump Grade Sliding Animation
	{
		jump.grade_pos.x += 2 * e_deltaTime;
	}

	if (jump.score_pos.x < 0.125f) //Jump Score Sliding Animation
	{
		jump.score_pos.x += e_deltaTime;
	}

	if (jump.count_pos.x < 0.12f) //Jump Count Sliding Animation
	{
		jump.count_pos.x += 2 * e_deltaTime;
	}

	if (collectible.score_pos.x < -0.4f) //collectible Score Sliding Animation
	{
		collectible.score_pos.x += e_deltaTime;
	}

	if (collectible.grade_pos.x < 0.4f) //collectible Grade Sliding Animation
	{
		collectible.grade_pos.x += 2 * e_deltaTime;
	}

	if (collectible.count_pos.x < -0.4f) //collectible Count Sliding Animation
	{
		collectible.count_pos.x += e_deltaTime;
	}

	if (AEInputCheckCurr(AEVK_LBUTTON)) //Left click to skip all Animations
	{
		timer.scoreDisplay			= timer.score;
		jump.scoreDisplay			= jump.score;
		collectible.scoreDisplay	= collectible.score;

		timer.grade_pos.x			= -0.175f;
		timer.score_pos.x			= -0.9f;
		timer.count_pos.x			= -0.9f;

		jump.grade_pos.x			= 0.725f;
		jump.score_pos.x			= 0.125f;
		jump.count_pos.x			= 0.12f;

		collectible.score_pos.x		= -0.4f;
		collectible.grade_pos.x		=  0.4f;
		collectible.count_pos.x		= -0.4f;

		return true;
	}

	return false;
//*******************************************************************************
}


/*!*************************************************************************
* 
	\brief
	Initializes Struct variables to default values

***************************************************************************/
void scoreInitialize()
{
	timer			= { -1.0f, -0.05f, -1.0f, -0.2f , -1.0f,  -0.2f,
						 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						 0, 0, 0, 0, '0' };
	jump			= { -1.0f, -0.05f, -1.0f, -0.2f , -1.0f,  -0.2f,
						 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						 0, 0, 0, 0, '0' };
	collectible		= { -1.0f, -0.4f , -1.0f, -0.55f, -1.0f,  -0.55f,
						 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						 0, 0, 0, 0, '0' };
}