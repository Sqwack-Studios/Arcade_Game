//=================================================================================
// Namespace		: Arcade_Game
// Name				: Paddle.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 23/09/2022 12:56:16
//=================================================================================

#ifndef _Arcade_Game_Paddle_H_
#define _Arcade_Game_Paddle_H_

#pragma once
#include "Excluder.h"
#include <stdint.h>
class Screen;
class Ball;

enum PaddleDirection
{
	LEFT = 1 << 0,
	RIGHT = 1 << 1
};

class Paddle : public Excluder
{
private:
	uint32_t mDirection; //Direction we are moving

	static const float VELOCITY;//pixels/sec
	const float CORNER_BOUNCE_SURFACE = 0.2f; //normalized
	AARectangle mBoundary;



protected:

public:

	void Init(const AARectangle& rect, const AARectangle& boundary);

	void Update(uint32_t deltaTime, Ball& ball);

	void Draw(Screen& screen);

	bool Bounce(Ball& ball);

	inline bool IsMovingLeft() const { return mDirection == PaddleDirection::LEFT; }
	inline bool IsMovinRight() const { return mDirection == PaddleDirection::RIGHT; }

	inline void SetMovementDirection(PaddleDirection direction) { mDirection |= direction; }
	inline void UnsetMovementDirection(PaddleDirection dir) { mDirection &= ~dir; }

	inline void StopMovement() { mDirection = 0; }

	static const uint32_t PADDLE_WIDTH = 50;
	static const uint32_t PADDLE_HEIGHT = 10;

};
#endif // !_Arcade_Game_Paddle_H_

