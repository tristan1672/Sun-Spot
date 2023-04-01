/*****************************************************************
  *  \file Particles.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *  
  *  \brief
  *  Particles component.
  *  - CreateParticle
  *		Creates particles objects
  *
  *  - UpdateParticle
  *		Updates particle position with its velocity
  *
  *  - DrawParticle
  *		Draws particles
  *
  *  - UnloadPArticle
  *		Unloads array
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "GameObjClasses.hpp"
#include "Utilities.hpp"

GameObject CreateParticle(float posX, float posY, float velX, float velY, float scale, float lifetime = 10000, ColourValue color = { 1.0f, 1.0f, 1.0f, 1.0f }, AEGfxRenderMode mode = AE_GFX_RM_COLOR);

void UpdateParticle(GameObject* list);

void DrawParticle(GameObject* list);

void UnloadPArticle(GameObject* list);