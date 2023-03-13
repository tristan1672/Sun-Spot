#pragma once
#include "AEEngine.h"
#include "Ultilities.hpp"
#include "Constants.hpp"
/*
this file contains gameobject class, a dynamic object class and function to make mesh on initialize all of wich are declearations;
*/



extern AEGfxVertexList* pMesh;
extern AEGfxVertexList* arrMesh;
extern AEGfxVertexList* circleMesh;
void MakeMesh()/*used to make default mesh*/;
void MakeArrowMesh();// use for arrow mesh
void MakeCircle(); //used for circle objects

// normal game object class, conatins all transformation data for an game object and also a function that draws the gameobject along with its colour
class GameObject {
	//GameObject perameters
protected:
	Vector2D scale;
	ColourValue colour;
	f32 rotation;
	AEGfxRenderMode renderMode;
	AEGfxTexture* ptex{nullptr};
	AEGfxVertexList* objMesh{ nullptr };
public:
	Vector2D position;
	Vector2D direction{ 0 };
	//the draw function for created object, can be changed when inherited
	virtual void DrawObj();

	//constructor
	GameObject(Vector2D Position = { 0.f,0.f }, Vector2D Scale = { 10.f,10.f }, 
		ColourValue Colour = { 1.f,1.f,1.f,1.f }, f32 Rotation = 0.f, AEGfxRenderMode RenderMode = AE_GFX_RM_COLOR, AEGfxVertexList* ObjectMesh = pMesh, Vector2D Direction = {0,0});
#pragma region Getter/Setter

	Vector2D GetPosition();
	void SetPosition(Vector2D Position);
	Vector2D GetScale();
	void SetScale(Vector2D Scale);
	ColourValue GetColour();
	void SetColour(ColourValue Colour);
	f32 GetRotation();
	void SetRotation(f32 Rotation);
	void SetTexture(AEGfxTexture* texturePointer);
#pragma endregion

};
// obj class with extra booleans, use to check for collision, also contains velosity so it is affected by gravity and forces
class DynamicObj:public GameObject {
	int collisionFlag{};

//use for 
	bool prevFrameStickyCollision{}, currFrameStickyCollision{};


public:
	Vector2D velocity;
//physics modifiers
	float e_jumpForce = 350.f, vertMod = 1.0f,dragCoeff = 1.f, friction = 1.f, e_jumpForceMod = 1.0;
	bool jumpReady = true, collideTop = false, collideRight = false, collideLeft = false;

	//hot spot
	int topY{}, btmY{}, leftX{}, rightX{}, X1{}, X2{}, Y1{}, Y2{};

	DynamicObj(Vector2D Velocity = {0.f,0.f}, Vector2D Position = {0.f,0.f}, Vector2D Scale = { PLAYER_SIZE_X, PLAYER_SIZE_Y }, 
		ColourValue Colour = {1.f,1.f,1.f,1.f}, f32 Rotation = 0, AEGfxRenderMode RenderMode = AE_GFX_RM_COLOR, AEGfxVertexList* ObjectMesh = pMesh);
#pragma region Getter/Setter

	Vector2D GetVelocity();
	void SetVelocity(Vector2D Velocity);
	void PhysicsUpdate();
	void SetColFlag(int colFlag);
	int  GetColFlag();
	void LevelCollision();
	void SnapToGrid();
#pragma endregion
};

class Platform: public GameObject {
	int platformType{};
public:
	Platform(Vector2D Position = { 0.f,0.f }, Vector2D Scale = { 10.f,10.f },
		ColourValue Colour = { 1.f,1.f,1.f,1.f }, f32 Rotation = 0, AEGfxRenderMode RenderMode = AE_GFX_RM_COLOR, AEGfxVertexList* ObjectMesh = pMesh);
	Platform& operator=(const Platform& p);

	int GetPlatformType();
	void SetPlatformType(int Type);
};