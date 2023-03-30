#pragma once
#include "Timer.hpp"
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

public:
	bool TextBoxActive;
	bool Active = true;
	UIText(std::string Text = "No text found check for instantiation", Vector2D Position = {0.f,0.f}, Vector2D Scale = {10.f,10.f},
		ColourValue Colour = { 1.f,1.f,1.f,1.f },bool ActiveTextBox = false, ColourValue TextBoxColour = {1.f,1.f,1.f,1.f});

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