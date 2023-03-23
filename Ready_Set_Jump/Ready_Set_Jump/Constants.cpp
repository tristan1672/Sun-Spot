#include "Constants.hpp"

// Window
//---------------------------
const int WINDOW_WIDTH   = 1270;
const int WINDOW_HEIGHT  = 720;
const float WINDOW_WIDTH_OFFSET = WINDOW_WIDTH * 0.5f;
const float WINDOW_HEIGHT_OFFSET = WINDOW_HEIGHT * 0.5f;

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
const float MAX_JUMP_FORCE = 425.f;
const float MIN_JUMP_FORCE = 100.f;
const float ORIGINAL_VERT_MOD = 1.0f; // Not used
// Drag
const float NORMAL_DRAG = 2.f;
const float AIR_DRAG = 0.f; 
const float STICK_DRAG = 10.f;
// Friction
const float NORMAL_FRICTION = 10.f;
const float ICE_FRICTION = 1.5f;
const float SLIME_FRICTION = 25.f;
const float FULL_STOP_FRICTION = 1 / e_deltaTime;

// Jump Arrow
const float MAX_HOLD_TIME = 0.5f;
const float MAX_HOLD_DISTANCE = 158.f;
const float MIN_HOLD_DISTANCE = 10.f;

// Collision
//---------------------------
const int COLLISION_LEFT   = 0x00000001;	//0001
const int COLLISION_RIGHT  = 0x00000002;	//0010
const int COLLISION_TOP    = 0x00000004;	//0100
const int COLLISION_BOTTOM = 0x00000008;	//1000