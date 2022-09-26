//=================================================================================
// Namespace		: Arcade_Game
// Name				: Block.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 26/09/2022 14:06:08
//=================================================================================

#ifndef _Arcade_Game_Block_H_
#define _Arcade_Game_Block_H_

#pragma once
#include "Excluder.h"
#include "Color.h"

class Ball;
class Screen;

class Block: public Excluder
{
private:
	Color mOutlineColor;
	Color mFillColor;

	int mHp;

protected:

public:

	static const int UNBREAKABLE{ -1 };

	Block();

	void Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);
	void Draw(Screen& screen);
	void Bounce(Ball& ball, const BoundaryEdge& edge);

	void ReduceHP();
	inline int GetHP() const { return mHp; }
	inline bool IsDestroyed() const { return mHp == 0; }
	inline const Color& GetOutlineColor() const { return mOutlineColor; }
	inline const Color& GetFillColor() const { return mFillColor; }
};
#endif // !_Arcade_Game_Block_H_

