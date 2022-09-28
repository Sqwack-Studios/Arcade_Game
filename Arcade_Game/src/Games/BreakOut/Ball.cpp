#include "Ball.h"
#include "Utils.h"
#include "Screen.h"
#include "Circle.h"
#include "BoundaryEdge.h"

const float Ball::RADIUS = 2.5f;

Ball::Ball(): 
	Ball(Vec2D::Zero, RADIUS)
{}

Ball::Ball(const Vec2D& pos, float radius):
	mBoundaryBox(pos - Vec2D(radius, radius), radius*3.f, radius*3.f),
	mVelocity(Vec2D::Zero),
	mCircle(mBoundaryBox.GetCenterPoint(), RADIUS)
{
}

void Ball::Update(uint32_t deltaTime)
{
	mBoundaryBox.MoveBy(mVelocity * MillisecondsToSeconds(deltaTime));
	mCircle.MoveBy(mVelocity * MillisecondsToSeconds(deltaTime));

}

void Ball::Draw(Screen& screen)
{
	screen.Draw(mCircle, Color::Red(), true, Color::Red());
	/*screen.Draw(mBoundaryBox, Color::Green());*/
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge)
{
	if (edge.normal == Vec2D::Down)
	{
		Vec2D point(mBoundaryBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY());
		mBoundaryBox.MoveTo(point);

	}
	else if (edge.normal == Vec2D::Up)
	{
		Vec2D point(mBoundaryBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBoundaryBox.GetHeight());
		mBoundaryBox.MoveTo(point);

	}
	else if (edge.normal == Vec2D::Right)
	{
		Vec2D point(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBoundaryBox.GetTopLeftPoint().GetY());
		mBoundaryBox.MoveTo(point);

	}
	else if (edge.normal == Vec2D::Left)
	{
		Vec2D point(edge.edge.GetP0().GetX() - mBoundaryBox.GetWidth(), mBoundaryBox.GetTopLeftPoint().GetY());
		mBoundaryBox.MoveTo(point);
		
	}
	mCircle.MoveTo(mBoundaryBox.GetCenterPoint());

	pointOnEdge = edge.edge.ClosestPoint(mBoundaryBox.GetCenterPoint(), limitToEdge);
}

void Ball::MoveTo(const Vec2D& point)
{
	
	mBoundaryBox.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
	mCircle.MoveTo(mBoundaryBox.GetCenterPoint());

	
}

void Ball::Bounce(const BoundaryEdge& edge)
{
	Vec2D pointOnEdge;

	
	MakeFlushWithEdge(edge, pointOnEdge, true);

	
	mVelocity = mVelocity.Reflect(edge.normal);
	
}
