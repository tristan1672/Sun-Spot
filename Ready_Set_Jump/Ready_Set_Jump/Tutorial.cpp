/**
  *  \file Tutorial.cpp
  *  \author Xiao Jun Yu
  *  \par DP Email: junyu.xiao\\digipen.edu
  *  \par Course: csd1451
  *
  *  \brief
  *  Sets tutorial objects
  * 
  * -SetTutorialObj(GameObject& Object,Vector2D pos, Vector2D size, AEGfxTexture*& texture,std::string imagePath)
  *		a helper function to set the tutorial guides easily
  * -MakeTutorialText()
  *		sets each tutorial guides
  * -RenderTutorialText()
  *		draws all tutorial guides
  * -FreeTutorialtext()
  *		frees all memeories allocated
  * 
  * All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
*/
#include "Tutorial.hpp"
#include "AEEngine.h"
#include "UI.hpp"
namespace Tutorial {
	GameObject TutorialTextObj[10]{};
	AEGfxTexture* TurorialText[10]{nullptr};

	void SetTutorialObj(GameObject& Object,Vector2D pos, Vector2D size, AEGfxTexture*& texture,std::string imagePath) {
		// function to set the objects and their textures
		texture = AEGfxTextureLoad(imagePath.c_str());
		Object = GameObject(pos, size, { 1.f,1.f,1.f,1.f }, 0.f, AE_GFX_RM_TEXTURE);
		Object.SetTexture(texture);
	}

	void MakeTutorialText() {
		//sets inidvidual tutorial text to their location and set their texture to each obj
		SetTutorialObj(TutorialTextObj[0], {-450.f,115.f}, {300.f,260.f},     TurorialText[0], "Assets/Images/TutorialText/ControlIntro.png");
		SetTutorialObj(TutorialTextObj[1], { 400.f,0.f }, { 360.f,120.f },    TurorialText[1], "Assets/Images/TutorialText/IceIntro.png");
		SetTutorialObj(TutorialTextObj[2], { 987.f,320.f }, { 360.f,200.f },  TurorialText[2], "Assets/Images/TutorialText/CheckpointIntro.png");
		SetTutorialObj(TutorialTextObj[3], { 1500.f,0.f }, { 360.f,200.f },   TurorialText[3], "Assets/Images/TutorialText/JumpGapText.png");
		SetTutorialObj(TutorialTextObj[4], { 4000.f,220.f }, { 360.f,200.f }, TurorialText[4], "Assets/Images/TutorialText/JumpDown.png");
		SetTutorialObj(TutorialTextObj[5], { 6100.f,-390.f }, { 360.f,200.f },TurorialText[5], "Assets/Images/TutorialText/SlimeIntro.png");
		SetTutorialObj(TutorialTextObj[6], { 7020.f,250.f }, { 360.f,200.f }, TurorialText[6], "Assets/Images/TutorialText/CollectibleIntro.png");
		SetTutorialObj(TutorialTextObj[7], { 6300.f,-75.f }, { 360.f,200.f }, TurorialText[7], "Assets/Images/TutorialText/StickyIntroPt1.png");
		SetTutorialObj(TutorialTextObj[8], { 7300.f,-75.f }, { 360.f,200.f }, TurorialText[8], "Assets/Images/TutorialText/StickyIntroPt2.png");
		SetTutorialObj(TutorialTextObj[9], { 9625.f,250.f }, { 360.f,200.f }, TurorialText[9], "Assets/Images/TutorialText/ExitIntro.png");

	}
	void RenderTutorialText() {
		// draws all the tutorial text obj
		for (size_t i{}; i < sizeof(TutorialTextObj) / sizeof (TutorialTextObj[0]); ++i)TutorialTextObj[i].DrawObj();
	}

	void FreeTutorialtext() {
		// frees the textures loaded
		for (size_t i{}; i < sizeof(TutorialTextObj) / sizeof(TutorialTextObj[0]); ++i) {
			if (TurorialText[i]) {
				AEGfxTextureUnload(TurorialText[i]);
			}
		}
	}
}