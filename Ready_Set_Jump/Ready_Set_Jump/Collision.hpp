/*****************************************************************
  *  \file Collision.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  Collision component.
  *  - LevelCollision (Class member function)
  *		 Checks for player collision against level.
  *
  *  - SnapToGrid (Class member function)
  *		 Snaps to grid
  *
  *  - ObjectCollision
  *		 Checks for player collision against objects that is not a platform
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/

#pragma once
#include "PreCompiledHeader.hpp"
#include "GameObjClasses.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"
#include "Level.hpp"

void ObjectCollision();