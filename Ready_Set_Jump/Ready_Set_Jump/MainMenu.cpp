#include "MainMenu.hpp"
UIText select_Level;
UIText quit;
UIText guide;

void Menu_Load() {
	MakeMesh();
}

void Menu_Initialize() {
	select_Level = UIText("Select Level", { -0.26f, 0.3f },{1.f,1.f},{1.f,1.f,1.f,1.f}, true,{ 0.f,1.f,1.f,1.f });
	quit = UIText("Quit", { -0.09f, -0.5f }, { 1.f,1.f }, { 1.f,1.f,1.f,1.f }, true, { 0.f,1.f,1.f,1.f });
	guide= UIText("How To Play", { -0.23f, -0.1f }, { 1.f,1.f }, { 1.f,1.f,1.f,1.f }, true, { 0.19f, 0.8f, 0.19f,1.f });
}

void Menu_Update() {
	mousePos mouse{};
	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);

		if ( select_Level.MouseCollision({ mouse.ClickX ,mouse.ClickY})) {
			next = GS_LEVEL;
		}
		if (quit.MouseCollision({ mouse.ClickX ,mouse.ClickY })) {
			next = GS_QUIT;
		}
	}

}

void Menu_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	select_Level.DrawObj();
	quit.DrawObj();
	guide.DrawObj();
}

void Menu_Free() {

}

void Menu_Unload() {
	AEGfxMeshFree(pMesh);
}