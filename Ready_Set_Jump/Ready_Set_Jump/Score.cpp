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
struct Score collectable;
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
	char collectablescore[25];
	char collectablegrade[2];
	char collectablecount[25];
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
	collectable.score	= calculateScore(e_numOfCollectableCollected, e_totalNumOfCollectable, e_totalNumOfCollectable * 1000.0f);
	timer.score			= calculateScore(e_levelTime, timer.F, 10000.0f, true);
	jump.score			= calculateScore(jump.count, jump.F, 10000.0f, true);

	//Grade Calculation
	calculateGrades();

	//Setting Animation 
	scoreAnimations();

	//Store variables to string buffer
	snprintf(collectablegrade, sizeof collectablegrade, "%c",						collectable.grade);
	snprintf(collectablescore, sizeof collectablescore, "collectable score: %d",	collectable.score);
	snprintf(collectablecount, sizeof collectablecount, "collected: %d/%d",			e_numOfCollectableCollected, e_totalNumOfCollectable);
	snprintf(timercount,	   sizeof timercount,		"time taken: ");
	snprintf(timergrade,	   sizeof timergrade,		"%c",						timer.grade);
	snprintf(timerscore,       sizeof timerscore,		"time score: %d",			timer.scoreDisplay);
	snprintf(jumpgrade ,	   sizeof timergrade,		"%c",						jump.grade);
	snprintf(jumpscore ,	   sizeof jumpscore,		"jump score: %d",			jump.scoreDisplay);
	snprintf(jumpcount ,	   sizeof jumpcount,		"jumps: %d",				jump.countDisplay);

	//Print string buffer 
	AEGfxPrint(e_fontID, collectablescore, collectable.score_pos.x, collectable.score_pos.y, 0.7f, 1.0f, 1.0f, 1.0f);
	AEGfxPrint(e_fontID, collectablegrade, collectable.grade_pos.x, collectable.grade_pos.y, 3.0f, collectable.red, collectable.green, collectable.blue);
	AEGfxPrint(e_fontID, collectablecount, collectable.count_pos.x, collectable.count_pos.y, 0.7f, 1.0f, 1.0f, 1.0f);
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

//Collectables Grade Evaluation
	float collectablePercent = static_cast<float>(e_numOfCollectableCollected) / static_cast<float>(e_totalNumOfCollectable);
	if (collectablePercent > 0.8f)
	{
		collectable.grade = 'S';
		collectable.red = 1.0f;
		collectable.green = 0.4f;
		collectable.blue = 0.0f;
	}
	else if (collectablePercent > 0.6f && collectablePercent <= 0.8f)
	{
		collectable.grade = 'A';
		collectable.red = 1.0f;
		collectable.green = 0.0f;
		collectable.blue = 0.0f;
	}
	else if (collectablePercent > 0.4f && collectablePercent <= 0.6f)
	{
		collectable.grade = 'B';
		collectable.red = 0.4f;
		collectable.green = 1.0f;
		collectable.blue = 0.4f;
	}
	else if (collectablePercent > 0.2f && collectablePercent <= 0.4f)
	{
		collectable.grade = 'C';
		collectable.red = 1.0f;
		collectable.green = 1.0f;
		collectable.blue = 0.6f;
	}
	else if (collectablePercent == 0.0f)
	{
		collectable.grade = 'F';
		collectable.red = 0.25f;
		collectable.green = 0.25f;
		collectable.blue = 0.25f;
	}
	else 
	{
		collectable.grade = 'D';
		collectable.red = 0.25f;
		collectable.green = 0.25f;
		collectable.blue = 0.0f;
	}
}

/*!*************************************************************************

	\brief
	Sets Score Display Animations:
	-Number incrementing from 0 to final score	  (Counting)
	-Display fonts moving laterally into position (Lateral Sliding)

***************************************************************************/
void scoreAnimations()
{
//Counting Animation
//*******************************************************************************
	//timer.scoreDisplay			= 0;
	//jump.scoreDisplay			= 0;
	//collectable.scoreDisplay	= 0;

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

	if (collectable.scoreDisplay < collectable.score) //Collectable Score Counting Animation
	{
		collectable.scoreDisplay += 3000 * e_deltaTime;
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

	if (collectable.score_pos.x < -0.4f) //Collectable Score Sliding Animation
	{
		collectable.score_pos.x += e_deltaTime;
	}

	if (collectable.grade_pos.x < 0.4f) //Collectable Grade Sliding Animation
	{
		collectable.grade_pos.x += 2 * e_deltaTime;
	}

	if (collectable.count_pos.x < -0.4f) //Collectable Count Sliding Animation
	{
		collectable.count_pos.x += e_deltaTime;
	}

	if (AEInputCheckCurr(AEVK_LBUTTON)) //Left click to skip all Animations
	{
		timer.scoreDisplay			= timer.score;
		jump.scoreDisplay			= jump.score;
		collectable.scoreDisplay	= collectable.score;

		timer.grade_pos.x			= -0.175f;
		timer.score_pos.x			= -0.9f;
		timer.count_pos.x			= -0.9f;

		jump.grade_pos.x			= 0.725f;
		jump.score_pos.x			= 0.125f;
		jump.count_pos.x			= 0.12f;

		collectable.score_pos.x		= -0.4f;
		collectable.grade_pos.x		=  0.4f;
		collectable.count_pos.x		= -0.4f;
	}
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
	collectable		= { -1.0f, -0.4f , -1.0f, -0.55f, -1.0f,  -0.55f,
						 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						 0, 0, 0, 0, '0' };
}