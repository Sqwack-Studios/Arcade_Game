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
#include "SpriteSheet.h"
#include <random>

class Screen;
class Pacman;




class PacmanLevel
{
private:

	struct Tile
	{
		Vec2D position{ Vec2D::Zero };
		Vec2D offset{ Vec2D::Zero };
		int width{ 0 };
		bool collidable{ 0 };
		bool isTeleportTile{ 0 };
		bool excludePelletTile{ 0 };
		bool isPacmanSpawnPoint{ 0 };
		bool isItemSpawnPoint{ 0 };
		char teleportToSymbol{ '0' };
		char symbol{ '-' };
	};

	struct Pellet
	{
		uint32_t score{ 0 };
		AARectangle mBBox;
		int powerPellet{ 0 };
		bool eaten{ 0 };

		const uint32_t PELLET_SIZE = 2;
	};

	struct BonusItem
	{
		uint32_t score = 0;
		AARectangle mBBox;
		bool eaten{ 0 };
		bool spawned{ 0 };
		int spawnTimes{ -1 };
	};

	struct BonusItemLevelProperties
	{
		uint32_t score{ 0 };
		std::string spriteName{ "" };
		uint32_t begin{ 0 }; //which levels does this item spawn at
		uint32_t end{ 0 };
	};

	std::vector<Excluder> mWalls;
	std::vector<Tile> mTiles;
	std::vector<Tile> mPelletExclusionTiles;
	std::vector<Pellet> mPellets;
	std::vector<BonusItemLevelProperties> mBonusItemProperties;
	std::default_random_engine mRandomGenerator;

	Vec2D mLayoutOffset;
	size_t mTileHeight;
	size_t mCurrentLevel;
	Pacman* mnoptrPacman;
	Vec2D mPacmanSpawnLocation;
	BonusItem mBonusItem;
	std::string mBonusItemSpriteName;
	const SpriteSheet* mnoptrSpriteSheet;


	bool LoadLevel(const std::string& levelPath);
	Tile* GetTileForSymbol(const char& symbol);
	void ResetPellets();
	bool HasEatenAllPellets() const;
	size_t NumPelletsEaten() const;
	void GetBonusItemSpriteName(std::string& spriteName, uint32_t& score) const;
	void SpawnBonusItem(); //there is only 1 per level
	bool ShouldSpawnBonusItem() const;
	

protected:

public:


	bool Init(const std::string& levelPath, Pacman* noptrPacman, const SpriteSheet* noptrSpriteSheet);
	void Update(uint32_t deltaTime);
	void Draw(Screen& theScreen);
	bool WillCollide(const AARectangle& aBBox, PacmanMovement direction) const;
	void ResetLevel();
	bool IsLevelOver() const;
	void IncreaseLevel();
	void ResetToFirstLevel();

	inline const Vec2D& GetLayoutOffset() const { return mLayoutOffset; }
	inline const Vec2D& GetPacmanSpawnLocation() const { return mPacmanSpawnLocation; }
};
#endif // !_Arcade_Game_PacmanLevel_H_


