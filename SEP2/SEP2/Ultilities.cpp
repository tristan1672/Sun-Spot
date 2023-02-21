#include "Ultilities.hpp"
float e_gravity = -400.f, e_jumpForce = 300.f, min_jumpForce = 300.f, vertMod = 1.0f,
dragCoeff = 1.f, friction = 1.f;
const float original_jumpForce = 300.f, originalMin_jumpForce = 300.f, originalVertMod = 1.0f,
airDrag = 0.f, stickDrag = 4.f, normalDrag = 2.f,
normalFriction = 10.f, iceFriction = 1.5f, fullStopFriction = 1 / AEFrameRateControllerGetFrameTime();

Vector2D normalDirection(f32 X1, f32 Y1, f32 X2, f32 Y2){
	f32 X = X2 - X1;
	f32 Y = Y1 - Y2;
	float normal = sqrtf(static_cast<float>(X) * static_cast<float>(X) + static_cast<float>(Y) * static_cast<float>(Y));
	if (normal) {
		return { static_cast<float>(X) / normal, static_cast<float>(Y) / normal };
	}
	else
	{
		return { 0,0 };
	}
}