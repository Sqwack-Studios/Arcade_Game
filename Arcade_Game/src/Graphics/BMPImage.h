//=================================================================================
// Namespace		: Arcade_Game
// Name				: BMPImage.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 28/09/2022 18:06:45
//=================================================================================

#ifndef _Arcade_Game_BMPImage_H_
#define _Arcade_Game_BMPImage_H_

#pragma once
#include "Color.h"
#include <vector>
#include <string>
#include <stdint.h>


class BMPImage
{
private:
	std::vector<Color> mPixels;
	uint32_t mWidth;
	uint32_t mHeight;

protected:

public:

	BMPImage();

	bool Load(const std::string& path);

	inline const std::vector<Color>& GetPixels() const { return mPixels; }
	inline uint32_t GetWidth() const { return mWidth; }
	inline uint32_t GetHeight() const { return mHeight; }
};
#endif // !_Arcade_Game_BMPImage_H_

