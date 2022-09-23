//=================================================================================
// Namespace		: Arcade_Game
// Name				: LevelBoundary.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 23/09/2022 23:08:29
//=================================================================================

#ifndef _Arcade_Game_LevelBoundary_H_
#define _Arcade_Game_LevelBoundary_H_

#pragma once
#include "Excluder.h"


class AARectangle;
class Ball;

class LevelBoundary
{
private:
	Excluder mIncluder;
	bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const; //check to see if we collided at all
protected:

public:
	LevelBoundary(){}
	LevelBoundary(const AARectangle& boundary);
	bool HasCollided(const Ball& ball, BoundaryEdge& edge);
	inline const AARectangle& GetAARectangle() { return mIncluder.GetAARectangle(); }
};
#endif // !_Arcade_Game_LevelBoundary_H_

