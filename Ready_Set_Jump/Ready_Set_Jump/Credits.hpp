/*****************************************************************
  *  \file Credits.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  Credits component.
  *  - Credits_Load
  *		Nil (Requred for GSM to function correctly)
  *
  *  - Credits_Initialize
  *		Resets cam position to center
  *		Initalize text,position,size,color
  *
  *  - Credits_Update
  *		Increments timer used for animation
  *
  *  - Credits_Draw
  *		Draws text
  *
  *  - Credits_Free
  *		Nil (Requred for GSM to function correctly)
  *
  *  - Credits_Unload
  *		Unloads array
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/

#pragma once
#include "UI.hpp"
#include "Utilities.hpp"
#include "GameStateManager.hpp"

#ifndef CREDITS_HPP
#define CREDITS_HPP

void Credits_Load();

void Credits_Initialize();

void Credits_Update();

void Credits_Draw();

void Credits_Free();

void Credits_Unload();

#endif // CREDITS_HPP