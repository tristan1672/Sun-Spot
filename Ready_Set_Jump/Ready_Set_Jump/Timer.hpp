/*****************************************************************
  *  \file Timer.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  System component.
  *  - GetTime
  *		Get and sets delta time(Called in main)
  *
  *  - LevelTime
  *		Updates level time
  * 
  *  - DisplayTime
  *		Display time on screen
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "Utilities.hpp"
#include <string>

#ifndef TIMER_HPP
#define TIMER_HPP

void GetTime();

void LevelTime();

void DisplayTime(float pos_x, float pos_y);

#endif // TIMER_HPP