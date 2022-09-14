//=================================================================================
// Namespace		: Arcade_Game
// Name				: ScreenBuffer.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 15/09/2022 0:31:13
//=================================================================================

#ifndef _Arcade_Game_ScreenBuffer_H_
#define _Arcade_Game_ScreenBuffer_H_

#pragma once
#include <stdint.h>
#include "Color.h"
class Color;
struct SDL_Surface;

class ScreenBuffer
{
private:
	SDL_Surface* mSurface;
	size_t GetIndex(int r, int c);

	void CopyBuffer(const ScreenBuffer& screenBuffer);
protected:

public:
	ScreenBuffer();
	ScreenBuffer(const ScreenBuffer& screenBuffer);
	~ScreenBuffer();

	ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

	void Init(uint32_t format, uint32_t width, uint32_t height);

	inline SDL_Surface* GetSurface() { return mSurface; }

	void Clear(const Color& color = Color::Black());

	void SetPixel(const Color& color, int x, int y);
};
#endif // !_Arcade_Game_ScreenBuffer_H_

