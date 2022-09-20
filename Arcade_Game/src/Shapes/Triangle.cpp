#include "Triangle.h"
#include <cmath>
#include "Utils.h"

Triangle::Triangle() : Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero)
{

}

Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2)
{
    mPoints.push_back(p0);
    mPoints.push_back(p1);
    mPoints.push_back(p2);
}




Vec2D Triangle::GetCenterPoint() const
{
    float centroidX = (mPoints[0].GetX() + mPoints[1].GetX() + mPoints[2].GetX()) / 3.0f;
    float centroidY = (mPoints[0].GetY() + mPoints[1].GetY() + mPoints[2].GetY()) / 3.0f;
    return Vec2D(centroidX, centroidY);
}

float Triangle::Area() const
{
    return Area(GetP0(), GetP1(), GetP2());
}

float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const
{
    Vec2D u = p1 - p0;
    Vec2D v = p2 - p0;
    float crossUxV = u.Cross(v) /2.0f;

    if (crossUxV > 0)
        return crossUxV;
    else
        return -crossUxV;

}

bool Triangle::ContainsPoint(const Vec2D& s) const
{
    Vec2D P0_S(s - GetP0());
    std::cout << P0_S << std::endl;
    Vec2D P0_P1(GetP1() - GetP0());
    std::cout << P0_P1 << std::endl;

    //Check side of the side plane with the cross product of P0P1 X P0S
    std::cout << P0_P1.Cross(P0_S) << std::endl;
    bool crossP0P1_P0PS = P0_P1.Cross(P0_S) > 0;

    Vec2D P0_P2(GetP2() - GetP0());
    //The cross product with the segment P0P2 * P0S has to be different to be in the triangle
    std::cout << P0_P2.Cross(P0_S) << std::endl;
    if (P0_P2.Cross(P0_S) > 0 == crossP0P1_P0PS) return false;

    Vec2D P1_P2(GetP2() - GetP1());
    Vec2D P1_S(s - GetP1());
    //The cross product of the segment P2P1 X P1S has to equal initial cross product
    if (P1_P2.Cross(P1_S)> 0 != crossP0P1_P0PS) return false;

    return true;
}
