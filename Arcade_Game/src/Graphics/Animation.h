//=================================================================================
// Namespace		: Arcade_Game
// Name				: Animation.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 30/09/2022 13:31:34
//=================================================================================

#ifndef _Arcade_Game_Animation_H_
#define _Arcade_Game_Animation_H_

#pragma once
#include <string>
#include <vector>
#include "Vec2D.h"
#include "Color.h"
#include "Utils.h"

struct AnimationFrame
{
	std::string frame = "";
	std::string overlay = "";
	Color frameColor = Color::White();
	Color overlayColor = Color::White();
	Vec2D size;
	Vec2D offSet{ Vec2D::Zero };
	bool frameColorSet = 0;
};

struct Animation
{
	std::string mAnimationName;
	std::string mSpriteSheetName;
	std::string mOverlay;
	std::vector<std::string> mFrameNames;
	std::vector<Color> mFrameColors;
	std::vector<Color> mOverlayColors;
	std::vector<Vec2D> mFrameOffsets;
	Vec2D mSize;
	int mFPS;

	Animation();

	static std::vector<Animation> LoadAnimations(const std::string& animationFilePath);

	inline void AddFrame(const std::string& frameName) { mFrameNames.push_back(frameName); }
	inline void AddFrameColor(const Color& color) { mFrameColors.push_back(color); }
	inline void AddOverlayFrameColor(const Color& color) { mOverlayColors.push_back(color); }
	inline void AddFrameOffset(const Vec2D& offset) { mFrameOffsets.push_back(offset); }

	AnimationFrame GetAnimationFrame(uint32_t frameNum) const;
};
#endif // !_Arcade_Game_Animation_H_

