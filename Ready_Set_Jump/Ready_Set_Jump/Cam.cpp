/*
  *  \file Cam.cpp
  *  \author      : Tristan Tham
  *  \par DP Email: t.tham@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *	 Contains functions for creating Camera elements:
  *  Cam			-Function to execute Camera tracking and effects
  *   
  */

#include "Cam.hpp"

struct  CameraPos cam;

float	screenWidth				=  VIEWPORT_WIDTH	 * GRID_WIDTH_SIZE;
float   screenHeight			=  VIEWPORT_HEIGHT * GRID_HEIGHT_SIZE;
float	shakespeed				= 0.0f;
float   shakedistance			= 0.5f;
f64		shaketime;
bool	shake;
short	e_shakeStrength;



void Cam(bool airCheck)
{
	float distance = cam.Y - Player.position.y;
	if ((airCheck == true) && (Player.GetColFlag() == 0)) //Reset flag, Checks previous frame collision flag and current collision flag
	{
		shake = false;
		shaketime = 0.0f;
		shakespeed = 0.0f;
		e_shakeStrength = NO_SHAKE;
	}
	
	/* Jitter shake
	if (shake == true && (Player.jumpReady) && (shaketime < 0.2f))
	{
		shakespeed = 1.0f;
		shaketime += e_deltaTime;
		float distance = cam.Y - Player.position.y;
		if (shakespeed >= 0)
		{
			if (e_shakeStrength == HEAVY_SHAKE)
			{
				shakespeed = 500.0f;
			}
			else if (e_shakeStrength == MEDIUM_SHAKE)
			{
				shakespeed = 100.0f;
			}
			else
			{
				shakespeed = 0.0f;
			}

			if (distance > shakedistance)
			{
				shakespeed *= -1.0f;
			}
		}
		else
		{
			if (distance < -shakedistance)
			{
				shakespeed *= -1.0f;
			}
		}

	}*/

	//Camera Dip
	if ((shake == true) && (shaketime < 0.2f) && (e_shakeStrength > 0)) //Conditions
	{
		shaketime += e_deltaTime; //Counter
		
		if (distance > -10.0f) 
		{
			if (e_shakeStrength == MEDIUM_SHAKE)
			{
				shakespeed += -30.0f; //Decrease
			}
			
			if (e_shakeStrength == HEAVY_SHAKE)
			{
				shakespeed += -100.0f; //Heavy Decrease
			}
		}
	}
	if ((shaketime > 0.2f) && (distance < 0.0f))
	{
		shakespeed += 30.0f; //Increase
	}
	
	cam.X = Player.position.x;
	cam.Y = Player.position.y + (shakespeed * e_deltaTime * e_shakeStrength);
	
	/*Cam Bounding TEMP
	if (cam.X > (GRID_WIDTH_SIZE * e_binaryMapWidth * 0.5)) //Right Bound
	{
		cam.X = 100.0f;
	}

	if (cam.X < -100.0f) //Left Bound
	{
		cam.X = -100.0f;
	}

	if (cam.Y > 300.0f) //Top Bound
	{
		cam.Y = 300.0f;
	}

	if (cam.Y < -200.0f) //Bottom Bound
	{
		cam.Y = -200.0f;
	}
	*/
	//cam.X = AEClamp(cam.X, -(GRID_WIDTH_SIZE  * (VIEWPORT_WIDTH / 2.0f))    + (0.5f * screenWidth) , (GRID_WIDTH_SIZE  * (e_binaryMapWidth - (VIEWPORT_WIDTH / 2.0f))) - (0.5f * screenWidth));
	cam.Y = AEClamp(cam.Y, -(GRID_HEIGHT_SIZE * (VIEWPORT_HEIGHT * 0.5f + 1)) + (0.5f * screenHeight),  GRID_HEIGHT_SIZE * (e_binaryMapHeight / 2.0f));

	cam.X = AEClamp(cam.X, -(GRID_WIDTH_SIZE * (VIEWPORT_WIDTH / 2.0f)) + (0.5f * screenWidth), (GRID_WIDTH_SIZE * (e_binaryMapWidth - (VIEWPORT_WIDTH / 2.0f))) - (0.5f * screenWidth));
	//cam.Y = AEClamp(cam.Y, -(GRID_HEIGHT_SIZE * (VIEWPORT_HEIGHT / 2.0f)) + (0.5f * screenHeight), (GRID_HEIGHT_SIZE * (e_binaryMapHeight - (VIEWPORT_HEIGHT / 2.0f))) - (0.5f * screenHeight));
	//cam.Y = AEClamp(cam.Y, -(GRID_HEIGHT_SIZE * (e_binaryMapHeight / 2.0f)) + (0.5f * screenHeight), GRID_HEIGHT_SIZE * (e_binaryMapHeight / 2.0f));

	

	/*
	std::cout << "e_shakeStrength: " << e_shakeStrength << std::endl;
	std::cout << "distance: " << distance << std::endl;
	std::cout << "cam.Y: " << cam.Y << std::endl;
	std::cout << "shakespeed: " << shakespeed << std::endl; 
	std::cout << "player x:" << Player.position.x << " player y:" << Player.position.y << std::endl;
	std::cout << cam.X << ',' << cam.Y << std::endl;*/

	AEGfxSetCamPosition(cam.X, cam.Y); // Set camera to follow player
}
