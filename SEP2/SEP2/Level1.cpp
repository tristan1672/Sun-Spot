// ---------------------------------------------------------------------------
// includes
#pragma once

#include "Level1.hpp"

// ---------------------------------------------------------------------------


#define GROUND_LEVEL 20
 CameraPos cam;
 frogPos frog;
#define GROUND_LEVEL 20
static int s_levelGrid[GRID_SIZE][GRID_SIZE];
 //frogPos frog;
 mousePos mouse;
 DynamicObj Player;
 GameObject platform[GRID_SIZE][GRID_SIZE];
 GameObject jumpArrow;



int gGameRunning = 1;
bool flick = false;

bool shake;
float shakespeed;
float shakedistance = 0.5f;
f64 shaketime;

// Pointer to Mesh
AEGfxVertexList* groundMesh = nullptr;


std::fstream level1Map("Assets/Script/Level1.txt", std::ios_base::in);

// ----------------------------------------------------------------------------
// This function loads necessary data(resource and asset) and initialize it
// It is called once at the start of the state 
// ----------------------------------------------------------------------------
void Level1_Load()
{
	std::cout << "Level 1:Load\n";

	if (level1Map.is_open()) {
		std::cout << "Level 1 File opened\n";
	}
	else {
		std::cout << "Level 1 File Cannot be opened\n";
		exit(0);
	}

	char character = 0;
	int i = 0, j = 0;
	while (level1Map.get(character)) {

		if (j == GRID_SIZE) {
			j = 0;
			i++;

			if (i == GRID_SIZE) {
				break;
			}
		}

		if (character == '0' || character == '1') {
			s_levelGrid[i][j] = static_cast<int>(character) - 48;
			j++;
		}
		
		//std::cout << character;
		
	}

}

// ----------------------------------------------------------------------------
// This function initialize game object instances
// It is called once at the start of the state
// ----------------------------------------------------------------------------
void Level1_Initialize()
{
	std::cout << "Level 1:Initialize\n";

	Player = DynamicObj();
	Player.position = { 0,10 };

#pragma region set platform objects

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (s_levelGrid[i][j] == 1) {
				platform[i][j] = GameObject(
					{ gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * (WINDOW_WIDTH / GRID_SIZE), -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * (WINDOW_HEIGHT / GRID_SIZE) },
					{gridWidth, gridHeight});


			}
		}
	}
#pragma endregion

	jumpArrow = GameObject();
	jumpArrow.SetScale({ 10.f,100.f });
	jumpArrow.SetColour({ 0.f,1.f,0.f,0.5f });

	mouse.ClickX = 0;
	mouse.ClickY = 0;
	mouse.ReleaseX = 0;
	mouse.ReleaseY = 0;

	shake = false;
	shakespeed = 100.0f; //initialize shaking speed
	shakedistance = 0.5f; //initialize shaking distance

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
	groundMesh = AEGfxMeshEnd();

	MakeMesh();
}

// ----------------------------------------------------------------------------
// This function updates the state data
// It is called whenever there is a need to update the state's data
// ----------------------------------------------------------------------------
void Level1_Update()
{
	if (!Player.collideBotton) {
		Player.velocity.y += static_cast<float>(e_gravity * AEFrameRateControllerGetFrameTime());
		Player.position.y += static_cast<float>(Player.velocity.y * AEFrameRateControllerGetFrameTime());
		Player.position.x += static_cast<float>(Player.velocity.x * AEFrameRateControllerGetFrameTime());
	}


	//if (frog.Y > GROUND_LEVEL) {
	//	frog.velY += static_cast<float>(e_gravity * AEFrameRateControllerGetFrameTime());
	//	frog.Y += static_cast<float>(frog.velY * AEFrameRateControllerGetFrameTime());
	//	frog.X += static_cast<float>(frog.velX * AEFrameRateControllerGetFrameTime());
	//}
	//if (frog.Y <= GROUND_LEVEL && !frog.onFloor) {
	//	frog.velY = 0.0f;
	//	frog.velX = 0.0f;
	//	frog.Y = GROUND_LEVEL;
	//	frog.onFloor = true;
	//}

	// Mouse
	if (AEInputCheckTriggered(AEVK_LBUTTON) && Player.collideBotton) {
		AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);
	}
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.collideBotton) {
		Input_Handle_HoldCheck();
		if (e_jumpForce <= 100) {
			AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
			Vector2D mouseClickQuadPos = { static_cast<float>(mouse.ClickX) - WINDOW_WIDTH / 2.f, -(static_cast<float>(mouse.ClickY) - WINDOW_HEIGHT / 2.f) };
			Vector2D nDirection = normalDirection(mouse.ClickX, mouse.ClickY, mouse.ReleaseX, mouse.ReleaseY);
			float angle = atan2f(-nDirection.x,nDirection.y);
			std::cout << angle;
			jumpArrow.SetRotation(angle);
			jumpArrow.position = {mouseClickQuadPos.x,mouseClickQuadPos.y};
			std::cout << mouse.ReleaseY << "\n";
		}
	}
	if (AEInputCheckReleased(AEVK_LBUTTON) && Player.collideBotton) {
		AEInputGetCursorPosition(&mouse.ReleaseX, &mouse.ReleaseY);
		Input_Handle_Jump();
		jumpArrow.SetRotation(0);
		mouse.ReleaseX = 0; mouse.ReleaseY = 0;
	}

	//cam shake
	if (!frog.onFloor) //set shake and shaketime
	{
		shake = 1;
		shaketime = 0;
	}
	if ((shake == 1) && (frog.onFloor) && (shaketime < 0.2f)) //shake condition
	{
		shaketime += AEFrameRateControllerGetFrameTime();
		float distance = cam.Y - frog.Y;
		if (shakespeed >= 0)
		{
			if (distance > shakedistance)
			{
				shakespeed *= -1.0f;
			}
		}
		else
		{
			if (distance < -shakedistance)
			{
				shakespeed *= -1.0f;
			}
		}
		cam.Y = frog.Y + shakespeed * AEFrameRateControllerGetFrameTime();
	}
	collisionCheck(Player.position.x, Player.position.y);

	AEGfxSetCamPosition(cam.X, cam.Y); //cam position
	
}

// ----------------------------------------------------------------------------
// This function sends data that needs to be drawn to the graphic engine
// It is called after update to show animation/movement
// ----------------------------------------------------------------------------
void Level1_Draw()
{

	// Set the background to black.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	//// Tell the engine to get ready to draw something with texture.
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//// Set the tint to white, so that the sprite can 
	//// display the full range of colors (default is black).
	//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	//// Set blend mode to AE_GFX_BM_BLEND
	//// This will allow transparency.
	//AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	//AEGfxSetTransparency(1.0f);
	//// Set the texture to pTex
	////AEGfxTextureSet(pTex, 0, 0);
	//// Create a scale matrix that scales by 100 x and y
	AEMtx33 scale = { 0 };
	AEMtx33 rotate = { 0 };
	AEMtx33 translate = { 0 };
	AEMtx33 transform = { 0 };

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (s_levelGrid[i][j] == 1) {

				//AEMtx33Scale(&scale, gridWidth, gridHeight);
				//AEMtx33Rot(&rotate, 0);
				//AEMtx33Trans(&translate, gridWidth / 2.0f - (WINDOW_WIDTH / 2.0f) + j * (WINDOW_WIDTH / GRID_SIZE), -gridHeight / 2.0f + (WINDOW_HEIGHT / 2.0f) - i * (WINDOW_HEIGHT / GRID_SIZE));
				//AEMtx33Concat(&transform, &rotate, &scale);
				//AEMtx33Concat(&transform, &translate, &transform);
				//AEGfxSetTransform(transform.m);
				//AEGfxMeshDraw(groundMesh, AE_GFX_MDM_TRIANGLES);
				platform[i][j].DrawObj();
			}
		}
	}
	Player.DrawObj();
	if (AEInputCheckCurr(AEVK_LBUTTON) && Player.collideBotton && e_jumpForce <= 100) {
		jumpArrow.DrawObj();
	}
}

// ----------------------------------------------------------------------------
// This function frees objects instances
// It is called after to prepare the state to be unloaded or initialized again
// ----------------------------------------------------------------------------
void Level1_Free()
{
	std::cout << "Level 1:Free\n";

	level1Map.close();
}

// ----------------------------------------------------------------------------
// This function dumps all loaded during Level1_Load()
// It is called when the state should be terminated
// ----------------------------------------------------------------------------
void Level1_Unload()
{
	std::cout << "Level 1:Unload\n";
}

void collisionCheck(float playerX, float playerY) {

	float gridWidth = WINDOW_WIDTH / GRID_SIZE;
	float gridHeight = WINDOW_HEIGHT / GRID_SIZE;

	// Need find current location in grid 1st
	// Then check the surrounding for collision

	// Checking current location
	double width = -(WINDOW_WIDTH / 2.0f);
	double height = WINDOW_HEIGHT / 2.0f;
	int xCoord = 0, yCoord = 0;

	// Getting X coord in grid
	while (1) {
		if (playerX > width) {
			width += gridWidth;
			xCoord++;
		}
		else {
			xCoord -= 1;
			break;
		}
	}

	// Getting Y coord in grid
	while (1) {
		if (playerY < height) {
			height -= gridHeight;
			yCoord++;
		}
		else {
			yCoord -= 1;
			break;
		}
	}

	//std::cout << "Width Grid: " << xCoord + 1 << "\n";
	//std::cout << "Height Grid: " << yCoord + 1 << "\n";

	// Working seperately, not together
	bool leftHit = false, rightHit = false, topHit = false, btmHit = false;

	// Left & Right Collision Detecttion
	if (playerX > (xCoord*gridWidth - WINDOW_WIDTH/2.0f) && s_levelGrid[yCoord][xCoord] == 1) {
		// If on the left halve of a block
		if (playerX < (xCoord*gridWidth - WINDOW_WIDTH/2.0f + gridWidth/2.0f) ) {
			//frog.X -= 5;
			//frog.X = xCoord * gridWidth - WINDOW_WIDTH/2.0f;
			leftHit = true;

		}
		// If on the right halve of a block
		else if (playerX > (xCoord * gridWidth - WINDOW_WIDTH/2.0f + gridWidth/2.0f) ) {
			//frog.X += 5;
			//frog.X = (xCoord+1) * gridWidth - WINDOW_WIDTH/2.0f;
			rightHit = true;
		}
	}
	
	/*
	// Up & Down Collision Detecttion
	if (frogY < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight) && s_levelGrid[yCoord][xCoord] == 1) {
		// If on the top of the block (Platform below you)
		if (frog.Y > (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			frog.onFloor = true;
			//frog.Y = WINDOW_HEIGHT / 2.0f - yCoord * gridHeight;
			//frog.Y += 5;
			topHit = true;
		}
		// If on the btm of the block (Platform above you)
		else if (frog.Y < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			//frog.Y = WINDOW_HEIGHT / 2.0f - (yCoord+1) * gridHeight;
			//frog.Y -= 5;
			btmHit = true;
		}
	}
	*/

	if (playerY < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight) && s_levelGrid[yCoord][xCoord] == 1) {
		// If on the top of the block (Platform below you)
		if (Player.position.y > (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			Player.collideBotton = true;
			//frog.Y = WINDOW_HEIGHT / 2.0f - yCoord * gridHeight;
			//frog.Y += 5;
			topHit = true;
		}
		// If on the btm of the block (Platform above you)
		else if (Player.position.y < (WINDOW_HEIGHT / 2.0f - yCoord * gridHeight - gridHeight / 2.0f)) {
			//frog.Y = WINDOW_HEIGHT / 2.0f - (yCoord+1) * gridHeight;
			//frog.Y -= 5;
			btmHit = true;
		}
	}
	

	if (rightHit == true) {
		Player.position.x += static_cast<float>(Player.velocity.x * AEFrameRateControllerGetFrameTime());
		Player.velocity.x = 0;
		std::cout << "Hit Right 50% of block\n";
	}
	if (leftHit == true) {
		Player.position.x -= static_cast<float>(Player.velocity.x * AEFrameRateControllerGetFrameTime());
		Player.velocity.x = 0;
		std::cout << "Hit Left 50% of block \n";
	}

	if (topHit == true) {
		Player.position.y -= static_cast<float>(Player.velocity.y* AEFrameRateControllerGetFrameTime());
		std::cout << "Hit Top of block\n";
		//frog.velY = 0;
	}

	if (btmHit == true) {
		Player.position.y -= static_cast<float>(Player.velocity.y * AEFrameRateControllerGetFrameTime());
		std::cout << "Hit Btm of block\n";
		//frog.velY = 0;
	}




}