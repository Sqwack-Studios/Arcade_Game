#include "Actor.h"
#include "Utils.h"
#include <cmath>



void Actor::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, const uint32_t& movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor)
{
    mMovementDirection = PACMAN_MOVEMENT_NONE;
    mSprite.Init(animationsPath, spriteSheet, spriteColor);
    mUpdateSpriteOnUpdate = updateSpriteOnMovement;
    mMovementSpeed = movementSpeed;
    mDelta = Vec2D::Zero;
}

void Actor::Update(const uint32_t& deltaTime)
{
    if (mMovementDirection != PACMAN_MOVEMENT_NONE)
    {
        Vec2D delta{ Vec2D::Zero };

        delta = GetMovementVector(mMovementDirection) * mMovementSpeed;

        mDelta += delta * MillisecondsToSeconds(deltaTime);

        //we move by integer values only. 
        //we accumulate "amount to move" in the delta and extract integers through casting 
        if (IsGreaterThanOrEqual(fabs(mDelta.GetX()), 1.f))
        {
            int dx = static_cast<int>(fabs(mDelta.GetX()));

            if (mDelta.GetX() < 0)
            {
                mSprite.MoveBy(Vec2D(-dx, 0));
                mDelta.SetX(mDelta.GetX() + dx);
            }
            else
            {
                mSprite.MoveBy(Vec2D(dx, 0));
                mDelta.SetX(mDelta.GetX() - dx);
            }
        }
        else if(IsGreaterThanOrEqual(fabs(mDelta.GetY()), 1.f))
        {
            int dy = static_cast<int>(fabs(mDelta.GetY()));

            if (mDelta.GetY() < 0)
            {
                mSprite.MoveBy(Vec2D(0, -dy));
                mDelta.SetY(mDelta.GetY() + dy);
            }
            else
            {
                mSprite.MoveBy(Vec2D(0, dy));
                mDelta.SetY(mDelta.GetY() - dy);
            }
        }

        mSprite.Update(deltaTime);
    }

    if (mUpdateSpriteOnUpdate && mMovementDirection == PACMAN_MOVEMENT_NONE)
    {
        mSprite.Update(deltaTime);
    }
}

void Actor::Draw(Screen& screen)
{
    mSprite.Draw(screen);
}

void Actor::PlayAnimation(const std::string& animationName, bool looped)
{
    mSprite.PlayAnimation(animationName, looped);
}

void Actor::StopAnimation()
{
    SetMovementDirection(PACMAN_MOVEMENT_NONE);
    mSprite.StopAnimation();
}

AARectangle Actor::GetEatingBoundingBox() const
{
    return AARectangle::Inset(GetBoundingBox(), Vec2D(3, 3));
}
