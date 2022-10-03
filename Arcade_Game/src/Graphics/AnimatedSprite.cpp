#include "AnimatedSprite.h"
#include "AARectangle.h"
#include "Screen.h"

AnimatedSprite::AnimatedSprite():
    mPosition(Vec2D::Zero),
    mnoptrSpriteSheet(nullptr)
{
}

void AnimatedSprite::Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color)
{
    mAnimationPlayer.Init(animationsPath);
    mnoptrSpriteSheet = &spriteSheet;
    mColor = color;
}

void AnimatedSprite::Update(uint32_t deltaTime)
{
    mAnimationPlayer.Update(deltaTime);
}

void AnimatedSprite::Draw(Screen& theScreen)
{
    AnimationFrame frame = mAnimationPlayer.GetCurrentAnimationFrame();
    Color frameColor{ frame.frameColor };

    if (!frame.frameColorSet)
    {
        frameColor = mColor;
    }

    theScreen.Draw(*mnoptrSpriteSheet, frame.frame, mPosition + frame.offSet, frameColor);

    if (frame.overlay.size() > 0)
    {
        theScreen.Draw(*mnoptrSpriteSheet, frame.overlay, mPosition, frame.overlayColor);
    }
}

void AnimatedSprite::PlayAnimation(const std::string& animationName, bool looped)
{
    mAnimationPlayer.PlayAnimation(animationName, looped);
}

Vec2D AnimatedSprite::Size() const
{
    return mAnimationPlayer.GetCurrentAnimationFrame().size;
}

void AnimatedSprite::PauseAnimation()
{
    mAnimationPlayer.PauseAnimation();
}

void AnimatedSprite::ResumeAnimation()
{
    mAnimationPlayer.ResumeAnimation();
}

void AnimatedSprite::StopAnimation()
{
    mAnimationPlayer.StopAnimation();
}

const AARectangle AnimatedSprite::GetBoundingBox() const
{
    AARectangle bbox{ mPosition,static_cast<unsigned int>(Size().GetX()), static_cast<unsigned int>(Size().GetY()) };

    return bbox;
}
