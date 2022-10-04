#include "PacmanLevel.h"
#include "Screen.h"
#include "FileCommandLoader.h"
#include "Pacman.h"
#include "App.h"
#include "Circle.h"
#include <assert.h>

namespace {

    const uint32_t NUM_LEVELS = 256;
    const uint32_t SPRITE_HEIGHT = 16;
    const uint32_t SPRITE_WIDTH = 16;
}

bool PacmanLevel::Init(const std::string& levelPath, Pacman* noptrPacman, const SpriteSheet* noptrSpriteSheet)
{
    mCurrentLevel = 0;
    mnoptrPacman = noptrPacman;
    mnoptrSpriteSheet = noptrSpriteSheet;
    mBonusItemSpriteName = "";
    std::random_device r;

    mRandomGenerator.seed(r());

    bool levelLoaded = LoadLevel(levelPath);
    if (levelLoaded)
    {
        
        ResetLevel();
        ++mCurrentLevel;
    }

    return levelLoaded;
}

void PacmanLevel::Update(uint32_t deltaTime)
{
    for (const auto& wall : mWalls)
    {
        BoundaryEdge edge;
        Vec2D outOffset;
 
        if (wall.HasCollided(mnoptrPacman->GetBoundingBox(), edge, outOffset))
        {
            mnoptrPacman->MoveBy(outOffset);
            mnoptrPacman->StopAnimation();
        }
    }

    for (const Tile& tile : mTiles)
    {
        if (tile.isTeleportTile)
        {
            AARectangle teleportTileAABB(tile.position, tile.width, static_cast<float>(mTileHeight));
            Tile* teleportToTile = GetTileForSymbol(tile.teleportToSymbol);
            assert(teleportToTile);

            if (teleportToTile->isTeleportTile && teleportTileAABB.Intersects(mnoptrPacman->GetBoundingBox()))
            {
                mnoptrPacman->MoveTo(teleportToTile->position + teleportToTile->offset);
            }
        }
    }


    for (auto& pellet : mPellets)
    {
        if (!pellet.eaten)
        {
            if (mnoptrPacman->GetBoundingBox().Intersects(pellet.mBBox))
            {
                pellet.eaten = true;
                mnoptrPacman->AteItem(pellet.score);

                if (pellet.powerPellet)
                {
                    mnoptrPacman->ResetGhostEatenMultiplier();
                    //TODO: make ghost go vulnerable
                }
            }
        }
    }

    if (ShouldSpawnBonusItem())
    {
        SpawnBonusItem();
    }

    if (mBonusItem.spawned && !mBonusItem.eaten)
    {
        if (mnoptrPacman->GetEatingBoundingBox().Intersects(mBonusItem.mBBox))
        {
            mBonusItem.eaten = true;
            mnoptrPacman->AteItem(mBonusItem.score);
        }
    }

    if (IsLevelOver())
    {
        IncreaseLevel();
    }
}

void PacmanLevel::Draw(Screen& theScreen)
{
    //debug for walls
 
    for (const auto& wall : mWalls)
    {
        theScreen.Draw(wall.GetAARectangle(), Color::Blue());
    }

    for (const auto& pellet : mPellets)
    {
        if (!pellet.eaten)
        {
            if (!pellet.powerPellet)
            {
                theScreen.Draw(pellet.mBBox, Color::White());
            }
            else
            {
                Circle c{ pellet.mBBox.GetCenterPoint(), pellet.mBBox.GetWidth() / 2.0f };
                theScreen.Draw(c, Color::White(), true, Color::White());
            }
        }
    }

    if (mBonusItem.spawned && !mBonusItem.eaten)
    {
        theScreen.Draw(*mnoptrSpriteSheet, mBonusItemSpriteName, mBonusItem.mBBox.GetTopLeftPoint());
    }
  
}

bool PacmanLevel::WillCollide(const AARectangle& aBBox, PacmanMovement direction) const
{
    AARectangle bbox = aBBox;

    bbox.MoveBy(GetMovementVector(direction));

    for (const auto& wall : mWalls)
    {
        BoundaryEdge edge;
        Vec2D outHit;
        if (wall.HasCollided(bbox, edge, outHit))
        {
            return true;
        }
    }
    return false;
}

bool PacmanLevel::LoadLevel(const std::string& levelPath)
{
    FileCommandLoader fileLoader;

    Command tileCommand;
    tileCommand.command = "tile";
    tileCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.push_back(Tile());
    };
    fileLoader.AddCommand(tileCommand);

    Command tileWidthCommand;
    tileWidthCommand.command = "tile_width";
    tileWidthCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().width = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileWidthCommand);

    Command tileHeightCommand;
    tileHeightCommand.command = "tile_height";
    tileHeightCommand.parseFunc = [this](ParseFuncParams params) {

        mTileHeight = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileHeightCommand);

    Command tileSymbolCommand;
    tileSymbolCommand.command = "tile_symbol";
    tileSymbolCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().symbol = FileCommandLoader::ReadChar(params);
    };
    fileLoader.AddCommand(tileSymbolCommand);

    Command tileCollisionCommand;
    tileCollisionCommand.command = "tile_collision";
    tileCollisionCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().collidable = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileCollisionCommand);

    Vec2D layoutOffset;

    Command layoutOffsetCommand;
    layoutOffsetCommand.command = "layout_offset";
    layoutOffsetCommand.parseFunc = [this, &layoutOffset](ParseFuncParams params) {

        mLayoutOffset = FileCommandLoader::ReadSize(params);
        layoutOffset = mLayoutOffset;
    };
    fileLoader.AddCommand(layoutOffsetCommand);


    Command tileToTelerportCommand;
    tileToTelerportCommand.command = "tile_teleport_to_symbol";
    tileToTelerportCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().teleportToSymbol = FileCommandLoader::ReadChar(params);
    };
    fileLoader.AddCommand(tileToTelerportCommand);

    Command tileIsTeleportTileCommand;
    tileIsTeleportTileCommand.command = "tile_is_teleport_tile";
    tileIsTeleportTileCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().isTeleportTile = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileIsTeleportTileCommand);

    Command offSetCommand;
    offSetCommand.command = "tile_offset";
    offSetCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().offset = FileCommandLoader::ReadSize(params);
    };
    fileLoader.AddCommand(offSetCommand);

    Command tileExcludePelletCommand;
    tileExcludePelletCommand.command = "tile_exclude_pellet";
    tileExcludePelletCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().excludePelletTile = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileExcludePelletCommand);

    Command tileIsPacmanSpawnPointCommand;
    tileIsPacmanSpawnPointCommand.command = "tile_pacman_spawn_point";
    tileIsPacmanSpawnPointCommand.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().isPacmanSpawnPoint = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileIsPacmanSpawnPointCommand);

    Command tileItemSpawnPoint;
    tileItemSpawnPoint.command = "tile_item_spawn_point";
    tileItemSpawnPoint.parseFunc = [this](ParseFuncParams params) {

        mTiles.back().isItemSpawnPoint = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileItemSpawnPoint);

    Command layoutCommand;
    layoutCommand.command = "layout";
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.parseFunc = [this, &layoutOffset](ParseFuncParams params) {

        int startingX = layoutOffset.GetX();

        for (const char& c : params.line)
        {
            Tile* tile = GetTileForSymbol(c);

            if (tile)
            {
                tile->position = Vec2D(startingX, layoutOffset.GetY());

                if (tile->collidable)
                {
                    Excluder wall;
                    wall.Init
                    (
                        AARectangle(Vec2D(startingX, layoutOffset.GetY()), tile->width, static_cast<int>(mTileHeight))
                    );

                    mWalls.push_back(wall);
                }

                if (tile->isPacmanSpawnPoint > 0)
                {
                    mPacmanSpawnLocation = Vec2D(startingX + tile->offset.GetX(), layoutOffset.GetY() + tile->offset.GetY());
                }
                else if (tile->isItemSpawnPoint)
                {
                    mBonusItem.mBBox = AARectangle(
                        Vec2D(startingX + tile->offset.GetX(), layoutOffset.GetY() + tile->offset.GetY()),
                        SPRITE_WIDTH,
                        SPRITE_HEIGHT);
                   
                }

                if (tile->excludePelletTile != 0)
                {
                    mPelletExclusionTiles.push_back(*tile);
                }

                startingX += tile->width;
            }
        }

        layoutOffset += Vec2D(0, mTileHeight);
    };
    fileLoader.AddCommand(layoutCommand);

    Command bonusItemCommand;
    bonusItemCommand.command = "bonus_item";
    bonusItemCommand.parseFunc = [this](ParseFuncParams params) {

        BonusItemLevelProperties property;
        mBonusItemProperties.push_back(property);
    };
    fileLoader.AddCommand(bonusItemCommand);

    Command bonusItemSpriteNameCommand;
    bonusItemSpriteNameCommand.command = "bonus_item_sprite_name";
    bonusItemSpriteNameCommand.parseFunc = [this](ParseFuncParams params) {

        mBonusItemProperties.back().spriteName = FileCommandLoader::ReadString(params);
    };
    fileLoader.AddCommand(bonusItemSpriteNameCommand);

    Command bonusItemScoreCommand;
    bonusItemScoreCommand.command = "bonus_item_score";
    bonusItemScoreCommand.parseFunc = [this](ParseFuncParams params) {

        mBonusItemProperties.back().score = FileCommandLoader::ReadInt(params);

    };
    fileLoader.AddCommand(bonusItemScoreCommand);

    Command bonusItemBeginLevelCommand;
    bonusItemBeginLevelCommand.command = "bonus_item_begin_level";
    bonusItemBeginLevelCommand.parseFunc = [this](ParseFuncParams params) {

        mBonusItemProperties.back().begin = FileCommandLoader::ReadInt(params);

    };
    fileLoader.AddCommand(bonusItemBeginLevelCommand);

    Command bonusItemEndLevelCommand;
    bonusItemEndLevelCommand.command = "bonus_item_end_level";
    bonusItemEndLevelCommand.parseFunc = [this](ParseFuncParams params) {
        
        mBonusItemProperties.back().end = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(bonusItemEndLevelCommand);



        return fileLoader.LoadFile(levelPath);
}

PacmanLevel::Tile* PacmanLevel::GetTileForSymbol(const char& symbol)
{
    for (auto& tile : mTiles)
    {
        if (tile.symbol == symbol)
            return &tile;
    }

    return nullptr;
}

void PacmanLevel::ResetPellets()
{
    mPellets.clear();

    const uint32_t PADDING = static_cast<uint32_t>(mTileHeight);
    const uint32_t LEVEL_HEIGHT = mLayoutOffset.GetY() + 32 * mTileHeight;

    uint32_t startingY = mLayoutOffset.GetY() + PADDING + mTileHeight - 1;
    uint32_t startingX = PADDING + 3;

    Pellet p;
    p.score = 10;
    uint32_t row = 0;

    for (uint32_t y = startingY; y < LEVEL_HEIGHT; y += PADDING, ++row)
    {
        for (uint32_t x = startingX, col = 0; x < SCREEN_WIDTH; x += PADDING, ++col)
        {
            if (row == 0 || col == 22)
            {
                if (col == 0 || col == 25)
                {
                    p.powerPellet = 1;
                    p.score = 50;
                    p.mBBox = AARectangle(Vec2D(x - 3, y - 3), mTileHeight, mTileHeight);
                    mPellets.push_back(p);

                    p.powerPellet = 0;
                    p.score = 10;

                    continue;
                }
            }

            AARectangle rect = AARectangle(Vec2D(x, y), p.PELLET_SIZE, p.PELLET_SIZE);
            bool found = false;

            for (const Excluder& wall : mWalls)
            {
                if (wall.GetAARectangle().Intersects(rect))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                for (const Tile& excludedPelletTile : mPelletExclusionTiles)
                {
                    if (excludedPelletTile.excludePelletTile)
                    {
                        AARectangle tileAABB(excludedPelletTile.position, excludedPelletTile.width, mTileHeight);

                        if (tileAABB.Intersects(rect))
                        {
                            found = true;
                            break;
                        }
                    }
                }
            }

            if (!found)
            {
                p.mBBox = rect;
                mPellets.push_back(p);
            }
        }
    }
}

void PacmanLevel::ResetLevel()
{
    ResetPellets();

    std::uniform_int_distribution<size_t> distribution(20, mPellets.size() - 50);
    mBonusItem.spawnTimes = static_cast<int>(distribution(mRandomGenerator));

    GetBonusItemSpriteName(mBonusItemSpriteName, mBonusItem.score);

    if (mnoptrPacman)
    {
        mnoptrPacman->MoveTo(mPacmanSpawnLocation);
        mnoptrPacman->ResetToFirstAnimation();
    }
}

bool PacmanLevel::HasEatenAllPellets() const
{
    return NumPelletsEaten() >= mPellets.size() - 4; //there are 4 super pellets, we dont count them to win
}

size_t PacmanLevel::NumPelletsEaten() const
{
    size_t numEaten{0};

    for (const auto& pellet : mPellets)
    {
        if (!pellet.powerPellet && pellet.eaten)
        {
            ++numEaten;
        }
    }
    return numEaten;
}

void PacmanLevel::GetBonusItemSpriteName(std::string& spriteName, uint32_t& score) const
{
    for (const auto& properties : mBonusItemProperties)
    {
        if (mCurrentLevel >= properties.begin && mCurrentLevel <= properties.end)
        {
            spriteName = properties.spriteName;
            score = properties.score;
            return;
        }
    }
}

void PacmanLevel::SpawnBonusItem()
{
    mBonusItem.spawned = 1;
    mBonusItem.eaten = 0;
}

bool PacmanLevel::ShouldSpawnBonusItem() const
{
    auto numEaten = NumPelletsEaten();

    /*return !mBonusItem.spawned && numEaten >= mBonusItem.spawnTimes;*/
    return true;
}



bool PacmanLevel::IsLevelOver() const
{
    return HasEatenAllPellets();
}

void PacmanLevel::IncreaseLevel()
{
    ++mCurrentLevel;

    if (mCurrentLevel > NUM_LEVELS)
    {
        ResetToFirstLevel();
    }

    ResetLevel();
}

void PacmanLevel::ResetToFirstLevel()
{
    mCurrentLevel = 1;
    ResetLevel();
}
