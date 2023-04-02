/*****************************************************************
  *  \file Input.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)
  *
  *  \brief
  *  This is the input action that the player need to take to move the character in game, the main movment is to use flicking of mosue to sling shot
  *  player characters to their destinations
  *
  * -Input_Handle_HoldCheck()
  *		Checks if left mouse button is held for a certain time frame, if past that time, a guide arrow will show up
  * -Input_Handle_Jump()
  *		checks if left mouse button was released, if relased, make the player jump
  *
  *  All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

void Input_Handle_HoldCheck();
void Input_Handle_Jump();