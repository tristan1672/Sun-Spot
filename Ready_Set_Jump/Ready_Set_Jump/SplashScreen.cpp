/*
  *  \file SplashScreen.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\\digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  Defination file, Splash Screen Scene,  mainly how the image should fade in and out
  * 
  *	 All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
*/
#include "AEEngine.h"
#include "GameStateManager.hpp"
#include "GameObjClasses.hpp"
#include "Utilities.hpp"

GameObject SplashScreen;
AEGfxTexture* SplashScreenTexture{ nullptr };
float maxSplashScreenTime = 4.f;
bool fadingIn = true;
void SplashScreen_Load() {
	MakeMesh();// makes mesh for the shape of the image
	SplashScreenTexture = AEGfxTextureLoad("Assets/Images/DigiPen_BLACK.png");//loads in the the texture from this path
	SplashScreen = GameObject({ 0.0f, 0.0f }, { 1270.f,720.f }, {1.0f, 1.0f, 1.0f, 0.0f}, 0.f, AE_GFX_RM_TEXTURE);// setting the properties of the image
	SplashScreen.SetTexture(SplashScreenTexture);// set the object to have the proper texture

}

void SplashScreen_Initialize() {

}

void SplashScreen_Update() {
	if (AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckTriggered(AEVK_SPACE) || maxSplashScreenTime <=0.f) {/*
		*  if left  mouse button or space is pressed the splash screen will skipped
		*/
		e_next_state = GS_MAINMENU;
	}
	/*
	 *  this section is responsible for fading the splash screen in and out
	 */
	if (maxSplashScreenTime > 0.f) {
		maxSplashScreenTime -= e_deltaTime;
		if (fadingIn) {// when the splash screen fades in, increases the alpha, scaled with delta_time
			ColourValue temp = SplashScreen.GetColour();
			temp.alpha += e_deltaTime/2.f;
			SplashScreen.SetColour(temp);
			if (SplashScreen.GetColour().alpha >= 1.f) fadingIn = false;
		}
		else // when the splash screen fades out, decrease the alpha, scaled with delta_time
		{
			ColourValue temp = SplashScreen.GetColour();
			temp.alpha -= e_deltaTime/2.f;
			SplashScreen.SetColour(temp);
			if (SplashScreen.GetColour().alpha <= 0.f) fadingIn = true;
		}
	}

}

void SplashScreen_Draw() {//calls draw functions
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	SplashScreen.DrawObj();
}

void SplashScreen_Free() {

}

void SplashScreen_Unload() {// frees the meshes and texture that was allocated in load()
	AEGfxTextureUnload(SplashScreenTexture);
	AEGfxMeshFree(pMesh);
}