#pragma once
#include "GameObjClasses.hpp"
#include "Utilities.hpp"

GameObject CreateParticle(float posX, float posY, float velX, float velY, float scale, float lifetime = 10000, ColourValue color = { 1.0f, 1.0f, 1.0f, 1.0f }, AEGfxRenderMode mode = AE_GFX_RM_COLOR);

void UpdateParticle(GameObject* list);

void DrawParticle(GameObject* list);

void UnloadPArticle(GameObject* list);