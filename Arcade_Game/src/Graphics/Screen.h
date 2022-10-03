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
#include <string>
#include <vector>
#include <functional>


class Vec2D;
class Line2D;
class Triangle;
class AARectangle;
class Circle;
class BMPImage;
class SpriteSheet;
class BitmapFont;
struct Sprite;
struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Screen
{

private:
	static const unsigned int NUM_CIRCLE_SEGMENTS = 30;

	using FillPolyFunc = std::function<Color(uint32_t x, uint32_t y)>;

	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	SDL_Renderer* mRenderer;
	SDL_PixelFormat* mPixelFormat;
	SDL_Texture* mTexture;

	bool mFast;

	void ClearScreen();
	void FillPoly(const std::vector<Vec2D>& points, FillPolyFunc func);
	void InitPixelFormat();

	Screen(const Screen& screen);
	Screen& operator=(const Screen& screen);

protected:

public:

	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag, bool fast = true);
	void SwapScreen();

	inline void SetClearColor(const Color& clearColor) { mClearColor = clearColor; }
	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }

	//Draw Methods go here

	//Points, lines, general shapes
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(const std::vector<Line2D>& lines, const Color& color);
	void Draw(const Triangle& triangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const AARectangle& rect, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());

	//Images
	void Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor = Color::White());
	void Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor = Color::White());
	void Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor = Color::White());
};
#endif // !_Arcade_Game_Screen_H_

