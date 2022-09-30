#include "Animation.h"

Animation::Animation():
    mSize(Vec2D::Zero),
    mSpriteSheetName(""),
    mAnimationName(""),
    mFPS(0)
{
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
    return AnimationFrame();
}
