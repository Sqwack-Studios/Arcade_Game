#include "PacmanLevel.h"
#include "Screen.h"
#include "FileCommandLoader.h"
#include "Pacman.h"
#include <assert.h>



bool PacmanLevel::Init(const std::string& levelPath, Pacman* noptrPacman)
{
    mnoptrPacman = noptrPacman;
    return LoadLevel(levelPath);
}

void PacmanLevel::Update(uint32_t deltaTime)
{
    for (auto& wall : mWalls)
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
}

void PacmanLevel::Draw(Screen& theScreen)
{
    //debug for walls
 
    for (auto& wall : mWalls)
    {
        theScreen.Draw(wall.GetAARectangle(), Color::Blue());
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

                startingX += tile->width;
            }
        }

        layoutOffset += Vec2D(0, mTileHeight);
    };
    fileLoader.AddCommand(layoutCommand);

        return fileLoader.LoadFile(levelPath);
}

Tile* PacmanLevel::GetTileForSymbol(const char& symbol)
{
    for (auto& tile : mTiles)
    {
        if (tile.symbol == symbol)
            return &tile;
    }

    return nullptr;
}