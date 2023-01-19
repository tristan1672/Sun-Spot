#include "DrawShape.h"
AEGfxVertexList* pMesh = nullptr;
void MakeMesh() {
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();
}

void DrawRect(TransformVector rectTranslate, TransformVector rectScale, ColourValue rectColour , f32 rectRotation) {
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(rectColour.red, rectColour.green, rectColour.blue, rectColour.alpha);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	// Set the texture to pTex
	//AEGfxTextureSet(pTex, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, rectScale.x, rectScale.y);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, rectRotation);
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, rectTranslate.x, rectTranslate.y);
	// Concat the matrices (TRS)
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	// Choose the transform to use
	AEGfxSetTransform(transform.m);
	// Actually drawing the mesh 
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}