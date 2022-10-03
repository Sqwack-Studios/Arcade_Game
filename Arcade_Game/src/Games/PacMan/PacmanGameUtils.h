//=================================================================================
// Namespace		: Arcade_Game
// Name				: PacmanGameUtils.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 03/10/2022 12:39:37
//=================================================================================

#ifndef _Arcade_Game_PacmanGameUtils_H_
#define _Arcade_Game_PacmanGameUtils_H_

#pragma once
#include "Vec2D.h"
#include <vector>

enum PacmanMovement
{
	PACMAN_MOVEMENT_NONE = 0,
	PACMAN_MOVEMENT_UP,
	PACMAN_MOVEMENT_LEFT,
	PACMAN_MOVEMENT_DOWN,
	PACMAN_MOVEMENT_RIGHT
};

Vec2D GetMovementVector(PacmanMovement direction);
PacmanMovement GetOppositeDirection(PacmanMovement direction);
std::vector<PacmanMovement> GetPerpendicularMovements(PacmanMovement direction);

#endif // !_Arcade_Game_PacmanGameUtils_H_

