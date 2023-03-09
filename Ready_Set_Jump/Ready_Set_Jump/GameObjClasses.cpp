#include "GameObjClasses.hpp"
/**
  *  \file GameObjectClass.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\@digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  This file contains gameobject classes that will be used for making the stage and also a child class that is used for making player character there is also a function used here
  *		to create mesh
  *
*/
// Pointer to Mesh
AEGfxVertexList* pMesh = nullptr;
AEGfxVertexList* arrMesh = nullptr;
AEGfxVertexList* circleMesh = nullptr;
//fucntion defination that used to make mesh
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
void MakeArrowMesh() {
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		0.f, 0.f, 0xFFFFFFFF, 0.0f, 1.0f,
		1.f, 0.f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.f, 1.f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.f, 0.f, 0xFFFFFFFF, 1.0f, 1.0f,
		1.f, 1.f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.f, 1.f, 0xFFFFFFFF, 0.0f, 0.0f);
	// Saving the mesh (list of triangles) in pMesh
	arrMesh = AEGfxMeshEnd();
}
void MakeCircle() {
	AEGfxMeshStart();
	//Creating the circle shape
	int Parts = 12;
	for (float i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf(i * 2 * PI / Parts) * 0.5f, sinf(i * 2 * PI / Parts) * 0.5f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf((i + 1) * 2 * PI / Parts) * 0.5f, sinf((i + 1) * 2 * PI / Parts) * 0.5f, 0xFFFFFF00, 0.0f, 0.0f);
	}

	circleMesh = AEGfxMeshEnd();
}
// all defination that the Class Gameoobject will use most if not all variables comes with default value to prevent reading werid values
#pragma region Gameobject Class Defination
//constructor for GameObject
GameObject::GameObject(Vector2D Position, Vector2D Scale, ColourValue Colour, f32 Rotation, AEGfxRenderMode RenderMode, AEGfxVertexList* ObjectMesh, Vector2D Direction){
	position = Position; scale = Scale; colour = Colour; rotation = Rotation,renderMode = RenderMode,objMesh = ObjectMesh, direction = Direction;

}
#pragma region GameObject::Getter/Setter

Vector2D GameObject::GetPosition() {//Getter for position
	return position;
}
void GameObject::SetPosition(Vector2D Position) {//Setter for position
	position = Position;
}
Vector2D GameObject::GetScale() {//Getter for scale
	return scale;
}
void GameObject::SetScale(Vector2D Scale) {//Setter for scale
	scale = Scale;
}
ColourValue GameObject::GetColour() {//Getter for Colour
	return colour;
}
void GameObject::SetColour(ColourValue Colour) {//Setter for Colour
	colour = Colour;
}
f32 GameObject::GetRotation() {// Getter for rotation
	return rotation;
}
void GameObject::SetRotation(f32 Rotation) {// Setter for rotation
	rotation = Rotation;
}
void GameObject::SetTexture(AEGfxTexture* texturePointer) {
	ptex = texturePointer;
}
#pragma endregion
//the draw function for created object, can be changed when inherited
void GameObject::DrawObj() {
	AEGfxSetRenderMode(renderMode);
	AEGfxSetTintColor(colour.red, colour.green, colour.blue, colour.alpha);
	// Set blend mode to AE_GFX_BM_BLEND
	// This will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	// Set the texture to pTex
	//AEGfxTextureSet(pTex, 0, 0);
	// Create a scale matrix that scales by 100 x and y
	AEMtx33 Scale = { 0 };
	AEMtx33Scale(&Scale, scale.x, scale.y);
	// Create a rotation matrix that rotates by 0 degrees
	AEMtx33 Rotate = { 0 };
	AEMtx33Rot(&Rotate, rotation);
	// Create a translation matrix that translates by
	// 100 in the x-axis and 100 in the y-axis
	AEMtx33 Translate = { 0 };
	AEMtx33Trans(&Translate, position.x, position.y);
	// Concat the matrices (TRS)
	AEMtx33 Transform = { 0 };
	AEMtx33Concat(&Transform, &Rotate, &Scale);
	AEMtx33Concat(&Transform, &Translate, &Transform);
	// Choose the transform to use
	AEGfxSetTransform(Transform.m);
	// Actually drawing the mesh 
	AEGfxTextureSet(ptex, 0, 0);
	if (objMesh == nullptr) {
		printf("error\n");
	}
	AEGfxMeshDraw(objMesh, AE_GFX_MDM_TRIANGLES);
}
#pragma endregion

#pragma region Defination for DynamicObjClass
//constructor for any dynamic obj
DynamicObj::DynamicObj(Vector2D Velocity, Vector2D Position, Vector2D Scale, ColourValue Colour, f32 Rotation, AEGfxRenderMode RenderMode, AEGfxVertexList* ObjectMesh) {
	velocity = Velocity,position = Position; scale = Scale; colour = Colour; rotation = Rotation, renderMode = RenderMode, objMesh = ObjectMesh;
}
#pragma region Getter/Setter For DynamicObj

Vector2D DynamicObj::GetVelocity() {// returns object velocity 
		return velocity;
	}
void DynamicObj::SetVelocity(Vector2D Velocity) {//set object velocity
		velocity = Velocity;
	}

void DynamicObj::SetColFlag(int colFlag) {
	collisionFlag = colFlag;
}
int  DynamicObj::GetColFlag() {
	return collisionFlag;
}
#pragma endregion
#pragma endregion

#pragma region Platform Object Class
Platform::Platform(Vector2D Position, Vector2D Scale, ColourValue Colour, f32 Rotation, AEGfxRenderMode RenderMode, AEGfxVertexList* ObjectMesh) {
	position = Position; scale = Scale; colour = Colour; rotation = Rotation,renderMode = RenderMode, objMesh = ObjectMesh;
}

int Platform::GetPlatformType() {
	return platformType;
}

void Platform::SetPlatformType(int Type) {
	platformType = Type;
}
Platform& Platform::operator=(const Platform& p) {
	position = p.position; scale = p.scale; colour = p.colour; rotation = p.rotation;
	return *this;

}

#pragma endregion


