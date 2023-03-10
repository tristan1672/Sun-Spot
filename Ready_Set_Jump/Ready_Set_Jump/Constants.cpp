#include "Constants.hpp"

// Window
//---------------------------
const int WINDOW_WIDTH   = 1270;
const int WINDOW_HEIGHT  = 720;
// Level
//---------------------------
// PLayer
const float PLAYER_SIZE_X = 30.0f;
const float PLAYER_SIZE_Y = 30.0f;
// Goal
const float GOAL_SIZE_X = 30.0f;
const float GOAL_SIZE_Y = 30.0f;
// Collectable
const float COLLECTABLE_SIZE_X = 30.0f;
const float COLLECTABLE_SIZE_Y = 30.0f;
// View Port
const int VIEWPORT_WIDTH  = 30;
const int VIEWPORT_HEIGHT = 30;
// Platform
const f32 GRID_WIDTH_SIZE = static_cast<f32>(WINDOW_WIDTH) / static_cast<f32>(VIEWPORT_WIDTH);
const f32 GRID_HEIGHT_SIZE = static_cast<f32>(WINDOW_HEIGHT) / static_cast<f32>(VIEWPORT_HEIGHT);
// Jump Arrow
extern const float MAX_HOLD_TIME = 0.5f;
extern const float MAX_HOLD_DISTANCE = 150.f;
extern const float MIN_HOLD_DISTANCE = 10.f;

// Collision
//---------------------------
const int COLLISION_LEFT   = 0x00000001;	//0001
const int COLLISION_RIGHT  = 0x00000002;	//0010
const int COLLISION_TOP    = 0x00000004;	//0100
const int COLLISION_BOTTOM = 0x00000008;	//1000