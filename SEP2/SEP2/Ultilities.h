// ---------------------------------------------------------------------------
// includes
#pragma once
#include <cmath>

#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

#define GRID_SIZE 10

enum { DEBUG = 1 };

// ---------------------------------------------------------------------------
// External Variables
extern float e_gravity , e_jumpForce;
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------
// Structs
struct vector {
	double X;
	double Y;
};

vector normalDirection(s32 X1, s32 Y1, s32 X2, s32 Y2);

struct frogPos
{
	float X;
	float Y;
	float velX;
	float velY;
	bool onFloor;
};

struct mousePos {
	s32 ClickX;
	s32 ClickY;
	s32 ReleaseX;
	s32 ReleaseY;
};
// --------------------------------------------------------------------------- // End of structs