#include "App.h"
#include "SpriteSheet.h"
#include "FileCommandLoader.h"
#include "Utils.h"


SpriteSheet::SpriteSheet()
{

}

std::vector<std::string> SpriteSheet::SpriteNames() const
{
    std::vector<std::string> spriteNames;

    for (const auto& section : mSections)
    {
        spriteNames.push_back(section.key);
    }
    return spriteNames;
}

bool SpriteSheet::LoadSpriteSections(const std::string& path)
{
    FileCommandLoader fileLoader;

    Command spriteCommand;
    spriteCommand.command = "sprite";
    spriteCommand.parseFunc = [&](ParseFuncParams params){

        BMPImageSection section;
        mSections.push_back(section);
    };
    fileLoader.AddCommand(spriteCommand);

    Command keyCommand;
    keyCommand.command = "key";
    keyCommand.parseFunc = [&](ParseFuncParams params){

        mSections.back().key = FileCommandLoader::ReadString(params);
    };
    fileLoader.AddCommand(keyCommand);

    Command xPosCommand;
    xPosCommand.command = "xPos";
    xPosCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.xPos = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(xPosCommand);

    Command yPosCommand;
    yPosCommand.command = "yPos";
    yPosCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.yPos = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(yPosCommand);

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.width = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.height = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(heightCommand);

    return fileLoader.LoadFile(path);
}

bool SpriteSheet::Load(const std::string& name)
{
    bool loadedImage = mBMPImage.Load(App::GetBasePath() + std::string("Assets/") + name + ".bmp");
    bool loadedSpriteSection = LoadSpriteSections(App::GetBasePath() + std::string("Assets/") + name + ".txt");

    return loadedImage && loadedSpriteSection;
}

Sprite SpriteSheet::GetSprite(const std::string& spriteName) const
{
    for (const auto& section : mSections)
    {
        if (StringCompare(section.key, spriteName))
        {
            return section.sprite;
        }
    }

    return Sprite();
}
