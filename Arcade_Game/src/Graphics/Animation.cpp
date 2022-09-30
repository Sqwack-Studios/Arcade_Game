#include "Animation.h"
#include "FileCommandLoader.h"

Animation::Animation():
    mSize(Vec2D::Zero),
    mSpriteSheetName(""),
    mAnimationName(""),
    mFPS(0)
{
}

std::vector<Animation> Animation::LoadAnimations(const std::string& animationFilePath)
{
    std::vector<Animation> animations;

    FileCommandLoader fileLoader;

    Command animationCommand;
    animationCommand.command = "animation";
    animationCommand.parseFunc = [&](ParseFuncParams params) {

        Animation newAnimation;

        newAnimation.mAnimationName = FileCommandLoader::ReadString(params);
        animations.push_back(newAnimation);
    };
    fileLoader.AddCommand(animationCommand);

    Command spriteSheetCommand;
    spriteSheetCommand.command = "sprite_sheet";
    spriteSheetCommand.parseFunc = [&](ParseFuncParams params) {

        animations.back().mSpriteSheetName = FileCommandLoader::ReadString(params);
    };
    fileLoader.AddCommand(spriteSheetCommand);

    Command sizeCommand;
    sizeCommand.command = "size";
    sizeCommand.parseFunc = [&](ParseFuncParams params) {

        animations.back().mSize = FileCommandLoader::ReadSize(params);
    };
    fileLoader.AddCommand(sizeCommand);

    Command fpsCommand;
    fpsCommand.command = "fps";
    fpsCommand.parseFunc = [&](ParseFuncParams params) {

        animations.back().mFPS = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(fpsCommand);

    Command frameKeysCommand;
    frameKeysCommand.command = "frame_keys";
    frameKeysCommand.commandType = COMMAND_MULTI_LINE;
    frameKeysCommand.parseFunc = [&](ParseFuncParams params)
    {
        animations.back().AddFrame(params.line);
    };
    fileLoader.AddCommand(frameKeysCommand);

    Command overlayCommand;
    overlayCommand.command = "overlay";
    overlayCommand.parseFunc = [&](ParseFuncParams params)
    {
        animations.back().mOverlay = FileCommandLoader::ReadString(params);
    };
    fileLoader.AddCommand(overlayCommand);

    Command frameColorsCommand;
    frameColorsCommand.command = "frame_colors";
    frameColorsCommand.commandType = COMMAND_MULTI_LINE;
    frameColorsCommand.parseFunc = [&](ParseFuncParams params) {

        animations.back().AddFrameColor(FileCommandLoader::ReadColor(params));
    };
    fileLoader.AddCommand(frameColorsCommand);

    Command overlayFrameColorsCommand;
    overlayFrameColorsCommand.command = "overlay_colors";
    overlayFrameColorsCommand.commandType = COMMAND_MULTI_LINE;
    overlayFrameColorsCommand.parseFunc = [&](ParseFuncParams params) {

        animations.back().AddOverlayFrameColor(FileCommandLoader::ReadColor(params));
    };
    fileLoader.AddCommand(overlayFrameColorsCommand);

    Command frameOffsetsCommand;
    frameOffsetsCommand.command = "frame_offsets";
    frameOffsetsCommand.commandType = COMMAND_MULTI_LINE;
    frameOffsetsCommand.parseFunc = [&](ParseFuncParams params) {

        animations.back().AddFrameOffset(FileCommandLoader::ReadSize(params));
    };
    fileLoader.AddCommand(frameOffsetsCommand);

    fileLoader.LoadFile(animationFilePath);

    
    return animations;
}

AnimationFrame Animation::GetAnimationFrame(uint32_t frameNum) const
{
    AnimationFrame frame;

    if (frameNum > mFrameNames.size())
    {
        return frame;
    }

    frame.frame = mFrameNames[frameNum];

    if (frameNum < mFrameColors.size())
    {
        frame.frameColor = mFrameColors[frameNum];
        frame.frameColorSet = true;
    }

    if (mOverlay.size() > 0)
    {
        frame.overlay = mOverlay;
    }

    if (frameNum < mOverlayColors.size())
    {
        frame.overlayColor = mOverlayColors[frameNum];
    }

    if (frameNum < mFrameOffsets.size())
    {
        frame.offSet = mFrameOffsets[frameNum];
    }

    frame.size = mSize;

    return frame;
}
