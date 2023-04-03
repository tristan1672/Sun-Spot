/*****************************************************************
  *  \file PlatformSound.hpp
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

#pragma once
#include "Utilities.hpp"
#include "Level.hpp"
#include "GameObjClasses.hpp"
#include "Collision.hpp"

 /*****************************************************************
  * \brief
  *		Loads different platform sounds
  ****************************************************************/
void PlatformSoundLoad(void);

/*****************************************************************
 * \brief
 *		Plays platform sound according to its type
 *
 * \param Type
 *		Type of platform object
 ****************************************************************/
void PlatformSoundPlay(int Type);