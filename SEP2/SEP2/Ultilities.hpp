// ---------------------------------------------------------------------------
// includes
#pragma once
#include <cmath>

#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

enum { DEBUG = 1 };
enum { NO_SHAKE = 0, MEDIUM_SHAKE , HEAVY_SHAKE };
enum { EMPTY = 0, NORMAL_BLOCK, ICE_BLOCK };

// ---------------------------------------------------------------------------
// External Variables
extern float e_gravity, e_jumpForce, min_jumpForce, original_jumpForce;

extern int** e_levelGrid;
extern int BINARY_MAP_WIDTH, BINARY_MAP_HEIGHT;

//extern Platform** platform;
extern int e_collisionFlag;
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