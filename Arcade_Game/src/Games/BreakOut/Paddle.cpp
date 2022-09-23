#include "Paddle.h"
#include "Screen.h"
#include "Utils.h"

const float Paddle::VELOCITY = 100.f;

void Paddle::Init(const AARectangle& rect, const AARectangle& boundary)
{
	Excluder::Init(rect);
	mBoundary = boundary;
	mDirection = 0;
}

void Paddle::Update(uint32_t deltaTime)
{
	if (mDirection != 0)
	{
		Vec2D dir;
		if ((mDirection & PaddleDirection::LEFT) == PaddleDirection::LEFT && (mDirection & PaddleDirection::RIGHT) == PaddleDirection::RIGHT)
		{
			dir = Vec2D::Zero;
		}
		else if (mDirection == PaddleDirection::LEFT)
		{
			dir = Vec2D::Left;
		}
		else
		{
			dir = Vec2D::Right;
		}
		Vec2D dx = VELOCITY * MillisecondsToSeconds(deltaTime) * dir ;
		
		MoveBy(dx);
		const AARectangle& aaRect = GetAARectangle();

		if (IsGreaterThanOrEqual(mBoundary.GetTopLeftPoint().GetX(), aaRect.GetTopLeftPoint().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetTopLeftPoint().GetX(), aaRect.GetTopLeftPoint().GetY()));
		}
		else if(IsGreaterThanOrEqual(aaRect.GetBottomRightPoint().GetX(), mBoundary.GetBottomRightPoint().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetBottomRightPoint().GetX() - aaRect.GetWidth() + 1, aaRect.GetTopLeftPoint().GetY()));
		}

	}
}

void Paddle::Draw(Screen& screen)
{
	screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue());

}

