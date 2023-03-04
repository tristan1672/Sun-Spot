/*
  *  \file UI.cpp
  *  \author      : Tristan Tham
  *  \par DP Email: t.tham@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *	 Contains functions for creating UI elements:
  *   IsAreaClicked			-Function to check for button collision with player clicks
  *   
  */

#include "UI.hpp"
#include <string>

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
