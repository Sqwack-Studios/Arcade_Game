//=================================================================================
// Namespace		: Arcade_Game
// Name				: Color.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 14/09/2022 23:49:55
//=================================================================================

#ifndef _Arcade_Game_Color_H_
#define _Arcade_Game_Color_H_

#pragma once

#include <stdint.h>

struct SDL_PixelFormat;

class Color
{
private:
	uint32_t mColor;

protected:

public:
	static Color EvaluateMinueSourceAlpha(const Color& source, const Color& destination);

	static const SDL_PixelFormat* mFormat;
	static void InitColorFormat(const SDL_PixelFormat* format);

	static Color Black() { return Color(0, 0, 0, 255); }
	static Color White() { return Color(255, 255, 255, 255); }
	static Color Blue() { return Color(0, 0, 255, 255); }
	static Color Red() { return Color(255, 0, 0, 255); }
	static Color Green() { return Color(0, 255, 0, 255); }
	static Color Yellow() { return Color(255, 255, 0, 255); }
	static Color Magenta() { return Color(255, 0, 255, 255); }
	static Color Cyan() { return Color(37, 240, 217, 255); }
	static Color Pink() { return Color(252, 197, 224, 255); }
	static Color Orange() { return Color(245, 190, 100, 255); }


	Color();
	Color(uint32_t color);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	inline bool operator==(const Color& c) const { return mColor == c.mColor; }
	inline bool operator!=(const Color& c) const { return !(*this == c); }
	inline uint32_t GetPixelColor() const { return mColor; }

	void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void SetRed(uint8_t red);
	void SetGreen(uint8_t green);
	void SetBlue(uint8_t blue);
	void SetAlpha(uint8_t alpha);

	uint8_t GetRed() const;
	uint8_t GetGreen() const;
	uint8_t GetBlue() const;
	uint8_t GetAlpha() const;
};
#endif // !_Arcade_Game_Color_H_

