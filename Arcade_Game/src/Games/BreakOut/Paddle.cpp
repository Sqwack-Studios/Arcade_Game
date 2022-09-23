#include "Paddle.h"
#include "Color.h"
#include "Screen.h"
#include "Utils.h"

const float Paddle::VELOCITY = 50.f;

void Paddle::Init(const AARectangle& rect)
{
	Excluder::Init(rect);
	mDirection = PaddleDirection::NONE;
}

void Paddle::Update(uint32_t deltaTime)
{
	if (mDirection != PaddleDirection::NONE)
	{
		Vec2D dir;
		if (mDirection == PaddleDirection::LEFT)
		{
			dir = Vec2D::Left;
		}
		else
		{
			dir = Vec2D::Right;
		}
		float da = VELOCITY;
		Vec2D dx = VELOCITY * MillisecondsToSeconds(deltaTime) * dir ;
		MoveBy(dx);
	}
}

void Paddle::Draw(Screen& screen)
{
	screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue());
}

