/*
  *  \file UI.cpp
  *  \author      : Tristan Tham
  *  \par DP Email: t.tham@digipen.edu
  *  \par Course  : csd1451
  *
  *  \brief
  *	 Contains functions for creating UI elements:
  *   IsAreaClicked			-Function to check for button collision with player clicks
  * 
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
  */

#include "UI.hpp"
#include <string>

// Button collisions

UIText::UIText(std::string Text, Vector2D Position, Vector2D Scale,
	ColourValue Colour, bool ActiveTextBox, ColourValue TextBoxColour , s8 Font) {// constructor for UIText class
	position = Position; scale = Scale; colour = Colour; TextBoxActive = ActiveTextBox;
	charcount = Text.size() + 1;
	text = new char[GetCharCount()];// sets a new char array
	snprintf(text, charcount, Text.c_str());// puts string into text member data
	float w{};
	float h{};
	font = Font;
	AEGfxGetPrintSize(font, text, 1.f, w, h);
	TextBox = GameObject({ (position.x + w/2.f)* 800.f,(position.y + h/2.f)*450.f }, { w * 800.f,h * 700.f }, TextBoxColour);// makes textbox
}
UIText::UIText(UIText const& toCopy) {// copy constructor
	position = toCopy.position; scale = toCopy.scale; colour = toCopy.colour; TextBoxActive = toCopy.TextBoxActive;
	charcount = toCopy.charcount;
	text = new char[charcount];
	snprintf(text, charcount, toCopy.text);
	TextBox = toCopy.TextBox;

}
UIText& UIText::operator=(UIText const& toCopy) {// copy assignment
	position = toCopy.position; scale = toCopy.scale; colour = toCopy.colour; TextBoxActive = toCopy.TextBoxActive;
	charcount = toCopy.charcount;
	delete[] text;
	text = new char[charcount];
	snprintf(text, charcount, toCopy.text);
	TextBox = toCopy.TextBox;
	return *this;
}
UIText::~UIText() {
	delete[] text;
}

void UIText::DrawObj() {// draws the ui text obj
	if (TextBoxActive) {//if textbox is active, draw text box
		TextBox.DrawObj();
	}
	if (Active) {//if text is active, draw text
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(font, text, position.x, position.y, scale.x, colour.red, colour.green, colour.blue);
	}
}

size_t UIText::GetCharCount() {
	return charcount;
}
void UIText::SetCharCount(size_t size) {
	charcount = size;
}

bool UIText::MouseCollision(mousePos mousePos) {
	if (!TextBoxActive) { return false;}
	//x coordinate of max/min rectangle
	float xmax = TextBox.position.x + (TextBox.GetScale().x / 2);
	float xmin = TextBox.position.x - (TextBox.GetScale().x / 2);

	//y coordinate of max/min rectangle
	float ymax = TextBox.position.y + (TextBox.GetScale().y / 2);
	float ymin = TextBox.position.y - (TextBox.GetScale().y / 2);

	Vector2D mouseClickQuadPos = { static_cast<float>(mousePos.ClickX) - HALVE_WINDOW_WIDTH , -(static_cast<float>(mousePos.ClickY) - HALVE_WINDOW_HEIGHT) };
	//test if click x and click y is within the max and min coordinates of the rectangle
	if ((mouseClickQuadPos.x <= xmax && mouseClickQuadPos.x >= xmin) && (mouseClickQuadPos.y <= ymax && mouseClickQuadPos.y >= ymin)) {
		return true;
	}
	else {
		return false;
	}
}
void UIText::SetTextBoxAlpha(f32 newAlpha) {
	ColourValue tempColour = TextBox.GetColour();
	tempColour.alpha = newAlpha;
	TextBox.SetColour(tempColour);
}
f32 UIText::GetTextBoxAlpha() {
	return TextBox.GetColour().alpha;
}
void UIText::TextBoxFadeIn() {// text box fades in
	if (TextBox.GetColour().alpha <= 1.f) {
		SetTextBoxAlpha(TextBox.GetColour().alpha + 2.f*e_deltaTime);
	}
}
void UIText::TextBoxFadeOut() {
	if (TextBox.GetColour().alpha > 0.f) {// text box fades out
		SetTextBoxAlpha(TextBox.GetColour().alpha - 1.5f * e_deltaTime);
	}
}

char* UIText::GetText() {
	return text;
}