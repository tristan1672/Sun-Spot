// ---------------------------------------------------------------------------
// includes
#include <cmath>

#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

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

vector normalDirection(s32 X1, s32 Y1, s32 X2, s32 Y2) {
	s32 X = X2 - X1;
	s32 Y = Y1 - Y2;
	double normal = sqrt(static_cast<double>(X) * static_cast<double>(X) + static_cast<double>(Y) * static_cast<double>(Y));
	if (normal) {
		return { static_cast<double>(X) / normal, static_cast<double>(Y) / normal };
	}
	else
	{
		return { 0,0 };
	}
}

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