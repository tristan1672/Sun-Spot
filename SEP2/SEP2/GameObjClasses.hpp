#pragma once
#include "AEEngine.h"
#include "Ultilities.hpp"
/*
this file contains gameobject class, a dynamic object class and function to make mesh on initialize all of wich are declearations;
*/

#define PLAYER_SIZE_X 30.0f
#define PLAYER_SIZE_Y 30.0f

void MakeMesh()/*used to make default mesh*/;

// normal game object class, conatins all transformation data for an game object and also a function that draws the gameobject along with its colour
class GameObject {
	//GameObject perameters
protected:
	Vector2D scale;
	ColourValue colour;
	f32 rotation;
public:
	Vector2D position;
	//the draw function for created object, can be changed when inherited
	virtual void DrawObj();

	//constructor
	GameObject(Vector2D Position = { 0.f,0.f }, Vector2D Scale = { 10.f,10.f }, ColourValue Colour = { 1.f,1.f,1.f,1.f }, f32 Rotation = 0);
#pragma region Getter/Setter

	Vector2D GetPosition();
	void SetPosition(Vector2D Position);
	Vector2D GetScale();
	void SetScale(Vector2D Scale);
	ColourValue GetColour();
	void SetColour(ColourValue Colour);
	f32 GetRotation();
	void SetRotation(f32 Rotation);
#pragma endregion

};
// obj class with extra booleans, use to check for collision, also contains velosity so it is affected by gravity and forces
class DynamicObj:public GameObject {
public:
	Vector2D velocity;
	bool collideBotton = true, collideTop = false, collideRight = false, collideLeft = false;
	DynamicObj(Vector2D Velocity = {0.f,0.f}, Vector2D Position = {0.f,0.f}, Vector2D Scale = { PLAYER_SIZE_X, PLAYER_SIZE_Y }, ColourValue Colour = {1.f,1.f,1.f,1.f}, f32 Rotation = 0);
#pragma region Getter/Setter

	Vector2D GetVelocity();
	void SetVelocity(Vector2D Velocity);
#pragma endregion
};

class Platform: public GameObject {
	int platformType{};
public:
	Platform(Vector2D Position = { 0.f,0.f }, Vector2D Scale = { 10.f,10.f }, ColourValue Colour = { 1.f,1.f,1.f,1.f }, f32 Rotation = 0);
	Platform& operator=(const Platform& p);

	int GetPlatformType();
	void SetPlatformType(int Type);
};