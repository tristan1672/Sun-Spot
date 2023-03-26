#include "Tutorial.hpp"
#include "AEEngine.h"
#include "UI.hpp"
namespace Tutorial {
	GameObject TutorialTextObj[10]{};
	AEGfxTexture* TurorialText[10]{nullptr};

	void SetTutorialObj(GameObject& Object,Vector2D pos, Vector2D size, AEGfxTexture*& texture,std::string imagePath) {
		texture = AEGfxTextureLoad(imagePath.c_str());
		Object = GameObject(pos, size, { 1.f,1.f,1.f,1.f }, 0.f, AE_GFX_RM_TEXTURE);
		Object.SetTexture(texture);
	}

	void MakeTutorialText() {
		SetTutorialObj(TutorialTextObj[0], {-450.f,115.f}, {300.f,260.f},     TurorialText[0], "Assets/Images/TutorialText/ControlIntro.png");
		SetTutorialObj(TutorialTextObj[1], { 400.f,0.f }, { 360.f,120.f },    TurorialText[1], "Assets/Images/TutorialText/IceIntro.png");
		SetTutorialObj(TutorialTextObj[2], { 785.f,300.f }, { 360.f,200.f },  TurorialText[2], "Assets/Images/TutorialText/CheckpointIntro.png");
		SetTutorialObj(TutorialTextObj[3], { 1500.f,0.f }, { 360.f,200.f },   TurorialText[3], "Assets/Images/TutorialText/JumpGapText.png");
		SetTutorialObj(TutorialTextObj[4], { 3200.f,150.f }, { 360.f,200.f }, TurorialText[4], "Assets/Images/TutorialText/JumpDown.png");
		SetTutorialObj(TutorialTextObj[5], { 4900.f,-300.f }, { 360.f,200.f },TurorialText[5], "Assets/Images/TutorialText/SlimeIntro.png");
		SetTutorialObj(TutorialTextObj[6], { 5695.f,200.f }, { 360.f,200.f }, TurorialText[6], "Assets/Images/TutorialText/CollectibleIntro.png");
		SetTutorialObj(TutorialTextObj[7], { 5500.f,-75.f }, { 360.f,200.f }, TurorialText[7], "Assets/Images/TutorialText/StickyIntroPt1.png");
		SetTutorialObj(TutorialTextObj[8], { 6300.f,-75.f }, { 360.f,200.f }, TurorialText[8], "Assets/Images/TutorialText/StickyIntroPt2.png");
		SetTutorialObj(TutorialTextObj[9], { 7645.f,220.f }, { 360.f,200.f }, TurorialText[9], "Assets/Images/TutorialText/ExitIntro.png");

	}
	void RenderTutorialText() {
		for (size_t i{}; i < sizeof(TutorialTextObj) / sizeof (TutorialTextObj[0]); ++i)TutorialTextObj[i].DrawObj();
	}

	void FreeTutorialtext() {
		for (size_t i{}; i < sizeof(TutorialTextObj) / sizeof(TutorialTextObj[0]); ++i) {
			if (TurorialText[i]) {
				AEGfxTextureUnload(TurorialText[i]);
			}
		}
	}
}