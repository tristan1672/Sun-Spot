// ---------------------------------------------------------------------------
// Includes
#pragma once
#include <cmath>
#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

// ---------------------------------------------------------------------------
// Defines
#define DEBUG false
// --------------------------------------------------------------------------- // End of defines

// ---------------------------------------------------------------------------
// Enumerations
enum { NO_SHAKE = 0, MEDIUM_SHAKE , HEAVY_SHAKE };
enum { EMPTY_SPACE = 0, NORMAL_BLOCK, ICE_BLOCK, STICKY_BLOCK, GOAL, COLLECTABLES = 9};
enum { PLAYING = 0, WIN = 1,};
enum { EASY, MEDIUM, HARD};
// --------------------------------------------------------------------------- // End of enumerations

// ---------------------------------------------------------------------------
// External Variables
// Font
extern s8 e_fontID;

// Physics
extern float e_gravity, e_jumpForce, min_jumpForce , vertMod,dragCoeff, friction, currHoldTime;
extern const float original_jumpForce, originalMin_jumpForce, originalVertMod, airDrag, stickDrag, normalDrag, normalFriction, iceFriction, fullStopFriction, maxHoldTime;

// Time
extern float e_deltaTime, e_levelTime;


// Level
extern int level1_state;
extern int** e_levelGrid;
extern int e_binaryMapWidth, e_binaryMapHeight;
extern int e_collectableNum;

// Collision
//extern Platform** platform;
extern int e_collisionFlag;

// Camera
extern short e_shakeStrength;
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------
// Structs
struct Vector2D {
	f32 x;
	f32 y;
};
struct ColourValue
{
	float red, green, blue, alpha;
};

Vector2D normalDirection(f32 X1, f32 Y1, f32 X2, f32 Y2);

struct mousePos {
	s32 ClickX;
	s32 ClickY;
	s32 ReleaseX;
	s32 ReleaseY;
};

struct CameraPos
{
	f32 X;
	f32 Y;
};
// --------------------------------------------------------------------------- // End of structs