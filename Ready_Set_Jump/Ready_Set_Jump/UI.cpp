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
  */

#include "UI.hpp"
#include <string>

// Button collisions
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float minX, maxX, minY, maxY;
	minX = area_center_x - static_cast<float>(0.5 * area_width);
	maxX = area_center_x + static_cast<float>(0.5 * area_width);
	minY = area_center_y - static_cast<float>(0.5 * area_height);
	maxY = area_center_y + static_cast<float>(0.5 * area_height);

	if (((click_x > minX) && (click_x < maxX)) && ((click_y > minY) && (click_y < maxY))) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

UIText::UIText(std::string Text, Vector2D Position, Vector2D Scale,
	ColourValue Colour, bool ActiveTextBox, ColourValue TextBoxColour) {
	position = Position; scale = Scale; colour = Colour; TextBoxActive = ActiveTextBox;
	charcount = Text.size() + 1;
	text = new char[GetCharCount()];
	snprintf(text, charcount, Text.c_str());
	float w{};
	float h{};
	AEGfxGetPrintSize(e_fontID, text, 1.f, w, h);
	TextBox = GameObject({ (position.x + w/2.f)* 640.f,(position.y + h/2.f)*360.f }, { w * 750.f,h * 600.f }, TextBoxColour);
}
UIText::UIText(UIText const& toCopy) {
	position = toCopy.position; scale = toCopy.scale; colour = toCopy.colour; TextBoxActive = toCopy.TextBoxActive;
	charcount = toCopy.charcount;
	text = new char[charcount];
	snprintf(text, charcount, toCopy.text);
	TextBox = toCopy.TextBox;

}
UIText& UIText::operator=(UIText const& toCopy) {
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

void UIText::DrawObj() {
	if (TextBoxActive) {
		TextBox.DrawObj();
	}
	if (Active) {
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(e_fontID, text, position.x, position.y, scale.x, colour.red, colour.green, colour.blue);
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

	Vector2D mouseClickQuadPos = { static_cast<float>(mousePos.ClickX) - WINDOW_WIDTH / 2.f , -(static_cast<float>(mousePos.ClickY) - WINDOW_HEIGHT / 2.f) };
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
void UIText::TextBoxFadeIn() {
	if (TextBox.GetColour().alpha <= 1.f) {
		SetTextBoxAlpha(TextBox.GetColour().alpha + 2.f*e_deltaTime);
	}
}
void UIText::TextBoxFadeOut() {
	if (TextBox.GetColour().alpha > 0.f) {
		SetTextBoxAlpha(TextBox.GetColour().alpha - 1.5f * e_deltaTime);
	}
}
