//=================================================================================
// Namespace		: Arcade_Game
// Name				: BreakoutGameLevel.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 26/09/2022 14:19:31
//=================================================================================

#ifndef _Arcade_Game_BreakoutGameLevel_H_
#define _Arcade_Game_BreakoutGameLevel_H_

#pragma once
#include "Block.h"
#include <vector>
#include <stdint.h>

class Screen;
class Ball;
class AARectangle;

class BreakoutGameLevel
{
private:
	std::vector<Block> mBlocks;

	void CreateDefaultLevel(const AARectangle& boundary);
protected:

public:
	BreakoutGameLevel();
	void Init(const AARectangle& boundary);
	void Load(const std::vector<Block>& blocks);
	void Update(uint32_t deltaTime, Ball& ball);
	void Draw(Screen& screen);
};
#endif // !_Arcade_Game_BreakoutGameLevel_H_

