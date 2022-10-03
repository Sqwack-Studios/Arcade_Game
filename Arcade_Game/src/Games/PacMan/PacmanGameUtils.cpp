#include "PacmanGameUtils.h"

Vec2D GetMovementVector(PacmanMovement direction)
{
	switch (direction)
	{

	case PACMAN_MOVEMENT_NONE:
		return Vec2D::Zero;
	case PACMAN_MOVEMENT_UP:
		return Vec2D::Up;
	case PACMAN_MOVEMENT_LEFT:
		return Vec2D::Left;
	case PACMAN_MOVEMENT_DOWN:
		return Vec2D::Down;
	case PACMAN_MOVEMENT_RIGHT:
		return Vec2D::Right;
	default:
		return Vec2D::Zero;
	}

}

PacmanMovement GetOppositeDirection(PacmanMovement direction)
{
	switch (direction)
	{

	case PACMAN_MOVEMENT_UP:
		return PACMAN_MOVEMENT_DOWN;

	case PACMAN_MOVEMENT_LEFT:
		return PACMAN_MOVEMENT_RIGHT;

	case PACMAN_MOVEMENT_DOWN:
		return PACMAN_MOVEMENT_UP;

	case PACMAN_MOVEMENT_RIGHT:
		return PACMAN_MOVEMENT_LEFT;

	default:
		return PACMAN_MOVEMENT_NONE;
	}
}

std::vector<PacmanMovement> GetPerpendicularMovements(PacmanMovement direction)
{
	std::vector<PacmanMovement> perpendicular;

	if (direction == PACMAN_MOVEMENT_DOWN || direction == PACMAN_MOVEMENT_UP)
	{
		perpendicular.push_back(PACMAN_MOVEMENT_LEFT);
		perpendicular.push_back(PACMAN_MOVEMENT_RIGHT);
	}
	else if (direction == PACMAN_MOVEMENT_RIGHT || direction == PACMAN_MOVEMENT_LEFT)
	{
		perpendicular.push_back(PACMAN_MOVEMENT_UP);
		perpendicular.push_back(PACMAN_MOVEMENT_DOWN);
	}
	else if (direction == PACMAN_MOVEMENT_NONE)
	{
		perpendicular.push_back(PACMAN_MOVEMENT_UP);
		perpendicular.push_back(PACMAN_MOVEMENT_LEFT);
		perpendicular.push_back(PACMAN_MOVEMENT_DOWN);
		perpendicular.push_back(PACMAN_MOVEMENT_RIGHT);
	}

	return perpendicular;
}
