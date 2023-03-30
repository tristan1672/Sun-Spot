#include "Credits.hpp"

UIText* creditInfo[100];
static float creditTimer;

void Credits_Load() {
	AEGfxSetCamPosition(0.f, 0.f);
}

void Credits_Initialize() {

	creditTimer = 0.f;

	AEVec2 titleSize{ 1.5f, 1.5f };
	AEVec2 textSize{ 1.f, 1.f };

	// Team
	// Set 0
	creditInfo[0] = new UIText{ UIText("SUN SPOT", {0.f, 0.3f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[1] = new UIText{ UIText("PEH ZONG LIN ADRIAN", {0.f, 0.1f}, {textSize.x, textSize.y}, White) };
	creditInfo[2] = new UIText{ UIText("TRISTAN THAM RUI HONG", {0.f, 0.f}, {textSize.x, textSize.y}, White) };
	creditInfo[3] = new UIText{ UIText("XIAO JUN YU", {0.f, -0.1f}, {textSize.x, textSize.y}, White) };

	// Instructors
	// Set 1
	creditInfo[4] = new UIText{ UIText("INSTRUCTORS", {0.f, 0.25f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[5] = new UIText{ UIText("CHENG DING XIANG", {0.f, 0.05f}, {textSize.x, textSize.y}, White) };
	creditInfo[6] = new UIText{ UIText("GERALD WONG HAN FENG", {0.f, -0.05f}, {textSize.x, textSize.y}, White) };

	// Created at DigiPen
	// Set 2
	creditInfo[7] = new UIText{ UIText("Created at DigiPen Institute of Technology Singapore", {0.f, 0.f}, {titleSize.x, titleSize.y}, White) };


	// Executives
	// Set 3
	creditInfo[8] = new UIText{ UIText("PRESIDENT, FOUNDER, AND CHIEF EXECUTIVE OFFICER", {0.f, 0.25f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[9] = new UIText{ UIText("CLAUDE COMAIR", {0.f, 0.1f}, {textSize.x, textSize.y}, White) };

	// Set 4
	creditInfo[10] = new UIText{ UIText("CHIEF OPERATING OFFICER, INTERNATIONAL", {0.f, 0.45f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[11] = new UIText{ UIText("JASON CHU", {0.f, 0.3f}, {textSize.x, textSize.y}, White) };

	creditInfo[12] = new UIText{ UIText("CHIEF OPERATING OFFICER, REDMOND CAMPUS", {0.f, 0.05f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[13] = new UIText{ UIText("CHRISTOPHER COMAIR", {0.f, -0.1f}, {textSize.x, textSize.y}, White) };

	creditInfo[14] = new UIText{ UIText("CHIEF FINANCIAL OFFICER", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[15] = new UIText{ UIText("MICHAEL GATS", {0.f, -0.5f}, {textSize.x, textSize.y}, White) };

	// Set 5
	creditInfo[16] = new UIText{ UIText("CO - FOUNDER AND SENIOR EXECUTIVE VICE PRESIDENT", {0.f, 0.45f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[17] = new UIText{ UIText("MICHELE COMAIR", {0.f, 0.3f}, {textSize.x, textSize.y}, White) };

	creditInfo[18] = new UIText{ UIText("SENIOR VICE PRESIDENT", {0.f, 0.05f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[19] = new UIText{ UIText("RAYMOND YAN", {0.f, -0.1f}, {textSize.x, textSize.y}, White) };

	creditInfo[20] = new UIText{ UIText("CHIEF TECHNOLOGY OFFICER, INTERNATIONAL", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[21] = new UIText{ UIText("SAMIR ABOU SAMRA", {0.f, -0.5f}, {textSize.x, textSize.y}, White) };

	// Set 6
	creditInfo[22] = new UIText{ UIText("PROVOST AND ACTING DEPARTMENT CHAIR OF COMPUTER SCIENCE, SINGAPORE CAMPUS", {0.f, 0.3f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[23] = new UIText{ UIText("PRASANNA GHALI", {0.f, 0.15f}, {textSize.x, textSize.y}, White) };

	creditInfo[24] = new UIText{ UIText("SENIOR ADVISOR", {0.f, -0.1f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[25] = new UIText{ UIText("JOHN BAUER", {0.f, -0.25f}, {textSize.x, textSize.y}, White) };

	// Set 7
	creditInfo[26] = new UIText{ UIText("DEAN OF FACULTY, REDMOND CAMPUS", {0.f, 0.45f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[27] = new UIText{ UIText("DR. ERIK MOHRMANN", {0.f, 0.3f}, {textSize.x, textSize.y}, White) };

	creditInfo[28] = new UIText{ UIText("SENIOR VICE PRESIDENT OF FACILITIES MANAGEMENT", {0.f, 0.05f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[29] = new UIText{ UIText("MELVIN GONSALVEZ", {0.f, -0.1f}, {textSize.x, textSize.y}, White) };

	creditInfo[30] = new UIText{ UIText("EVP ADMINISTRATION AND OPERATIONS", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[31] = new UIText{ UIText("ANGELA KUGLER", {0.f, -0.5f}, {textSize.x, textSize.y}, White) };

	// Set 8
	creditInfo[32] = new UIText{ UIText("VICE PRESIDENT OF INSTITUTION ADVANCEMENT AND STRATEGIC INITIATIVES", {0.f, 0.45f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[33] = new UIText{ UIText("DR. CHARLES DUBA", {0.f, 0.3f}, {textSize.x, textSize.y}, White) };

	creditInfo[34] = new UIText{ UIText("VICE PRESIDENT OF SOFTWARE PRODUCTION", {0.f, 0.05f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[35] = new UIText{ UIText("BEN ELLINGER", {0.f, -0.1f}, {textSize.x, textSize.y}, White) };

	creditInfo[36] = new UIText{ UIText("VICE PRESIDENT OF INFORMATION TECHNOLOGY AND COMPUTER SYSTEMS", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White) };
	creditInfo[37] = new UIText{ UIText("JOHNNY DEEK", {0.f, -0.5f}, {textSize.x, textSize.y}, White) };

	// Copyright
	// Set 9
	creditInfo[38] = new UIText{ UIText("All content (C) 2023 Digipen Institute of Technology Singapore. All Rights Reserved", {0.f, 0.f}, {0.8f, 0.8f}, White) };

	// Special Credits
	// Set 10
	creditInfo[39] = new UIText{ UIText("Additional Third Party Library:", {0.f, 0.1f}, {textSize.x, textSize.y}, White) };
	creditInfo[40] = new UIText{ UIText("nlohmann/json", {0.f, -0.05f}, {textSize.x, textSize.y}, White) };
}

void Credits_Update() {
	mousePos mouse{};
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);

	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		next = GS_MAINMENU;
	}

	creditTimer += e_deltaTime;
}

void Credits_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	float time = 3.0f;

	//// Set 1
	//if (creditTimer < time) {
	//	for (unsigned int i{ 0 }; i < 4; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 2
	//else if (creditTimer < 2 * time) {
	//	for (unsigned int i{ 4 }; i < 7; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 3
	//else if (creditTimer < 3 * time) {
	//	creditInfo[7]->DrawObj();
	//}
	//// Set 4
	//else if (creditTimer < 4 * time) {
	//	for (unsigned int i{ 8 }; i < 10; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 5
	//else if (creditTimer < 5 * time) {
	//	for (unsigned int i{ 10 }; i < 16; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 6
	//else if (creditTimer < 6 * time) {
	//	for (unsigned int i{ 16 }; i < 22; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 7
	//else if (creditTimer < 7 * time) {
	//	for (unsigned int i{ 22 }; i < 26; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 8
	//else if (creditTimer < 8 * time) {
	//	for (unsigned int i{ 26 }; i < 32; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 9
	//else if (creditTimer < 9 * time) {
	//	for (unsigned int i{ 32 }; i < 38; ++i)
	//		creditInfo[i]->DrawObj();
	//}
	//// Set 10
	//else if (creditTimer < 10 * time) {
	//	creditInfo[38]->DrawObj();
	//}
	//else {
	//	next = GS_MAINMENU;
	//}

	int set = static_cast<int>(creditTimer / time);
	switch (set)
	{
	case 0:
		for (unsigned int i{ 0 }; i < 4; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 1:
		for (unsigned int i{ 4 }; i < 7; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 2:
		creditInfo[7]->DrawObj();
		break;

	case 3:
		for (unsigned int i{ 8 }; i < 10; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 4:
		for (unsigned int i{ 10 }; i < 16; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 5:
		for (unsigned int i{ 16 }; i < 22; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 6:
		for (unsigned int i{ 22 }; i < 26; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 7:
		for (unsigned int i{ 26 }; i < 32; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 8:
		for (unsigned int i{ 32 }; i < 38; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 9:
		creditInfo[38]->DrawObj();
		break;

	case 10:
		for (unsigned int i{ 39 }; i < 41; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 11:
		next = GS_MAINMENU;
	}
}

void Credits_Free() {
	for (size_t i{}; i < sizeof creditInfo / sizeof creditInfo[0]; ++i)
		delete creditInfo[i];
}

void Credits_Unload() {}