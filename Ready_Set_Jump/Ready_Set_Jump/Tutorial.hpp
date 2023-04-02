/*****************************************************************
  *  \file Tutorial.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)
  *
  *  \brief
  *  Sets tutorial objects
  *
  * -SetTutorialObj(GameObject& Object,Vector2D pos, Vector2D size, AEGfxTexture*& texture,std::string imagePath)
  *		a helper function to set the tutorial guides easily
  * -MakeTutorialText()
  *		sets each tutorial guides
  * -RenderTutorialText()
  *		draws all tutorial guides
  * -FreeTutorialtext()
  *		frees all memeories allocated
  *
  * All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

namespace Tutorial {
	void MakeTutorialText();
	void RenderTutorialText();
	void FreeTutorialtext();
}

#endif // TUTORIAL_HPP