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

enum PaddleDirection
{
	NONE = 0,
	LEFT,
	RIGHT
};

class Paddle : public Excluder
{
private:
	PaddleDirection mDirection; //Direction we are moving

	static const float VELOCITY; //pixels/sec

protected:

public:

	void Init(const AARectangle& rect);

	void Update(uint32_t deltaTime);

	void Draw(Screen& screen);

	inline bool IsMovingLeft() const { return mDirection == PaddleDirection::LEFT; }
	inline bool IsMovinRight() const { return mDirection == PaddleDirection::RIGHT; }

	inline void SetMovementDirection(PaddleDirection direction) { mDirection = direction; }
	inline void StopMovement() { mDirection = PaddleDirection::NONE; }

	static const uint32_t PADDLE_WIDTH = 100;
	static const uint32_t PADDLE_HEIGHT = 30;

};
#endif // !_Arcade_Game_Paddle_H_

