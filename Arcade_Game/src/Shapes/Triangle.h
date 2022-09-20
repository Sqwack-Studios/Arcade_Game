//=================================================================================
// Namespace		: Arcade_Game
// Name				: Triangle.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 20/09/2022 9:57:09
//=================================================================================

#ifndef _Arcade_Game_Triangle_H_
#define _Arcade_Game_Triangle_H_

#pragma once
#include "Shape.h"


class Triangle : public Shape
{
private:
	float Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;
protected:

public:

	Triangle();
	Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

	inline void SetP0(const Vec2D& p0) { mPoints[0] = p0; }
	inline void SetP1(const Vec2D& p1) { mPoints[1] = p1; }
	inline void SetP2(const Vec2D& p2) { mPoints[2] = p2; }

	inline Vec2D GetP0() const { return mPoints[0]; }
	inline Vec2D GetP1() const { return mPoints[1]; }
	inline Vec2D GetP2() const { return mPoints[2]; }

	virtual Vec2D GetCenterPoint() const override;

	float Area() const;

	bool ContainsPoint(const Vec2D& s) const;
};
#endif // !_Arcade_Game_Triangle_H_

