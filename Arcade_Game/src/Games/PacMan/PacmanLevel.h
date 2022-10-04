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
#include "PacmanGameUtils.h"

class Screen;
class Pacman;

struct Tile
{
	Vec2D position{ Vec2D::Zero };
	Vec2D offset{ Vec2D::Zero };
	int width{ 0 };
	bool collidable{ 0 };
	bool isTeleportTile{ 0 };
	char teleportToSymbol{ '0' };
	char symbol{ '-' };
};


class PacmanLevel
{
private:
	

	std::vector<Excluder> mWalls;
	std::vector<Tile> mTiles;

	Vec2D mLayoutOffset;
	size_t mTileHeight;
	Pacman* mnoptrPacman;


	bool LoadLevel(const std::string& levelPath);
	Tile* GetTileForSymbol(const char& symbol);

protected:

public:


	bool Init(const std::string& levelPath, Pacman* noptrPacman);
	void Update(uint32_t deltaTime);
	void Draw(Screen& theScreen);
	bool WillCollide(const AARectangle& aBBox, PacmanMovement direction) const;
};
#endif // !_Arcade_Game_PacmanLevel_H_


