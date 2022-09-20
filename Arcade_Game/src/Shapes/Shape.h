//=================================================================================
// Namespace		: Arcade_Game
// Name				: Shape.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 20/09/2022 9:49:24
//=================================================================================

#ifndef _Arcade_Game_Shape_H_
#define _Arcade_Game_Shape_H_

#pragma once
#include "Vec2D.h"
#include <vector>


class Shape
{
private:

protected:
	std::vector<Vec2D> mPoints;

public:
	virtual Vec2D GetCenterPoint() const = 0;
	virtual ~Shape() {}
	inline virtual std::vector<Vec2D> GetPoints() const { return mPoints; }
	void MoveBy(const Vec2D& delta);

};
#endif // !_Arcade_Game_Shape_H_

