/*
  *  \file Cam.cpp
  *  \author      : Tristan Tham
  *  \par DP Email: t.tham@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *	 Contains functions for creating Camera elements:
  *  Cam			-Driver function to execute Camera tracking and effects
  *  Shake			-Function to calculate and apply Shaking 
  *  Guide          -Function to apply endpoint guide to camera
  *   
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
  */

#include "Cam.hpp"

struct  CameraPos cam;

float	screenWidth				=  VIEWPORT_WIDTH	 * GRID_WIDTH_SIZE;
float   screenHeight			=  VIEWPORT_HEIGHT   * GRID_HEIGHT_SIZE;
float	shakespeed				= 0.0f;
float   shakedistance			= 0.5f;
f64		shaketime;
bool	shake;
short	e_shakeStrength;
Vector2D guide;
int		guiding;


void Cam(bool airCheck, Vector2D goalPos)
{
	float distance = cam.Y - Player.position.y;

	//Reset flag, Checks previous frame collision flag and current collision flag
	if ((airCheck == true) && (Player.GetColFlag() == 0)) 
	{
		shake = false;
		shaketime = 0.0f;
		shakespeed = 0.0f;
		e_shakeStrength = NO_SHAKE;
	}

	if (Player.velocity.y < -480.0f)
	{
		e_shakeStrength = HEAVY_SHAKE;
	}
	else if (Player.velocity.y < -300.0f)
	{
		e_shakeStrength = MEDIUM_SHAKE;
	}

	Guide(goalPos);
	Shake(distance);

	//Apply Cam Bounding
	cam.X = AEClamp(cam.X, -(GRID_WIDTH_SIZE * (VIEWPORT_WIDTH / 2.0f)) + (0.5f * screenWidth), (GRID_WIDTH_SIZE * (e_binaryMapWidth - (VIEWPORT_WIDTH / 2.0f))) - (0.5f * screenWidth));
	cam.Y = AEClamp(cam.Y, -(GRID_HEIGHT_SIZE * (e_binaryMapHeight - (VIEWPORT_HEIGHT / 2.0f))) + (0.5f * screenHeight), (GRID_HEIGHT_SIZE * (VIEWPORT_HEIGHT / 2.0f) - (0.5f * screenHeight)));
	
	//DEBUG
	std::cout << "e_shakeStrength: " << e_shakeStrength << std::endl;
	std::cout << "distance: " << distance << std::endl;
	std::cout << "shakespeed: " << shakespeed << std::endl; 
	std::cout << "Player.velocity.y: " << Player.velocity.y << std::endl;
	std::cout << "player x:" << Player.position.x << " player y:" << Player.position.y << std::endl;
	std::cout << cam.X << ',' << cam.Y << std::endl;

	//Apply calculations to camera
	AEGfxSetCamPosition(cam.X, cam.Y);
}

void Shake(float distance)
{
	//Camera Dip Algo
	if ((shake == true) && (shaketime < 0.2f) && (e_shakeStrength > 0)) //Conditions
	{
		shaketime += e_deltaTime; //Counter

		if (distance > -10.0f)
		{
			if (e_shakeStrength == MEDIUM_SHAKE)
			{
				shakespeed += -15.0f; //Decrease
			}

			if (e_shakeStrength == HEAVY_SHAKE)
			{
				shakespeed += -30.0f; //Heavy Decrease
			}
		}
	}
	if ((shaketime > 0.2f) && (distance < 0.0f))
	{
		shakespeed += 30.0f; //Increase
	}

	if((shaketime > 0.2f) && (distance > 39.0f))	
	{
		shakespeed = 0.0f;
	}

	//Apply shaking parameters to camera position
	if (guiding == 0)
	{
		cam.Y += (shakespeed * e_deltaTime);
	}
}

void Guide(Vector2D goalPos)
{
	if (AEInputCheckCurr(AEVK_Q))
	{
		guiding = 1;
		guide.x = goalPos.x - Player.position.x;
		guide.y = goalPos.y - Player.position.y;

		if (cam.X != goalPos.x)
		{
			cam.X += guide.x * e_deltaTime * 2.0f;
		}
		if (cam.Y != goalPos.y)
		{
			cam.Y = goalPos.y;
		}
	}

	if (!AEInputCheckCurr(AEVK_Q))
	{
		if (cam.X != Player.position.x)
		{
			guide.x = cam.X - Player.position.x;
			cam.X -= guide.x * e_deltaTime * 10.f;
		}
		if (cam.Y != Player.position.y)
		{
			guide.y = cam.Y - Player.position.y;
			cam.Y -= guide.y * e_deltaTime * 5.f;
		}
		if (cam.X < Player.position.x + HALVE_WINDOW_WIDTH)
		{
			guiding = 0;
		}
	}
}