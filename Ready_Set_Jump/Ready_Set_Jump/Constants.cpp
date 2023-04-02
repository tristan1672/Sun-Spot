/*****************************************************************
  *  \file Constants.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian) (33%)
  *				   : Tristan Tham Rui Hong (t.tham)        (33%)
  *                : Xiao Jun Yu (junyu.xiao)              (33%)
  *
  *  \brief
  *  File containing constant variables used throughout project.
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include "Constants.hpp"

// Window
//---------------------------
const int WINDOW_WIDTH   = 1600;
const int WINDOW_HEIGHT  = 900;
const float HALVE_WINDOW_WIDTH = WINDOW_WIDTH * 0.5f;
const float HALVE_WINDOW_HEIGHT = WINDOW_HEIGHT * 0.5f;

// Font
//---------------------------
const int FONT_SIZE = 30;
const int CREDIT_FONT_SIZE = 60;

// Level Select Menu
//---------------------------
const int LEVEL_ARRAY_SIZE = 3;
const float LEVEL_BUTTON_GAP = 0.3f;

// Level
//---------------------------
// PLayer
const float PLAYER_SIZE_X = 30.0f;
const float PLAYER_SIZE_Y = 30.0f;
// Goal
const float GOAL_SIZE_X = 30.0f;
const float GOAL_SIZE_Y = 45.0f;
// collectible
const float collectible_SIZE_X = 30.0f;
const float collectible_SIZE_Y = 30.0f;
// View Port
const int VIEWPORT_WIDTH  = 30;
const int VIEWPORT_HEIGHT = 25;
// Platform
const f32 GRID_WIDTH_SIZE = static_cast<f32>(WINDOW_WIDTH) / static_cast<f32>(VIEWPORT_WIDTH);
const f32 GRID_HEIGHT_SIZE = static_cast<f32>(WINDOW_HEIGHT) / static_cast<f32>(VIEWPORT_HEIGHT);
// Physics
// Jump
const float ORIGINAL_JUMP_FORCE_MOD = 1.0f;
const float MAX_JUMP_FORCE = 500.f;
const float MIN_JUMP_FORCE = 100.f;
const float ORIGINAL_VERT_MOD = 1.0f; // Not used
// Drag
const float NORMAL_DRAG = 2.f;
const float AIR_DRAG = 0.f; 
const float STICK_DRAG = 10.f;
// Friction
const float NORMAL_FRICTION = 25.f;
const float ICE_FRICTION = 1.5f;
const float SLIME_FRICTION = 5.f;
const float FULL_STOP_FRICTION = 1 / e_deltaTime;

// Jump Arrow
const float MAX_HOLD_TIME = 0.5f;
const float MAX_HOLD_DISTANCE = 158.f;
const float MIN_HOLD_DISTANCE = 10.f;

// Collision
//---------------------------
const unsigned int COLLISION_LEFT   = 0x00000001;	//0001
const unsigned int COLLISION_RIGHT  = 0x00000002;	//0010
const unsigned int COLLISION_TOP    = 0x00000004;	//0100
const unsigned int COLLISION_BOTTOM = 0x00000008;	//1000

// Particle
//---------------------------
const unsigned int MAX_PARTICLE_NUMBER = 2048;