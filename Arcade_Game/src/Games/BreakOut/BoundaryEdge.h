//=================================================================================
// Namespace		: Arcade_Game
// Name				: BoundaryEdge.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 23/09/2022 11:29:15
//=================================================================================

#ifndef _Arcade_Game_BoundaryEdge_H_
#define _Arcade_Game_BoundaryEdge_H_

#pragma once
#include "Vec2D.h"
#include "Line2D.h"

/*
*				^	normal
*				|
*-------------------------------edge
*
*/

enum EdgeType
{
	BOTTOM_EDGE = 0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};
struct BoundaryEdge
{
	Vec2D normal;
	Line2D edge;
};
#endif // !_Arcade_Game_BoundaryEdge_H_

