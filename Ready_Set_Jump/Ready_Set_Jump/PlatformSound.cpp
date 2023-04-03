/*****************************************************************
  *  \file PlatformSound.cpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  Platform sound component.
  *  - PlatformSoundLoad
  *		Load platform sounds
  *
  *  - PlatformSoundPlay
  *		Plays platform sound according to its type
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#include "PlatformSound.hpp"

AEAudio iceAudio;
AEAudio stickyAudio;
AEAudio slimeAudio;
AEAudio checkpointAudio;
AEAudio collectibleAudio;
AEAudioGroup e_platformAudioGroup;


/*****************************************************************
 * \brief
 *		Loads different platform sounds
 ****************************************************************/
void PlatformSoundLoad() {
	e_platformAudioGroup = AEAudioCreateGroup();
	iceAudio = AEAudioLoadMusic("Assets/Sound/Ice_Sound.mp3");
	stickyAudio = AEAudioLoadMusic("Assets/Sound/Sticky_Sound.mp3");
	slimeAudio = AEAudioLoadMusic("Assets/Sound/Slime_Sound.mp3");
	checkpointAudio = AEAudioLoadMusic("Assets/Sound/Checkpoint_Sound.mp3");
	collectibleAudio = AEAudioLoadMusic("Assets/Sound/Collectible_Sound.mp3");
}

/*****************************************************************
 * \brief
 *		Plays platform sound according to its type
 * 
 * \param Type
 *		Type of platform object
 ****************************************************************/
void PlatformSoundPlay(int Type) {
	switch (Type) {
	case ICE_BLOCK:
		AEAudioPlay(iceAudio, e_platformAudioGroup, 0.2f, 1, 0);
		break;

	case STICKY_BLOCK:
		AEAudioPlay(stickyAudio, e_platformAudioGroup, 0.1f, 1, 0);
		break;

	case SLIME_BLOCK:
		AEAudioPlay(slimeAudio, e_platformAudioGroup, 0.1f, 1, 0);
		break;

	case CHECKPOINT:
		AEAudioPlay(checkpointAudio, e_platformAudioGroup, 0.1f, 1, 0);
		break;

	case COLLECTIBLES:
		AEAudioPlay(collectibleAudio, e_platformAudioGroup, 0.1f, 1, 0);
		break;
	}
}


/*****************************************************************
 * \brief
 *		Checks which type of collision occur and calls the corresponding audio
 ****************************************************************/
void DynamicObj::CollisionSound() {

	if (collisionFlag & COLLISION_BOTTOM) {// checks if the obj collides on the bottom
		// Checking when block is the player on 
		if (position.x < (platform[static_cast<int>(btmY)][static_cast<int>(X1)].position.x + (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetScale().x / 2.f))) {

			switch (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetPlatformType())
			{
			case ICE_BLOCK:
				PlatformSoundPlay(ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				PlatformSoundPlay(STICKY_BLOCK);
				break;

			case SLIME_BLOCK:
				PlatformSoundPlay(SLIME_BLOCK);
				break;

			default:
				break;
			}
		}
		else if (position.x > (platform[static_cast<int>(btmY)][static_cast<int>(X1)].position.x - (platform[static_cast<int>(btmY)][static_cast<int>(X1)].GetScale().x / 2.f))) {
			switch (platform[static_cast<int>(btmY)][static_cast<int>(X2)].GetPlatformType())
			{
			case ICE_BLOCK:
				PlatformSoundPlay(ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				PlatformSoundPlay(STICKY_BLOCK);
				break;

			case SLIME_BLOCK:
				PlatformSoundPlay(SLIME_BLOCK);
				break;

			default:
				break;
			}
		}
	}
	if (collisionFlag & COLLISION_RIGHT) {
		if (position.y < (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].position.y + (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetScale().y / 2.f)) ||
			position.y >(platform[static_cast<int>(Y1)][static_cast<int>(rightX)].position.y - (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetScale().y / 2.f))) {
			switch (platform[static_cast<int>(Y1)][static_cast<int>(rightX)].GetPlatformType())
			{
			case ICE_BLOCK:
				PlatformSoundPlay(ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				PlatformSoundPlay(STICKY_BLOCK);
				break;

			case SLIME_BLOCK:
				PlatformSoundPlay(SLIME_BLOCK);
				break;

			default:
				break;
			}
		}
		else if (platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType() < GOAL) {
			switch (platform[static_cast<int>(Y2)][static_cast<int>(rightX)].GetPlatformType())
			{
			case ICE_BLOCK:
				PlatformSoundPlay(ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				PlatformSoundPlay(STICKY_BLOCK);
				break;

			case SLIME_BLOCK:
				PlatformSoundPlay(SLIME_BLOCK);
				break;

			default:
				break;
			}
		}
	}
	if (collisionFlag & COLLISION_LEFT) {
		if (position.y < (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].position.y + (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetScale().y / 2.f)) ||
			position.y >(platform[static_cast<int>(Y1)][static_cast<int>(leftX)].position.y - (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetScale().y / 2.f))) {
			switch (platform[static_cast<int>(Y1)][static_cast<int>(leftX)].GetPlatformType())
			{
			case ICE_BLOCK:
				PlatformSoundPlay(ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				PlatformSoundPlay(STICKY_BLOCK);
				break;

			case SLIME_BLOCK:
				PlatformSoundPlay(SLIME_BLOCK);
				break;

			default:
				break;
			}
		}
		else if (platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType() > EMPTY_SPACE && platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType() < GOAL) {
			switch (platform[static_cast<int>(Y2)][static_cast<int>(leftX)].GetPlatformType())
			{
			case ICE_BLOCK:
				PlatformSoundPlay(ICE_BLOCK);
				break;

			case STICKY_BLOCK:
				PlatformSoundPlay(STICKY_BLOCK);
				break;

			case SLIME_BLOCK:
				PlatformSoundPlay(SLIME_BLOCK);
				break;

			default:
				break;
			}
		}
	}
}