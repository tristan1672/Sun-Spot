// ---------------------------------------------------------------------------
// Includes
#pragma once
#include <cmath>
#include "PreCompiledHeader.hpp"
#include "Constants.hpp"
#include "AEEngine.h"
// --------------------------------------------------------------------------- // End of includes

// ---------------------------------------------------------------------------
// Defines
#define DEBUG false
// --------------------------------------------------------------------------- // End of defines

// ---------------------------------------------------------------------------
// Enumerations
enum { NO_SHAKE = 0, MEDIUM_SHAKE , HEAVY_SHAKE };
enum { EMPTY_SPACE = 0, NORMAL_BLOCK, ICE_BLOCK, STICKY_BLOCK, SLIME_BLOCK,PLAYER_SPAWN, GOAL = 7, CHECKPOINT ,COLLECTIBLES};
enum { PAUSED, PLAYING , WIN ,SCENE_SWITCH_BUFFER};
enum { EASY, MEDIUM, HARD};
enum { MAIN, LS, STAGE};
// --------------------------------------------------------------------------- // End of enumerations

// ---------------------------------------------------------------------------
// External Variables

// Different States 
extern int e_current_state, e_previous_state, e_next_state;

// Function Pointers
typedef void(*FP)(void);
extern FP e_fpLoad, e_fpInitialize, e_fpUpdate, e_fpDraw, e_fpFree, e_fpUnload;

// Font
extern s8 e_fontID;
extern s8 e_creditFontID;

// Physics
extern float e_gravity;

// Time
extern float e_deltaTime, e_levelTime;

// Jump Arrow
extern float currHoldTime, currHoldDistance;

// Score animation
extern bool e_scoreAnimation;

// Score flag
extern int e_skip;
extern int e_move;

// Structs
struct Vector2D {
	f32 x;
	f32 y;
	Vector2D& operator-();
};
struct ColourValue
{
	float red, green, blue, alpha;
};

// Level
extern Vector2D playerSpawnPoint;
extern int level_state;
extern int** e_levelGrid;
extern int e_binaryMapWidth, e_binaryMapHeight;
extern int e_totalNumOfcollectible, e_numOfcollectibleCollected;
extern int e_uiState;
extern bool e_outOfMap;

// Camera
extern short e_shakeStrength;
extern bool shake;
// --------------------------------------------------------------------------- // End of external variables

// ---------------------------------------------------------------------------


static const ColourValue GreenTea{ 0.33f,0.61f,0.19f,0.f };
static const ColourValue Green{ 0.82f,0.94f,0.75f,1.f };
static const ColourValue Red{ 0.73f,0.118f,0.063f,1.f };
static const ColourValue Yellow{ 0.97f,0.71f,0.f,1.f };
static const ColourValue White{ 1.f,1.f,1.f,1.f };
static const ColourValue Black{ 0.f,0.f,0.f,1.f };
static const ColourValue Grey{ 0.5f,0.5f,0.5f,0.5f };

Vector2D normalDirection(f32 X1, f32 Y1, f32 X2, f32 Y2);
float Distance(f32 X1, f32 Y1, f32 X2, f32 Y2);

struct mousePos {
	s32 ClickX;
	s32 ClickY;
	s32 ReleaseX;
	s32 ReleaseY;
};


// --------------------------------------------------------------------------- // End of structs