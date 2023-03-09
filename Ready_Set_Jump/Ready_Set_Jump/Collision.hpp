#pragma once

#include "PreCompiledHeader.hpp"
#include "GameObjClasses.hpp"
#include "Ultilities.hpp"
#include "Level1.hpp"


void ObjectiveCollision();

// ---------------------------------------------------------------------------
// Const Variables
const int	COLLISION_LEFT = 0x00000001;	//0001
const int	COLLISION_RIGHT = 0x00000002;	//0010
const int	COLLISION_TOP = 0x00000004;	//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000