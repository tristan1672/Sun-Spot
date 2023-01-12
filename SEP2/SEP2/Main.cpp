// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"



// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;

	//AEGfxVertexList * pMesh1 = 0;
	AEGfxVertexList * pMesh2 = 0;

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	//set background color
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Initialization end
	/////////////////////



	////////////////////////////////
	// Creating the objects (Shapes)

	// Informing the library that we're about to start adding triangles
	//AEGfxMeshStart();

	//// 1 triangle at a time
	//// X, Y, Color, texU, texV
	//AEGfxTriAdd(
	//	-25.5f, -25.5f, 0xFFFF0000, 0.0f, 0.0f,
	//	25.5f, 0.0f, 0xFFFF0000, 0.0f, 0.0f,
	//	-25.5f, 25.5f, 0xFFFF0000, 0.0f, 0.0f);

	//// Saving the mesh (list of triangles) in pMesh1

	//pMesh1 = AEGfxMeshEnd();
	//AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 0.0f, // When you have a differnt color at each point of the triangle 
		0.5f, -0.5f, 0x00FFFF00, 0.0f, 0.0f,  // The program will auto mix it, and it will show up as a gradient with each pixle
		-0.5f, 0.5f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");

	// Creating the objects (Shapes) end
	////////////////////////////////////



	////////////////////////////
	// Loading textures (images)

	// Loading textures (images) end
	//////////////////////////////////

	//////////////////////////////////
	// Creating Fonts	

	// Creating Fonts end
	//////////////////////////////////


	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update

		// Game loop update end
		///////////////////////


		//////////////////
		// Game loop draw

		//// Drawing object 1
		//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		//// Set position for object 1
		//AEGfxSetPosition(0.0f, 0.0f);
		//// No texture for object 1
		//AEGfxTextureSet(NULL, 0, 0);
		//// Drawing the mesh (list of triangles)
		//AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

		//// Drawing object 2 - (first)
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 2
		AEGfxSetPosition(100.0f, -60.0f);
		// No texture for object 2
		AEGfxTextureSet(NULL, 0, 0);

		// Drawing object 3 - (Second)
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 3
		AEGfxSetPosition(100.0f, 60.0f);
		// No texture for object 3
		AEGfxTextureSet(NULL, 0, 0);

		// Create a scale matrix that scales by 100 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 100.f, 100.f);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0.0f);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 100.f, 100.f);
		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale); // It starts from the back. Scaling the mesh, rotating it, then moving it
		AEMtx33Concat(&transform, &translate, &transform);
		// Choose the transform to use
		AEGfxSetTransform(transform.m);


		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
		// No tint
		//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f); // Removes color
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
		// Add Blue tint
		//AEGfxSetTintColor(0.0f, 0.0f, 1.0f, 1.0f);




		// Game loop draw end
		/////////////////////

		
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	//AEGfxMeshFree(pMesh1);
	AEGfxMeshFree(pMesh2);

	// free the system
	AESysExit();
}