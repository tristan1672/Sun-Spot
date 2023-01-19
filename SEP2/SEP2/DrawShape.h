#pragma once
#include "AEEngine.h"
// Pointer to Mesh
void MakeMesh();
struct TransformVector {
	f32 x;
	f32 y;
};
struct ColourValue
{
	float red, green, blue, alpha;
};
void DrawRect(TransformVector rectTranslate = {0.f,0.f}, TransformVector rectScale = { 10.f,10.f }, ColourValue rectColour = {1.f,1.f,1.f,1.f}, f32 rectRotation = 0.f);