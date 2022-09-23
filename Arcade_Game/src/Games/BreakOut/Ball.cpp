#include "Ball.h"
#include "Utils.h"
#include "Screen.h"
#include "Circle.h"
#include "BoundaryEdge.h"

const float Ball::RADIUS = 1.5f;

Ball::Ball(): 
	Ball(Vec2D::Zero, RADIUS)
{}

Ball::Ball(const Vec2D& pos, float radius):
	mBoundaryBox(pos - Vec2D(radius, radius), radius*2.0f, radius*2.0f),
	mVelocity(Vec2D::Zero),
	mCircle(mBoundaryBox.GetCenterPoint(), RADIUS)
{
}

void Ball::Update(uint32_t deltaTime)
{
	/*mBoundaryBox.MoveBy(mVelocity * MillisecondsToSeconds(deltaTime));*/
}

void Ball::Draw(Screen& screen)
{
	screen.Draw(mCircle, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge)
{
	if (edge.normal == Vec2D::Down)
	{
		mBoundaryBox.MoveTo(
			Vec2D(mBoundaryBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
	}
	else if (edge.normal == Vec2D::Up)
	{
		mBoundaryBox.MoveTo(
			Vec2D(mBoundaryBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBoundaryBox.GetHeight()));
	}
	else if (edge.normal == Vec2D::Right)
	{
		mBoundaryBox.MoveTo(
			Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBoundaryBox.GetTopLeftPoint().GetY()));
	}
	else if (edge.normal == Vec2D::Left)
	{
		mBoundaryBox.MoveTo(
			Vec2D(edge.edge.GetP0().GetX() - mBoundaryBox.GetWidth(), mBoundaryBox.GetTopLeftPoint().GetY()));	
	}

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

	MakeFlushWithEdge(edge, pointOnEdge, false);

	mVelocity = mVelocity.Reflect(edge.normal);
}
