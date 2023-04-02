/*****************************************************************
  *  \file GameObjectClass.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)
  *
  *  \brief
  *  This file contains gameobject classes that will be used for making the stage and also a child class that is used for making player character there is also a function used here
  *	 to create mesh
  *
  * -MakeMesh()
  *		Makes the default rectangle mesh
  * -MakeArrowMesh()
  *		Make rectangle mesh, with center at its bottom, used for aim mode arrow
  * -MakeCircle()
  *		Makes circle mesh
  * -GameObject(Vector2D Position, Vector2D Scale, ColourValue Colour, f32 Rotation, AEGfxRenderMode RenderMode, AEGfxVertexList* ObjectMesh, Vector2D Direction)
  *		Default constructor for the class GameObject
  * -GetPosition()
  *		gets the position of gameobject class object
  * -SetPosition(Vector2D Position)
  *		sets the position of gameobject class object
  * -GetScale()
  *		gets the scale of gameobject class object
  * -SetScale(Vector2D Scale)
  *		sets the scale of gameobject class object
  * -GetColour()
  *		gets the colour of gameobject class object
  * -SetColour(ColourValue Colour)
  *		sets the colour of gameobject class object
  * -GetRotation()
  *		gets the rotation of gameobject class object
  * -SetRotation(f32 Rotation)
  *		sets the rotation of gameobject class object
  * -SetTexture(AEGfxTexture* texturePointer)
  *		sets the texture of gameobject class object
  * -SetRenderMode(AEGfxRenderMode render)
  *		sets the render mode of gameobject class object
  * -GetDirection()
  *		gets the direction of gameobject class object
  * -SetDirection(Vector2D Direction)
  *		sets the direction of gameobject class object
  * -DrawObj()
  *		draws Gameobject
  * -DynamicObj(Vector2D Velocity, Vector2D Position, Vector2D Scale, ColourValue Colour, f32 Rotation, AEGfxRenderMode RenderMode, AEGfxVertexList* ObjectMesh)
  *		default constructor of DynamicObj, inherits from GameObject
  * -GetVelocity()
  *		gets the velocity of DynamicObj class object
  * -SetVelocity(Vector2D Velocity)
  *		sets the velocity of DynamicObj class object
  * -SetColFlag(int colFlag)
  *		sets the collision flag of DynamicObj class object
  * -GetColFlag()
  *		gets the collision flag of DynamicObj class object
  * -Platform(Vector2D Position, Vector2D Scale, ColourValue Colour, f32 Rotation, AEGfxRenderMode RenderMode, AEGfxVertexList* ObjectMesh)
  *		default constructor for Platform object
  * -GetPlatformType()
  *		gets the platform type of Platform class object
  * -SetPlatformType(int Type)
  *		sets the platform type of Platform class object
  * -Platform::operator=(const Platform& p)
  *		operator overload for =, copies attributes of one platform to another
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "AEEngine.h"
#include "Utilities.hpp"
#include "Constants.hpp"
/*
this file contains gameobject class, a dynamic object class and function to make mesh on initialize all of wich are declearations;
*/

#ifndef GAME_OBJ_CLASSES_HPP
#define GAME_OBJ_CLASSES_HPP

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
	void SetRenderMode(AEGfxRenderMode render);
	Vector2D GetDirection();
	void SetDirection(Vector2D direction);
#pragma endregion

};
// obj class with extra booleans, use to check for collision, also contains velosity so it is affected by gravity and forces
class DynamicObj:public GameObject {
	int collisionFlag{};

public:
	Vector2D velocity{};
//physics modifiers
	float e_jumpForce = 350.f, vertMod = 1.0f,dragCoeff = 1.f, friction = 1.f, e_jumpForceMod = 1.0;
	bool jumpReady;

	//hot spot
	float topY{}, btmY{}, leftX{}, rightX{}, X1{}, X2{}, Y1{}, Y2{};

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

#endif // GAME_OBJ_CLASSES_HPP