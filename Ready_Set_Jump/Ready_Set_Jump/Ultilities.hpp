// ---------------------------------------------------------------------------
// Includes
#pragma once
#include <cmath>
#include "PreCompiledHeader.hpp"
#include "Constants.hpp"
#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

// ---------------------------------------------------------------------------
// Defines
#define DEBUG false
// --------------------------------------------------------------------------- // End of defines

// ---------------------------------------------------------------------------
// Enumerations
enum { NO_SHAKE = 0, MEDIUM_SHAKE , HEAVY_SHAKE };
enum { EMPTY_SPACE = 0, NORMAL_BLOCK, ICE_BLOCK, STICKY_BLOCK, SLIME_BLOCK, GOAL = 7, HINT = 8 ,COLLECTABLES};
enum { PAUSED, PLAYING , WIN ,};
enum { EASY, MEDIUM, HARD};
// --------------------------------------------------------------------------- // End of enumerations

// ---------------------------------------------------------------------------
// External Variables
// Font
extern s8 e_fontID;

// Physics
extern float e_gravity;
extern const float max_jumpForce, min_jumpForce, originalVertMod, airDrag, stickDrag, normalDrag,
normalFriction, iceFriction, fullStopFriction, slimeFriction,
originalJumpForceMod;

// Time
extern float e_deltaTime, e_levelTime;

// Jump Arrow
extern float currHoldTime, currHoldDistance;
extern const float maxHoldTime, maxHoldDistance, minHoldDistance;


// Level
extern f32 e_playerSpawnPointX, e_playerSpawnPointY;
extern int level1_state;
extern int** e_levelGrid;
extern int e_binaryMapWidth, e_binaryMapHeight;
extern int e_totalNumOfCollectable, e_numOfCollectableCollected;

// Camera
extern short e_shakeStrength;
extern bool shake;
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------
// Structs
struct Vector2D {
	f32 x;
	f32 y;
	Vector2D& operator-();
};
struct ColourValue
{
	float red, green, blue, alpha;
};

Vector2D normalDirection(f32 X1, f32 Y1, f32 X2, f32 Y2);
float Distance(f32 X1, f32 Y1, f32 X2, f32 Y2);

struct mousePos {
	s32 ClickX;
	s32 ClickY;
	s32 ReleaseX;
	s32 ReleaseY;
};


// --------------------------------------------------------------------------- // End of structs