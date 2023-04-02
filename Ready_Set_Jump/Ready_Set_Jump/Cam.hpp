/*****************************************************************
  *  \file Cam.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Tristan Tham Rui Hong (t.tham)
  *
  *  \brief
  *	 Contains functions for creating Camera elements:
  *  Cam			-Driver function to execute Camera tracking and effects
  *  Shake			-Function to calculate and apply Shaking
  *  Guide          -Function to apply endpoint guide to camera
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "PreCompiledHeader.hpp"
#include "Collision.hpp"
#include "GameObjClasses.hpp"
#include "Level.hpp"
#include <iostream>

#ifndef Cam_HPP
#define Cam_HPP

struct CameraPos
{
	f32 X;
	f32 Y;
};

void Cam(bool airCheck, Vector2D goalPos);
void Shake(float distance);
void Guide(Vector2D goalPos);
#endif // Cam_HPP