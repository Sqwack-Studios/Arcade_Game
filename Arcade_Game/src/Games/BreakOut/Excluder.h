//=================================================================================
// Namespace		: Arcade_Game
// Name				: Excluder.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 23/09/2022 11:26:03
//=================================================================================

#ifndef _Arcade_Game_Excluder_H_
#define _Arcade_Game_Excluder_H_

#pragma once
#include "AARectangle.h"
#include "BoundaryEdge.h"


class Excluder
{
private:
	AARectangle mAARect;
	BoundaryEdge mEdges[NUM_EDGES];
	bool mReverseNormals;
	
	void SetupEdges();
protected:

public:
	virtual ~Excluder() {}
	void Init(const AARectangle& rect, bool reverseNormals = false);
	bool HasCollided(const AARectangle& rect, BoundaryEdge& edge, Vec2D& OutOffset) const;

	inline AARectangle& GetAARectangle() { return mAARect; }
	void MoveBy(const Vec2D& delta);
	void MoveTo(const Vec2D& point);
	const BoundaryEdge& GetEdge(EdgeType edge) const;
};
#endif // !_Arcade_Game_Excluder_H_

