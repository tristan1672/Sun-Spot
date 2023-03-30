#include "Particles.hpp"

GameObject CreateParticle(float posX) {

	AEVec2 particalPosition = { static_cast<float>(posX + WINDOW_WIDTH), static_cast<float>(rand() % static_cast<int>(e_binaryMapHeight * GRID_HEIGHT_SIZE) - static_cast<float>(e_binaryMapHeight * GRID_HEIGHT_SIZE) + HALVE_WINDOW_HEIGHT) };

	int randScale = rand() % 8 + 2;
	AEVec2 particalScale = { static_cast<float>(randScale), static_cast<float>(randScale) };

	int randLifeTime = rand() % 70 + 10000;
	AEVec2 particleVelocity = { -static_cast<float>(rand() % 5 + 2) , 0.0f };

	return GameObject({ particalPosition.x, particalPosition.y }, { particalScale.x, particalScale.y }, { 1.f, 1.f, 1.f, 1.f },
		static_cast<float>(randLifeTime), AE_GFX_RM_COLOR, pMesh, { particleVelocity.x , particleVelocity.y });
}