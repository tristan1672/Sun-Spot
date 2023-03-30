#include "Particles.hpp"

// Repurpose GameObject to make things clearer when trying to create particle
GameObject CreateParticle(float posX, float posY, float velX, float velY, float scale, float lifetime , ColourValue color , AEGfxRenderMode mode) {

	return GameObject({ posX, posY }, { scale, scale }, { color.red, color.green, color.blue, color.alpha },
		lifetime, mode, pMesh, { velX , velY });
}