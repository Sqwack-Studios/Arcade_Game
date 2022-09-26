//=================================================================================
// Namespace		: Arcade_Game
// Name				: BreakOut.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 23/09/2022 10:55:07
//=================================================================================

#ifndef _Arcade_Game_BreakOut_H_
#define _Arcade_Game_BreakOut_H_




#pragma once
#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"

class BreakOut: public Game
{
private:
	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	BreakoutGameLevel mLevel;

	void ResetGame();

	const Vec2D INITIAL_BALL_VEL = Vec2D(100, -100);

protected:

public:

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
};
#endif // !_Arcade_Game_BreakOut_H_

