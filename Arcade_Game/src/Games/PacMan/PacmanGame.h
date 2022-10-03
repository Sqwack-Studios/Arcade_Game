//=================================================================================
// Namespace		: Arcade_Game
// Name				: PacmanGame.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 03/10/2022 10:55:43
//=================================================================================

#ifndef _Arcade_Game_PacmanGame_H_
#define _Arcade_Game_PacmanGame_H_

#pragma once
#include "Game.h"
#include "PacmanLevel.h"

//Overall design
/*
	-Pacman
		-Can eat ghost if ate a super pellet
		-Eat pellets
		-Move in 4 directions through player input (up, down, left, right)
		-Animated
		-Can be eaten 
		-Lives and scores

	-Ghost
		-Can eat pacman if is vulnerable
		-Moves in 4 directions 
		-Animated
		-Different states (alive, vulnerable, vulnerable ending, dead)
		-Has AI
		-Has spawn location
		-Score value
	-AI
		-Each ghost has different behaviours
			-Chase (blinky)
			-Cut off/Ambush (pinky)
			-Pinser attack with Blinky(inky)
			-Wander (clyde)
		-Scatter mode

	-Level
		-Contains the walls, like a maze
		-Contains pellets
		-Wraps Pacman/ghost at specific locations
		-Single background
	-Pellet
		-Super pellet: turns ghost to vulnerable state when eaten by pacman
		-Specific score value
	-Special items
		-Different with different score values
	-UI
		-Score
		-Lives
		-Game over/Ready
	-Game
		-Level
		-Pacman
		-Ghosts
	-States
		-Level start
		-Playing
		-Lost life
		-Game over ->restart, end

*/

class PacmanGame: public Game
{
private:
	PacmanLevel mLevel;
protected:

public:

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetName() const override;
};
#endif // !_Arcade_Game_PacmanGame_H_

