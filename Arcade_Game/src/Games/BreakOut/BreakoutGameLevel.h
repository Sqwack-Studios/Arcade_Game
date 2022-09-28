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
#include "LayoutBlock.h"


class Screen;
class Ball;
class AARectangle;
struct LayoutBlock;

class BreakoutGameLevel
{
private:
	std::vector<Block> mBlocks;

	static const int BLOCK_WIDTH = 18;
	static const int BLOCK_HEIGHT = 8;

	void CreateDefaultLevel(const AARectangle& boundary);
	static LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol);

protected:

public:
	BreakoutGameLevel();
	void Init(const AARectangle& boundary);
	void Load(const std::vector<Block>& blocks);
	void Update(uint32_t deltaTime, Ball& ball);
	void Draw(Screen& screen);

	static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string& filePath);
};
#endif // !_Arcade_Game_BreakoutGameLevel_H_

