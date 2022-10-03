//=================================================================================
// Namespace		: Arcade_Game
// Name				: PacmanLevel.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 03/10/2022 11:52:40
//=================================================================================

#ifndef _Arcade_Game_PacmanLevel_H_
#define _Arcade_Game_PacmanLevel_H_

#pragma once
#include "Vec2D.h"
#include "Excluder.h"
#include <string>
#include <vector>

class Screen;

struct Tile
{
	Vec2D position{ Vec2D::Zero };
	int width{ 0 };
	bool collidable{ 0 };
	char symbol{ '-' };
};


class PacmanLevel
{
private:
	

	std::vector<Excluder> mWalls;
	std::vector<Tile> mTiles;

	Vec2D mLayoutOffset;
	size_t mTileHeight;


	bool LoadLevel(const std::string& levelPath);
	Tile* GetTileForSymbol(const char& symbol);

protected:

public:


	bool Init(const std::string& levelPath);
	void Update(uint32_t deltaTime);
	void Draw(Screen& theScreen);
};
#endif // !_Arcade_Game_PacmanLevel_H_

