#include "Vec2D.h"
#include "Utils.h"

std::ostream& operator<< (std::ostream& OutConsole, Vec2D& vec)
{
	std::cout << "X: " << vec.mX << "\tY: " << vec.mY << std::endl;

	return OutConsole;
}

bool Vec2D::operator == (const Vec2D& vec2) const
{
	return IsEqual(mX, vec2.mX) && IsEqual(mY, vec2.mY);
}

bool Vec2D::operator != (const Vec2D& vec2) const
{
	return !(*this == vec2);
}