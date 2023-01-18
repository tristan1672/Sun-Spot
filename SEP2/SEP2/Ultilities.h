// ---------------------------------------------------------------------------
// includes
#include <cmath>

#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

// ---------------------------------------------------------------------------
// External Variables
extern float e_gravity{ 150.0f }, e_jumpForce(200.0f);
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------
// Structs
struct vector {
	double X{ 0 };
	double Y{ 0 };
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
	float X{ 0 };
	float Y{ 0 };
	float velX{ 0 };
	float velY{ 0 };
	bool onFloor{ true };
};

struct mousePos {
	s32 ClickX{ 0 };
	s32 ClickY{ 0 };
	s32 ReleaseX{ 0 };
	s32 ReleaseY{ 0 };
};
// --------------------------------------------------------------------------- // End of structs