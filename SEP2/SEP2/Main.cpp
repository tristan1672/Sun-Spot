// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include <iostream>



// ---------------------------------------------------------------------------
// main
struct vector { 
	s32 X{0};
	s32 Y{0};
};
vector normalDirection(s32 ClickX, s32 ClickY, s32 ReleaseX, s32 ReleaseY) {
	return { (ReleaseX - ClickX),(ReleaseY - ClickY) };
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	struct frogPos
	{
		float X{0};
		float Y{0};
		float velX{0};
		float velY{0};
		bool onFloor{true};
	};
	struct mousePos {
		s32 ClickX{ 0 };
		s32 ClickY{ 0 };
		s32 ReleaseX{ 0 };
		s32 ReleaseY{ 0 };
	};

	frogPos frog;
	mousePos mouse;
	vector Direction;

	float gravity{ -50 };
	float jumpForce{ 50 };
	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1270, 720, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	// === ADDED CODE ===
	// Pointer to Mesh
	AEGfxVertexList* pMesh = 0;
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

	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/PlanetTexture.png");

	// ===




	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Your own update logic goes here
		if (frog.Y > 0) {
			frog.velY += gravity * AEFrameRateControllerGetFrameTime();
			frog.Y += frog.velY * AEFrameRateControllerGetFrameTime();
			frog.X += frog.velX * AEFrameRateControllerGetFrameTime();
		}
		if (frog.Y <= 0 &&!frog.onFloor) {
			frog.velY = 0;
			frog.velX = 0;
			frog.Y = 0;
			frog.onFloor = true;
		}
		if (AEInputCheckTriggered(AEVK_SPACE) && frog.onFloor) {
			frog.velY = jumpForce ;
			frog.velX = jumpForce ;
			frog.Y += frog.velY * AEFrameRateControllerGetFrameTime();
			frog.X += frog.velX * AEFrameRateControllerGetFrameTime();
			frog.onFloor = false;
		}
		
		if (AEInputCheckTriggered(AEVK_LBUTTON) && frog.onFloor) {
			AEInputGetCursorPosition(&mouse.ClickX,&mouse.ClickY);
		}
		if (AEInputCheckReleased(AEVK_LBUTTON) && frog.onFloor) {
			AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
		}

		// Your own rendering logic goes here
		
		// === ADDED CODE ===
		// Set the background to black.
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set the tint to white, so that the sprite can 
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Set blend mode to AE_GFX_BM_BLEND
		// This will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		// Set the texture to pTex
		//AEGfxTextureSet(pTex, 0, 0);
		// Create a scale matrix that scales by 100 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 10.f, 10.f);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate,frog.X , frog.Y);
		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		// Choose the transform to use
		AEGfxSetTransform(transform.m);
		// Actually drawing the mesh 
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		// ===


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	// free the system
	AESysExit();
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);

}