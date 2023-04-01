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

#include "Particles.hpp"

/*****************************************************************
 * @brief 
 *		Creates a particle GameObject with the given properties.
 *
 * @param posX 
 *		The x-coordinate of the particle's starting position.
 * 
 * @param posY 
 *		The y-coordinate of the particle's starting position.
 * 
 * @param velX 
 *		The x-component of the particle's initial velocity.
 * 
 * @param velY 
 *		The y-component of the particle's initial velocity.
 * 
 * @param scale 
 *		The scale of the particle.
 * 
 * @param lifetime 
 *		The lifetime of the particle in seconds.
 * 
 * @param color 
 *		The color of the particle.
 * 
 * @param mode 
 *		The render mode of the particle.
 *
 * @return 
 *		The newly created particle GameObject.
 ****************************************************************/
GameObject CreateParticle(float posX, float posY, float velX, float velY, float scale, float lifetime , ColourValue color , AEGfxRenderMode mode) {
	// Repurposed class
	return GameObject({ posX, posY }, { scale, scale }, { color.red, color.green, color.blue, color.alpha },
		lifetime, mode, pMesh, { velX , velY });
}

/*****************************************************************
 * @brief 
 *		Updates the properties of all particles in the given list.
 *
 * @param list 
 *		The list of particle GameObjects to update.
 ****************************************************************/
void UpdateParticle(GameObject *list) {

	// Update particle effect for background
	for (unsigned int i{}; i < MAX_PARTICLE_NUMBER; ++i) {

		GameObject* pInst = list + i;

		// Rotation is resued as lifetime
		if (pInst->GetRotation() > 0) {
			pInst->SetPosition({ pInst->GetPosition().x + pInst->GetDirection().x, pInst->GetPosition().y + pInst->GetDirection().y });
			pInst->SetRotation(pInst->GetRotation() - 1.0f);
		}

		// If off screen, "kills" it
		if (pInst->GetPosition().x < -HALVE_WINDOW_WIDTH - 5)
			pInst->SetRotation(0.f);
	}
}

/*****************************************************************
 * @brief 
 *		Renders all particles in the given list.
 *
 * @param list 
 *		The list of particle GameObjects to render.
 ****************************************************************/
void DrawParticle(GameObject* list) {

	for (unsigned int i{}; i < MAX_PARTICLE_NUMBER; ++i) {

		GameObject* pInst = list + i;

		// Rotation is resued as lifetime
		if (pInst->GetRotation() > 0) {
			pInst->DrawObj();
		}
	}
}

/*****************************************************************
 * @brief 
 *		Unloads all resources associated with the given list of particles.
 *
 * @param list 
 *		The list of particle GameObjects to unload.
 ****************************************************************/
void UnloadPArticle(GameObject* list) {
	delete[] list;
}