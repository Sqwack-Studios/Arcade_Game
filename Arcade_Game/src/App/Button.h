//=================================================================================
// Namespace		: Arcade_Game
// Name				: Button.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 29/09/2022 21:18:58
//=================================================================================

#ifndef _Arcade_Game_Button_H_
#define _Arcade_Game_Button_H_

#pragma once
#include <string>
#include "AARectangle.h"
#include <functional>
#include "Color.h"
#include "BitmapFont.h"

class Screen;



class Button
{
public:
	using ButtonAction = std::function<void(void)>;

	Button(const BitmapFont& bitmapFont, const Color& textcolor, const Color& highlightColor = Color::White());
	void Init(Vec2D topLeft, unsigned int width, unsigned int height);

	void Draw(Screen& theScreen);
	void ExecuteAction();

	inline void SetButtonText(const std::string& text) { mTitle = text; }
	inline const std::string& GetButtonText() const { return mTitle; }
	inline void SetHighlighted(bool highlighted) { mHighlighted = highlighted; }
	inline bool IsHighlighted() const { return mHighlighted; }
	inline void SetButtonAction(ButtonAction action) { mAction = action; }

private:
	const BitmapFont& mBitmapFont;
	std::string mTitle;
	AARectangle mBBox;

	bool mHighlighted;
	ButtonAction mAction;
	Color mHighlightcolor;
	Color mTextColor;

protected:



	
};
#endif // !_Arcade_Game_Button_H_

