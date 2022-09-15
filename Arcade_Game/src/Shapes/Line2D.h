//=================================================================================
// Namespace		: Arcade_Game
// Name				: Line2D.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 15/09/2022 19:28:44
//=================================================================================

#ifndef _Arcade_Game_Line2D_H_
#define _Arcade_Game_Line2D_H_

#pragma once
#include "Vec2D.h"

class Line2D
{
private:

	Vec2D mP0;
	Vec2D mP1;

protected:

public:

	Line2D();
	Line2D(float x0, float y0, float x1, float y1);
	Line2D(const Vec2D& p0, const Vec2D& p1);

	inline const Vec2D& GetP0() const { return mP0; }
	inline const Vec2D& GetP1() const { return mP1; }

	inline void SetP0(const Vec2D& P0) { mP0 = P0; }
	inline void SetP1(const Vec2D& P1) { mP1 = P1; }

	bool operator==(const Line2D& line) const;
	
	float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const;
	
	Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment = false) const;

	Vec2D MidPoint() const;
	float Slope() const;
	float Lenght() const;
};
#endif // !_Arcade_Game_Line2D_H_

