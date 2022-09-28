//=================================================================================
// Namespace		: Arcade_Game
// Name				: SpriteSheet.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 28/09/2022 18:40:30
//=================================================================================

#ifndef _Arcade_Game_SpriteSheet_H_
#define _Arcade_Game_SpriteSheet_H_

#pragma once
#include "BMPImage.h"
#include <string>
#include <vector>
#include <stdint.h>

struct Sprite
{
	uint32_t xPos = 0;
	uint32_t yPos = 0;
	uint32_t width = 0;
	uint32_t height = 0;
};

class SpriteSheet
{
private:
	struct BMPImageSection
	{
		std::string key = "";
		Sprite sprite;
	};

	BMPImage mBMPImage;
	std::vector<BMPImageSection> mSections;


	std::vector<std::string> SpriteNames() const;
	bool LoadSpriteSections(const std::string& path);


protected:

public:

	SpriteSheet();
	bool Load(const std::string& name);
	Sprite GetSprite(const std::string& spriteName) const;

	inline const BMPImage& GetBMPImage() const { return mBMPImage; }

	inline uint32_t GetWidth() const { return mBMPImage.GetWidth(); }
	inline uint32_t GetHeight() const { return mBMPImage.GetHeight(); }
};
#endif // !_Arcade_Game_SpriteSheet_H_

