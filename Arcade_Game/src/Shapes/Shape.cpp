#include "Shape.h"

void Shape::MoveBy(const Vec2D& delta)
{
	for (Vec2D& point : mPoints)
	{
		point += delta;
	}
}