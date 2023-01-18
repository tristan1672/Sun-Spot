#include "Ultilities.h"
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