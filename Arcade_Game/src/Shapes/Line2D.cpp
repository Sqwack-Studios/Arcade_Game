#include "Line2D.h"

Line2D::Line2D() : Line2D(Vec2D::Zero, Vec2D::Zero)
{

}

Line2D::Line2D(float x0, float y0, float x1, float y1) :
	Line2D(Vec2D(x0,y0), Vec2D(x1, y1))
{

}

Line2D::Line2D(const Vec2D& p0, const Vec2D& p1) :
	mP0(p0),
	mP1(p1)
{

}

bool Line2D::operator==(const Line2D& line) const
{
	return line.GetP0() == mP0 && line.GetP1() == mP1;
}

float Line2D::MinDistanceFrom(const Vec2D& p, bool limitToSegment) const
{
	return 0.0f;
}

Vec2D Line2D::ClosestPoint(const Vec2D& p, bool limitToSegment) const
{
	return Vec2D();
}

Vec2D Line2D::MidPoint() const
{
	return Vec2D();
}

float Line2D::Slope() const
{
	return 0.0f;
}

float Line2D::Lenght() const
{
	return 0.0f;
}
