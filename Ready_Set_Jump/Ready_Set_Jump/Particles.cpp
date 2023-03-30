#include "Particles.hpp"

// Repurpose GameObject to make things clearer when trying to create particle
GameObject CreateParticle(float posX, float posY, float velX, float velY, float scale, float lifetime , ColourValue color , AEGfxRenderMode mode) {

	return GameObject({ posX, posY }, { scale, scale }, { color.red, color.green, color.blue, color.alpha },
		lifetime, mode, pMesh, { velX , velY });
}

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

void DrawParticle(GameObject* list) {

	for (unsigned int i{}; i < MAX_PARTICLE_NUMBER; ++i) {

		GameObject* pInst = list + i;

		// Rotation is resued as lifetime
		if (pInst->GetRotation() > 0) {
			pInst->DrawObj();
		}

	}
}