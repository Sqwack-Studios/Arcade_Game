//=================================================================================
// Namespace		: Arcade_Game
// Name				: Star2D.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 19/09/2022 13:02:57
//=================================================================================

#ifndef _Arcade_Game_Star2D_H_
#define _Arcade_Game_Star2D_H_

#pragma once
#include "Vec2D.h"
#include <vector>

class Line2D;

class Star2D
{
private:
	static const int DEFAULT_INNER_RADII = 3;
	static const int DEFAULT_OUTER_RADII = 10;
	static const int DEFAULT_NUM_SPIKES = 5;
	static Vec2D DEFAULT_STAR_POSITION;

	Vec2D mCenter;
	int mOuterRadii;
	int mInnerRadii;
	int mNumSpikes;

	std::vector<Line2D> mLines;

	void BuildStar();

protected:

public:

	Star2D();
	Star2D(const Vec2D& center);
	Star2D(const Vec2D& center, const int& outerRadii, const int& innerRadii, const int& numSpikes, const float& angle = 0.0);

	void Rotate(const float& angle, const Vec2D& aroundPoint);
	std::vector<Line2D> SendToBuffer() const { return mLines; };


};
#endif // !_Arcade_Game_Star2D_H_

