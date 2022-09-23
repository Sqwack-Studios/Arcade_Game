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

class BreakOut: public Game
{
private:
	Paddle mPaddle;
	Ball mBall;

	void ResetGame();


protected:

public:

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
};
#endif // !_Arcade_Game_BreakOut_H_

