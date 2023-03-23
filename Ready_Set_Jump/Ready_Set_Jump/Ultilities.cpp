#include "Ultilities.hpp"

float e_gravity = -600.f;

// Jump Arrow
extern float currHoldTime = 0.f, currHoldDistance = 0.f;

Vector2D normalDirection(f32 X1, f32 Y1, f32 X2, f32 Y2){
	f32 X = X2 - X1;
	f32 Y = Y2 - Y1;
	float normal = Distance(X1,Y1,X2,Y2);	
	if (normal) {
		return { static_cast<float>(X) / normal, static_cast<float>(Y) / normal };
	}
	else
	{
		return { 0,0 };
	}
}

float Distance(f32 X1, f32 Y1, f32 X2, f32 Y2) {
	f32 X = X2 - X1;
	f32 Y = Y2 - Y1;
	return  sqrtf(static_cast<float>(X) * static_cast<float>(X) + static_cast<float>(Y) * static_cast<float>(Y));

}

Vector2D& Vector2D::operator-() {
	x = -x;
	y = -y;
	return *this;
}