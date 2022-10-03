//=================================================================================
// Namespace		: Arcade_Game
// Name				: AARectangle.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 20/09/2022 12:16:52
//=================================================================================

#ifndef _Arcade_Game_AARectangle_H_
#define _Arcade_Game_AARectangle_H_

#pragma once
#include "Shape.h"

class AARectangle: public Shape
{
private:

	Vec2D BuildBottomRightPoint(const Vec2D& topLeft, unsigned int width, unsigned int height) const;
protected:

public:
	AARectangle();
	AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
	AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

	inline void SetTopLeftPoint(const Vec2D& topLeft) { mPoints[0] = topLeft; }
	inline void SetBottomRightPoint(const Vec2D& bottomRight) { mPoints[1] = bottomRight; }

	Vec2D GetTopLeftPoint() const { return mPoints[0]; }
	Vec2D GetBottomRightPoint() const { return mPoints[1]; }

	int GetWidth() const;
	int GetHeight() const;

	void MoveTo(const Vec2D& position);

	virtual Vec2D GetCenterPoint() const override;

	bool Intersects(const AARectangle& otherRect) const;
	bool ContainsPoint(const Vec2D& point) const;

	static AARectangle Inset(const AARectangle& rect, const Vec2D& insets);

	virtual std::vector<Vec2D> GetPoints() const override;
};
#endif // !_Arcade_Game_AARectangle_H_

