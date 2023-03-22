#include "AEEngine.h"
#include "GameStateManager.hpp"
#include "GameObjClasses.hpp"

GameObject SplashScreen;
AEGfxTexture* SplashScreenTexture{ nullptr };
void SplashScreen_Load() {
	MakeMesh();
	SplashScreenTexture = AEGfxTextureLoad("Assets/Images/DigiPen_BLACK.png");
	SplashScreen = GameObject({ 0.0f, 0.0f }, { 1000.f,500.f }, {1.0f, 1.0f, 1.0f, 1.0f}, 0.f, AE_GFX_RM_TEXTURE);
	SplashScreen.SetTexture(SplashScreenTexture);

}

void SplashScreen_Initialize() {

}

void SplashScreen_Update() {
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		next = GS_MAINMENU;
	}
}

void SplashScreen_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	SplashScreen.DrawObj();
}

void SplashScreen_Free() {

}

void SplashScreen_Unload() {
	delete SplashScreenTexture;
	AEGfxMeshFree(pMesh);
}