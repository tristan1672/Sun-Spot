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
#endif // Cam_HPP