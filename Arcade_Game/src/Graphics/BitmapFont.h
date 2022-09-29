//=================================================================================
// Namespace		: Arcade_Game
// Name				: BitmapFont.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 29/09/2022 13:13:33
//=================================================================================

#ifndef _Arcade_Game_BitmapFont_H_
#define _Arcade_Game_BitmapFont_H_

#pragma once
#include "SpriteSheet.h"
#include "Utils.h"
#include <stdint.h>

class Vec2D;
class AARectangle;


enum BitmapFontXAlignment {
	BFXA_LEFT = 0,
	BFXA_CENTER,
	BFXA_RIGHT
};

enum BitmapFontYAlignment {
	BFYA_TOP = 0,
	BFYA_CENTER,
	BFYA_BOTTOM
};


class BitmapFont
{
private:
	SpriteSheet mFontSheet;

protected:

public:

	BitmapFont();

	Size GetSizeOf(const std::string& str) const;
	bool Load(const std::string& name);
	Vec2D GetDrawPosition(const std::string& str, const AARectangle& box, BitmapFontXAlignment xAlign = BFXA_LEFT, BitmapFontYAlignment yAlign = BFYA_TOP) const;

	inline const SpriteSheet& GetSpriteSheet() const { return mFontSheet; }
	inline const uint32_t GetFontSpacingBetweenLetters() const { return 2; }
	inline const uint32_t GetFontSpacingBetweenWords() const { return 5; }
};
#endif // !_Arcade_Game_BitmapFont_H_

