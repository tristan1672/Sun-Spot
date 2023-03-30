#include "Particles.hpp"

GameObject CreateParticle(float posX, float posY, float velX, float velY, float scale, float lifetime) {

	return GameObject({ posX, posY }, { scale, scale }, { 1.f, 1.f, 1.f, 1.f },
		lifetime, AE_GFX_RM_COLOR, pMesh, { velX , velY });
}