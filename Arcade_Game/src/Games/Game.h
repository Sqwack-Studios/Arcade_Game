//=================================================================================
// Namespace		: Arcade_Game
// Name				: Game.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 22/09/2022 13:48:14
//=================================================================================

#ifndef _Arcade_Game_Game_H_
#define _Arcade_Game_Game_H_

#pragma once
#include <string>
#include <stdint.h>


class GameController;
class Screen;

//Game interface
class Game
{
private:

protected:

public:
	virtual ~Game(){}
	virtual void Init(GameController& controller) = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual std::string GetName() const = 0;
};
#endif // !_Arcade_Game_Game_H_

