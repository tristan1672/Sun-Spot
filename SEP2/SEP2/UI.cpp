#include "UI.hpp"

AEGfxVertexList* UImesh = nullptr;


void UIMesh()
{
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
	UImesh = AEGfxMeshEnd();
}
/*
* Function takes in pointer to texture, x coordinate , y coordinate, x scaling, y scaling
*/
void DrawTexture(AEGfxTexture* ptex, f32 pos_x, f32 pos_y, f32 scale_x, f32 scale_y) 
{

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	// Tell the engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set the tint to white, so that the sprite can 
	// display the full range of colors (default is black).
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	// Set the texture to pTex
	AEGfxTextureSet(ptex, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 Scale = { 0 };
	AEMtx33Scale(&Scale, scale_x, scale_y);
	// Create a rotation matrix that rotates by 45 degrees
	AEMtx33 Rotate = { 0 };
	AEMtx33Rot(&Rotate, 0.0f);
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
	AEMtx33 Translate = { 0 };
	AEMtx33Trans(&Translate, pos_x, pos_y);
	// Concat the matrices (TRS)
	AEMtx33 Transform = { 0 };
	AEMtx33Concat(&Transform, &Rotate, &Scale);
	AEMtx33Concat(&Transform, &Translate, &Transform);
	// Choose the transform to use
	AEGfxSetTransform(Transform.m);
	// Actually drawing the mesh 
	AEGfxMeshDraw(UImesh, AE_GFX_MDM_TRIANGLES);
	
}