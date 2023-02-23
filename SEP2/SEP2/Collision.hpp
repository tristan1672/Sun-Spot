#pragma once

#include "PreCompiledHeader.hpp"
#include "GameObjClasses.hpp"
#include "Ultilities.hpp"
#include "Level1.hpp"

// Checks collision and snap player into position if required
void CollisionCheck();

// Checks collision against collectible
void CollectableCheck();