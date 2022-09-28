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
#include <vector>

enum BreakOutGameStates
{
	IN_PLAY = 0,
	IN_SERVE,
	IN_GAME_OVER
};


class BreakOut: public Game
{
private:
	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	std::vector<BreakoutGameLevel> mLevels;
	size_t mCurrentLevel;
	BreakOutGameStates mGameState;
	int mLives;
	float mYCutoff;

	void ResetGame(size_t toLevel = 0);
	void SetToServeState();

	bool IsBallPassedCutoffY() const;
	void ReduceLifeByOne();
	bool IsGameOver() const { return mLives <= 0; }

	const int MAX_LIVES = 3;
	const float INITIAL_BALL_SPEED = 100.f;
	BreakoutGameLevel& GetCurrentLevel() { return mLevels[mCurrentLevel]; }

protected:

public:

	

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
};
#endif // !_Arcade_Game_BreakOut_H_

