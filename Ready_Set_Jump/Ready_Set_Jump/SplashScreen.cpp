#include "AEEngine.h"
#include "GameStateManager.hpp"
#include "GameObjClasses.hpp"
#include "Utilities.hpp"

GameObject SplashScreen;
AEGfxTexture* SplashScreenTexture{ nullptr };
float maxSplashScreenTime = 4.f;
bool fadingIn = true;
void SplashScreen_Load() {
	MakeMesh();
	SplashScreenTexture = AEGfxTextureLoad("Assets/Images/DigiPen_BLACK.png");
	SplashScreen = GameObject({ 0.0f, 0.0f }, { 1270.f,720.f }, {1.0f, 1.0f, 1.0f, 0.0f}, 0.f, AE_GFX_RM_TEXTURE);
	SplashScreen.SetTexture(SplashScreenTexture);

}

void SplashScreen_Initialize() {

}

void SplashScreen_Update() {
	if (AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckTriggered(AEVK_SPACE) || maxSplashScreenTime <=0.f) {
		next = GS_MAINMENU;
	}
	if (maxSplashScreenTime > 0.f) {
		maxSplashScreenTime -= e_deltaTime;
		if (fadingIn) {
			ColourValue temp = SplashScreen.GetColour();
			temp.alpha += e_deltaTime;
			SplashScreen.SetColour(temp);
			if (SplashScreen.GetColour().alpha >= 1.f) fadingIn = false;
		}
		else
		{
			ColourValue temp = SplashScreen.GetColour();
			temp.alpha -= e_deltaTime;
			SplashScreen.SetColour(temp);
			if (SplashScreen.GetColour().alpha <= 0.f) fadingIn = true;
		}
	}

}

void SplashScreen_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	SplashScreen.DrawObj();
}

void SplashScreen_Free() {

}

void SplashScreen_Unload() {
	AEGfxTextureUnload(SplashScreenTexture);
	AEGfxMeshFree(pMesh);
}