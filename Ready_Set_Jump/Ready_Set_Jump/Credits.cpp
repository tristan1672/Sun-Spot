/*****************************************************************
  *  \file Credits.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  Credits component.
  *  - Credits_Load
  *		Nil (Requred for GSM to function correctly)
  * 
  *  - Credits_Initialize
  *		Resets cam position to center
  *		Initalize text,position,size,color
  * 
  *  - Credits_Update
  *		Increments timer used for animation
  * 
  *  - Credits_Draw
  *		Draws text
  * 
  *  - Credits_Free
  *		Nil (Requred for GSM to function correctly)
  * 
  *  - Credits_Unload
  *		Unloads array
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

// Includes
#include "Credits.hpp"

// Global Static Variables
UIText* creditInfo[44];
static float creditTimer;
AEAudio backgroud;
AEAudioGroup backgroundSoundGroup;
/*****************************************************************
 * \brief
 *		This function loads necessary data(resource and asset) and initialize it
 *		It is called once at the start of the state 
 ****************************************************************/
void Credits_Load() {
	backgroud = AEAudioLoadMusic("Assets/Sound/MenuBackground.wav");
	backgroundSoundGroup = AEAudioCreateGroup();
}

/*****************************************************************
 * \brief
 *		This function initialize game object instances
 *		It is called once at the start of the state
 ****************************************************************/
void Credits_Initialize() {
	AEGfxSetCamPosition(0.f, 0.f);

	AEAudioPlay(backgroud, backgroundSoundGroup, 1,1,1);

	creditTimer = 0.f;

	AEVec2 titleSize{ 0.65f, 0.65f };
	AEVec2 textSize{ 0.5f, 0.5f };

	// Team
	// Set 0
	creditInfo[0] = new UIText{ UIText("SUN SPOT", {0.f, 0.15f}, {titleSize.x + 0.25f, titleSize.y + 0.25f}, White, false, White, e_creditFontID) };
	creditInfo[1] = new UIText{ UIText("PEH ZONG LIN ADRIAN", {0.f, 0.f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };
	creditInfo[2] = new UIText{ UIText("TRISTAN THAM RUI HONG", {0.f, -0.1f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };
	creditInfo[3] = new UIText{ UIText("XIAO JUN YU", {0.f, -0.2f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Instructors
	// Set 1
	creditInfo[4] = new UIText{ UIText("INSTRUCTORS", {0.f, 0.15f}, {titleSize.x + 0.25f, titleSize.y + 0.25f}, White, false, White, e_creditFontID) };
	creditInfo[5] = new UIText{ UIText("CHENG DING XIANG", {0.f, 0.f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };
	creditInfo[6] = new UIText{ UIText("GERALD WONG HAN FENG", {0.f, -0.1f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Created at DigiPen
	// Set 2
	creditInfo[7] = new UIText{ UIText("Created at DigiPen Institute of Technology Singapore", {0.f, 0.f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Executives
	// Set 3
	creditInfo[8] = new UIText{ UIText("PRESIDENT, FOUNDER, AND CHIEF EXECUTIVE OFFICER", {0.f, 0.075f}, {titleSize.x - 0.05f, titleSize.y - 0.05f}, White, false, White, e_creditFontID) };
	creditInfo[9] = new UIText{ UIText("CLAUDE COMAIR", {0.f, -0.075f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Set 4
	creditInfo[10] = new UIText{ UIText("CHIEF OPERATING OFFICER, INTERNATIONAL", {0.f, 0.4f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[11] = new UIText{ UIText("JASON CHU", {0.f, 0.3f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[12] = new UIText{ UIText("CHIEF OPERATING OFFICER, REDMOND CAMPUS", {0.f, 0.025f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[13] = new UIText{ UIText("CHRISTOPHER COMAIR", {0.f, -0.075f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[14] = new UIText{ UIText("CHIEF FINANCIAL OFFICER", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[15] = new UIText{ UIText("MICHAEL GATS", {0.f, -0.45f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Set 5
	creditInfo[16] = new UIText{ UIText("CO - FOUNDER AND SENIOR EXECUTIVE VICE PRESIDENT", {0.f, 0.4f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[17] = new UIText{ UIText("MICHELE COMAIR", {0.f, 0.3f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[18] = new UIText{ UIText("SENIOR VICE PRESIDENT", {0.f, 0.025f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[19] = new UIText{ UIText("RAYMOND YAN", {0.f, -0.075f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[20] = new UIText{ UIText("CHIEF TECHNOLOGY OFFICER, INTERNATIONAL", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[21] = new UIText{ UIText("SAMIR ABOU SAMRA", {0.f, -0.45f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Set 6
	creditInfo[22] = new UIText{ UIText("PROVOST AND ACTING DEPARTMENT CHAIR OF COMPUTER SCIENCE,", {0.f, 0.35f}, {titleSize.x - 0.05f, titleSize.y - 0.05f}, White, false, White, e_creditFontID) };
	creditInfo[23] = new UIText{ UIText("SINGAPORE CAMPUS", {0.f, 0.25f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[24] = new UIText{ UIText("PRASANNA GHALI", {0.f, 0.15f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[25] = new UIText{ UIText("SENIOR ADVISOR", {0.f, -0.15f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[26] = new UIText{ UIText("JOHN BAUER", {0.f, -0.25f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Set 7
	creditInfo[27] = new UIText{ UIText("DEAN OF FACULTY, REDMOND CAMPUS", {0.f, 0.4f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[28] = new UIText{ UIText("DR. ERIK MOHRMANN", {0.f, 0.3f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[29] = new UIText{ UIText("SENIOR VICE PRESIDENT OF FACILITIES MANAGEMENT", {0.f, 0.025f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[30] = new UIText{ UIText("MELVIN GONSALVEZ", {0.f, -0.075f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[31] = new UIText{ UIText("EVP ADMINISTRATION AND OPERATIONS", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[32] = new UIText{ UIText("ANGELA KUGLER", {0.f, -0.45f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Set 8
	creditInfo[33] = new UIText{ UIText("VICE PRESIDENT", {0.f, 0.5f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[34] = new UIText{ UIText("OF INSTITUTION ADVANCEMENT AND STRATEGIC INITIATIVES", {0.f, 0.4f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[35] = new UIText{ UIText("DR. CHARLES DUBA", {0.f, 0.3f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[36] = new UIText{ UIText("VICE PRESIDENT OF SOFTWARE PRODUCTION", {0.f, 0.025f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[37] = new UIText{ UIText("BEN ELLINGER", {0.f, -0.075f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	creditInfo[38] = new UIText{ UIText("VICE PRESIDENT", {0.f, -0.35f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[39] = new UIText{ UIText("OF INFORMATION TECHNOLOGY AND COMPUTER SYSTEMS", {0.f, -0.45f}, {titleSize.x, titleSize.y}, White, false, White, e_creditFontID) };
	creditInfo[40] = new UIText{ UIText("JOHNNY DEEK", {0.f, -0.55f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Copyright
	// Set 9
	creditInfo[41] = new UIText{ UIText("All content (C) 2023 Digipen Institute of Technology Singapore. All Rights Reserved", {0.f, 0.f}, {0.8f, 0.8f}, White, false, White, e_creditFontID) };

	// Special Credits
	// Set 10
	creditInfo[42] = new UIText{ UIText("Additional Third Party Library:", {0.f, 0.075f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };
	creditInfo[43] = new UIText{ UIText("nlohmann/json", {0.f, -0.025f}, {textSize.x, textSize.y}, White, false, White, e_creditFontID) };

	// Centering Text
	for (unsigned int i{}; i < 44; ++i) {
		AEVec2 size{};
		AEGfxGetPrintSize(e_creditFontID, creditInfo[i]->GetText(), creditInfo[i]->GetScale().x, size.x, size.y);
		creditInfo[i]->SetPosition({ -0.5f * size.x + creditInfo[i]->GetPosition().x, creditInfo[i]->GetPosition().y });
	}
}

/*****************************************************************
 * \brief
 *		This function updates the state data
 *		It is called whenever there is a need to update the state's data
****************************************************************/
void Credits_Update() {
	mousePos mouse{};
	AEInputGetCursorPosition(&mouse.ClickX, &mouse.ClickY);

	if (AEInputCheckTriggered(AEVK_LBUTTON)) {
		e_next_state = GS_MAINMENU;
	}

	creditTimer += e_deltaTime;
}

/*****************************************************************
 * \brief
 *		This function sends data that needs to be drawn to the graphic engine
 *		It is called after update to show animation/movement
****************************************************************/
void Credits_Draw() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	float time = 3.0f;
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
		for (unsigned int i{ 22 }; i < 27; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 7:
		for (unsigned int i{ 27 }; i < 33; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 8:
		for (unsigned int i{ 33 }; i < 41; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 9:
		creditInfo[41]->DrawObj();
		break;

	case 10:
		for (unsigned int i{ 42 }; i < 44; ++i)
			creditInfo[i]->DrawObj();
		break;

	case 11:
		e_next_state = GS_MAINMENU;
	}
}

/*****************************************************************
 * \brief
 *		This function frees objects instances
 *		It is called after to prepare the state to be unloaded or initialized again
****************************************************************/
void Credits_Free() {}

/*****************************************************************
 * \brief
 *		This function dumps all loaded during Level1_Load()
 *		It is called when the state should be terminated
****************************************************************/
void Credits_Unload() {
	for (size_t i{}; i < sizeof creditInfo / sizeof creditInfo[0]; ++i)
		delete creditInfo[i];
}