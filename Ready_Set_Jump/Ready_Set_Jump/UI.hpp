/*****************************************************************
  *  \file UI.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Xiao Jun Yu (junyu.xiao)
  *
  *  \brief
  *	 Contains functions for creating UI elements:
  *   IsAreaClicked			-Function to check for button collision with player clicks
  *
  * -UIText(std::string Text, Vector2D Position, Vector2D Scale,ColourValue Colour, bool ActiveTextBox, ColourValue TextBoxColour , s8 Font)
  *		constructor for UIText Objects
  * -UIText(UIText const& toCopy)
  *		copy constructor for UIText Objects
  * -UIText::operator=(UIText const& toCopy)
  *		copy assignment operator overload to get value from another UIText Object
  * -~UIText()
  *		destructor for UIText, frees memeories allocated when constructing
  * -DrawObj()
  *		draws UIText Objects, checks if the text or the text boxes are active
  * -GetCharCount()
  *		get how many character the UI text holds
  * -SetCharCount(size_t size)
  *		set how many character the UI text holds
  * -MouseCollision(mousePos mousePos)
  *		checks if mouse is colliding with the text box
  * -GetTextBoxAlpha()
  *		gets the opacity of text box
  * -SetTextBoxAlpha(f32 newAlpha)
  *		sets the opacity of text box
  * -TextBoxFadeIn()
  *		make the text box fade in
  * -TextBoxFadeOut()
  *		make the text box fade out
  * -GetText()
  *		get the text stored in UIText
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
 ****************************************************************/

#pragma once
#include "Timer.hpp"
#include "Utilities.hpp"
#include <iostream>
#include "GameObjClasses.hpp"
#include <cstring>
#include <string>

#ifndef UI_HPP
#define UI_HPP

class UIText :public GameObject {
	char* text = nullptr;
	size_t charcount{};
	GameObject TextBox{};
	s8 font;

public:
	bool TextBoxActive;
	bool Active = true;
	UIText(std::string Text = "No text found check for instantiation", Vector2D Position = {0.f,0.f}, Vector2D Scale = {10.f,10.f},
		ColourValue Colour = { 1.f,1.f,1.f,1.f },bool ActiveTextBox = false, ColourValue TextBoxColour = {1.f,1.f,1.f,1.f}, s8 Font = e_fontID);

	UIText(UIText const& toCopy);
	UIText& operator=(UIText const& toCopy);
	~UIText();
	size_t GetCharCount();
	void SetCharCount(size_t size);
	void DrawObj()override;
	bool MouseCollision(mousePos mousePos);
	void TextBoxFadeIn();
	void TextBoxFadeOut();
	void SetTextBoxAlpha(f32 newAlpha);
	f32 GetTextBoxAlpha(); 
	char* GetText();
};

#endif // UI_HPP