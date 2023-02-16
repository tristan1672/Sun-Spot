// ---------------------------------------------------------------------------
// includes
#pragma once
#include <cmath>

#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

enum { DEBUG = 1 };

// ---------------------------------------------------------------------------
// External Variables
extern float e_gravity, e_jumpForce;

extern int** e_levelGrid;
extern int BINARY_MAP_WIDTH{ 0 }, BINARY_MAP_HEIGHT{ 0 };
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