#include "BitmapFont.h"
#include "Vec2D.h"
#include "AARectangle.h"
#include <string>

BitmapFont::BitmapFont()
{
}

Size BitmapFont::GetSizeOf(const std::string& str) const 
{
	Size textSize;

	size_t length = str.length();
	int i = 0;

	for (const char& c : str)
	{
		if (c == ' ')
		{
			textSize.width += GetFontSpacingBetweenWords();
			i++;
			continue;
		}

		Sprite sprite = mFontSheet.GetSprite(std::string("") + c);
		textSize.height = (textSize.height < sprite.height) ? sprite.height : textSize.height;
		textSize.width += sprite.width;

		if (i + 1 < length)
		{
			textSize.width += GetFontSpacingBetweenLetters();
		}
		i++;
	}

	return textSize;
}

bool BitmapFont::Load(const std::string& name)
{
	return mFontSheet.Load(name);
}

Vec2D BitmapFont::GetDrawPosition(const std::string& str, const AARectangle& box, BitmapFontXAlignment xAlign, BitmapFontYAlignment yAlign) const
{
	Size textSize = GetSizeOf(str);

	uint32_t x{ 0 };
	uint32_t y{ 0 };


	switch (xAlign)
	{
		case BFXA_LEFT:
			//do nothing, add x+= box.GetTopLeftPoint
			break;
		case BFXA_CENTER:
			x = box.GetWidth() / 2 - textSize.width / 2;
			break;
		case BFXA_RIGHT:
			x = box.GetWidth() - textSize.width;
			break;
		default:
			break;
	}
	
	switch (yAlign)
	{
		case BFYA_TOP:
			//do nothing, add y+= box.GetTopLeftPoint
			break;
		case BFYA_CENTER:
			y = (box.GetHeight() / 2) - textSize.height / 2;
			break;
		case BFYA_BOTTOM:
			y = box.GetHeight() - textSize.height;
			break;
		default:
			break;
	}

	x += box.GetTopLeftPoint().GetX();
	y += box.GetTopLeftPoint().GetY();
	return Vec2D(x, y);
}
