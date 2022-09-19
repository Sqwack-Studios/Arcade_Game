//=================================================================================
// Namespace		: Arcade_Game
// Name				: Screen.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 15/09/2022 11:42:28
//=================================================================================

#ifndef _Arcade_Game_Screen_H_
#define _Arcade_Game_Screen_H_

#pragma once
#include <stdint.h>
#include "ScreenBuffer.h"
#include "Color.h"
#include <vector>


class Vec2D;
class Line2D;
struct SDL_Window;
struct SDL_Surface;

class Screen
{

private:
	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	void ClearScreen();

	Screen(const Screen& screen);
	Screen& operator=(const Screen& screen);

protected:

public:

	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreen();

	inline void SetClearColor(const Color& clearColor) { mClearColor = clearColor; }
	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }

	//Draw Methods go here
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(const std::vector<Line2D>& lines, const Color& color);
};
#endif // !_Arcade_Game_Screen_H_

