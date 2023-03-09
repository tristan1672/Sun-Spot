#include "Ultilities.hpp"

float e_gravity = -500.f;
const float max_jumpForce = 350.f, min_jumpForce = 100.f, originalVertMod = 1.0f,
airDrag = 0.f, stickDrag = 10.f, normalDrag = 2.f,
normalFriction = 10.f, iceFriction = 1.5f, fullStopFriction = 1 / e_deltaTime, slimeFriction = 25.f,
originalJumpForceMod = 1.0f;

const f32 e_gridWidthSize = WINDOW_WIDTH / viewPortWidth;
const f32 e_gridHeightSize = WINDOW_HEIGHT / viewPortHeight;


// Jump Arrow
extern float currHoldTime = 0.f, currHoldDistance = 0.f;
extern const float maxHoldTime = 0.5f, maxHoldDistance = 150.f, minHoldDistance= 10.f;

Vector2D normalDirection(f32 X1, f32 Y1, f32 X2, f32 Y2){
	f32 X = X2 - X1;
	f32 Y = Y1 - Y2;
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
	f32 Y = Y1 - Y2;
	return  sqrtf(static_cast<float>(X) * static_cast<float>(X) + static_cast<float>(Y) * static_cast<float>(Y));

}

Vector2D& Vector2D::operator-() {
	x = -x;
	y = -y;
	return *this;
}