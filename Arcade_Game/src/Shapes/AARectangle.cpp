#include "AARectangle.h"
#include "Utils.h"
#include <cmath>



AARectangle::AARectangle(): AARectangle(Vec2D::Zero, Vec2D::Zero)
{
}

AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(BuildBottomRightPoint(topLeft, width, height));
}

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(bottomRight);
}

Vec2D AARectangle::BuildBottomRightPoint(const Vec2D& topLeft, unsigned int width, unsigned int height) const
{
    return Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1);
}

int AARectangle::GetWidth() const
{
    return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}

int AARectangle::GetHeight() const
{
    return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY() + 1;
}

void AARectangle::MoveTo(const Vec2D& position)
{
    int width = GetWidth();
    int height = GetHeight();

    SetTopLeftPoint(position);
    SetBottomRightPoint(BuildBottomRightPoint(GetTopLeftPoint(), width, height));
}

Vec2D AARectangle::GetCenterPoint() const
{
    return Vec2D(GetTopLeftPoint().GetX() + GetWidth()/2, GetTopLeftPoint().GetY() + GetHeight()/2);
}

bool AARectangle::Intersects(const AARectangle& otherRect) const
{
    return !(otherRect.GetBottomRightPoint().GetX() <       GetTopLeftPoint().GetX()        ||
             otherRect.GetTopLeftPoint().GetX()     >       GetBottomRightPoint().GetX()    ||
             otherRect.GetBottomRightPoint().GetY() <       GetTopLeftPoint().GetY()        ||
             otherRect.GetTopLeftPoint().GetY()     >       GetBottomRightPoint().GetY());
}

bool AARectangle::ContainsPoint(const Vec2D& point) const
{
    bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
    bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY(); 

    return withinX && withinY;
}

AARectangle AARectangle::Inset(const AARectangle& rect, const Vec2D& insets)
{
    return AARectangle(rect.GetTopLeftPoint() + insets, rect.GetWidth() - 2*insets.GetX(), rect.GetHeight() - 2 * insets.GetY());
}

std::vector<Vec2D> AARectangle::GetPoints() const
{
    std::vector <Vec2D> points;

    points.push_back(mPoints[0]);
    points.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY()));
    points.push_back(mPoints[1]);
    points.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY()));

    return points;
}
