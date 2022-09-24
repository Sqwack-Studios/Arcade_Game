#include "Paddle.h"
#include "Screen.h"
#include "Utils.h"
#include "Ball.h"
#include <assert.h>

const float Paddle::VELOCITY = 100.f;

void Paddle::Init(const AARectangle& rect, const AARectangle& boundary)
{
	Excluder::Init(rect);
	mBoundary = boundary;
	mDirection = 0;
}

void Paddle::Update(uint32_t deltaTime, Ball& ball)
{
	if (GetAARectangle().ContainsPoint(ball.GetPosition()))
	{
		Vec2D pointOnEdge;
		ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
	}

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

bool Paddle::Bounce(Ball& ball)
{
	BoundaryEdge edge;
	Vec2D pointOnEdge;

	if (HasCollided(ball.GetBoundaryBox(), edge, pointOnEdge))
	{
		ball.MakeFlushWithEdge(edge, pointOnEdge, true);

		if (edge.edge == GetEdge(TOP_EDGE).edge)
		{
			float edgeLenght = edge.edge.Lenght();

			assert(!IsEqual(edgeLenght, 0) && "Por elculooo");

			float tx = (pointOnEdge.GetX() - edge.edge.GetP0().GetX()) / edgeLenght;


			if (((tx <= CORNER_BOUNCE_SURFACE) && ball.GetVelocity().GetX() > 0) || (tx >= (1.0f - CORNER_BOUNCE_SURFACE) && ball.GetVelocity().GetX() < 0))
			{
				ball.SetVelocity(-ball.GetVelocity());
				return true;
			}
		}
		ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal));
		return true;
	}
	return false;
}
