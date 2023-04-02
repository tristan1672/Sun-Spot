/*****************************************************************
  *  \file Constants.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian) (33%)
  *				   : Tristan Tham (t.tham)                 (33%)
  *                : Xiao Jun Yu (junyu.xiao)              (33%)
  *
  *  \brief
  *  File containing constant variables used throughout project.
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "AEEngine.h"
#include "Utilities.hpp"

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Window
//---------------------------
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const float HALVE_WINDOW_WIDTH;
extern const float HALVE_WINDOW_HEIGHT;

// Font
//---------------------------
extern const int FONT_SIZE;
extern const int CREDIT_FONT_SIZE;

// Level Select Menu
//---------------------------
extern const int LEVEL_ARRAY_SIZE;
extern const float LEVEL_BUTTON_GAP;

// Level
//---------------------------
// PLayer
extern const float PLAYER_SIZE_X;
extern const float PLAYER_SIZE_Y;
// Goal
extern const float GOAL_SIZE_X;
extern const float GOAL_SIZE_Y;
// collectible
extern const float collectible_SIZE_X;
extern const float collectible_SIZE_Y;
// View Port
extern const int VIEWPORT_WIDTH;
extern const int VIEWPORT_HEIGHT;
// Platform
extern const f32 GRID_WIDTH_SIZE;
extern const f32 GRID_HEIGHT_SIZE;
// Physics
// Jump
extern const float ORIGINAL_JUMP_FORCE_MOD;
extern const float MAX_JUMP_FORCE;
extern const float MIN_JUMP_FORCE;
// Drag
extern const float NORMAL_DRAG;
extern const float AIR_DRAG;
extern const float STICK_DRAG;
// Friction
extern const float NORMAL_FRICTION;
extern const float ICE_FRICTION;
extern const float SLIME_FRICTION;
extern const float FULL_STOP_FRICTION;

// Jump Arrow
extern const float MAX_HOLD_TIME;
extern const float MAX_HOLD_DISTANCE;
extern const float MIN_HOLD_DISTANCE;

// Collision
//---------------------------
extern const unsigned int COLLISION_LEFT;
extern const unsigned int COLLISION_RIGHT;
extern const unsigned int COLLISION_TOP;
extern const unsigned int COLLISION_BOTTOM;

// Particle
//---------------------------
extern const unsigned int MAX_PARTICLE_NUMBER;

#endif // CONSTANTS_HPP