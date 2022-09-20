//=================================================================================
// Namespace		: Arcade_Game
// Name				: Circle.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 20/09/2022 12:55:20
//=================================================================================

#ifndef _Arcade_Game_Circle_H_
#define _Arcade_Game_Circle_H_

#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	float mRadius;

protected:

public:
	Circle();
	Circle(const Vec2D& center, float radius);

	virtual Vec2D GetCenterPoint() const override { return mPoints[0]; }
	inline float GetRadius() const { return mRadius; }
	inline void SetRaiuds(float radius) { mRadius = radius; }
	void MoveTo(const Vec2D& position) { mPoints[0] = position; }

	bool Intersects(const Circle& otherCircle) const;
	bool ContainsPoint(const Vec2D& point) const;
};
#endif // !_Arcade_Game_Circle_H_

