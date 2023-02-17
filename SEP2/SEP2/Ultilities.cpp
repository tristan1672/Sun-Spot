#include "Ultilities.hpp"
float e_gravity = -150, e_jumpForce = 200, min_jumpForce = 150, vertMod = 1.0f;
const float original_jumpForce = 200, originalMin_jumpForce = 150, originalVertMod = 1.0f;

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