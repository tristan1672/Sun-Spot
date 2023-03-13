#pragma once
#include "Timer.hpp"
#include <iostream>
#include "GameObjClasses.hpp"
#include <cstring>
#include <string>

#ifndef UI_HPP
#define UI_HPP

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

class UIText :public GameObject {
	char* text = nullptr;
	size_t charcount{};
	GameObject TextBox{};

public:
	bool TextBoxActive;
	bool Active = true;
	UIText(std::string Text = "No text found check for instantiation", Vector2D Position = {0.f,0.f}, Vector2D Scale = {10.f,10.f},
		ColourValue Colour = { 1.f,1.f,1.f,1.f },bool ActiveTextBox = false, ColourValue TextBoxColour = {0.f,0.f,0.f,1.f});

	UIText(UIText const& toCopy);
	UIText& operator=(UIText const& toCopy);
	~UIText();
	size_t GetCharCount();
	void SetCharCount(size_t size);
	void DrawObj()override;
	bool MouseCollision(mousePos mousePos);
};

#endif // UI_HPP