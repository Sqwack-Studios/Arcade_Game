#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer():
    mTime(0),
    mCurrentAnimation(0),
    mFrame(0),
    mLooped(false),
    mIsPlaying(false),
    mIsFinishedPlaying(false)
{
}

bool AnimationPlayer::Init(const std::string& animationPath)
{
    mAnimations = Animation::LoadAnimations(animationPath);

    return mAnimations.size() > 0;
}


void AnimationPlayer::Update(uint32_t deltaTime)
{
    if (mIsPlaying)
    {
        mTime += deltaTime;

        int fps = mAnimations[mCurrentAnimation].mFPS;

        float millisecondsPerFrame = static_cast<float>(1000) / static_cast<float>(fps);

        if (static_cast<float>(mTime) > millisecondsPerFrame)
        {
            mTime -= static_cast<uint32_t>(millisecondsPerFrame);

            if (mFrame + 1 < mAnimations[mCurrentAnimation].mFrameNames.size())
            {
                mFrame++;
            }
            else if (mLooped)
            {
                mFrame = 0;
            }
            else
            {
                mIsFinishedPlaying = true;
            }
        }
    }
}

bool AnimationPlayer::PlayAnimation(const std::string& animationName, const bool& looped)
{
    bool found{ false };

    for (size_t i = 0; i < mAnimations.size(); i++)
    {
        if (mAnimations[i].mAnimationName == animationName)
        {
            mCurrentAnimation = i;
            found = true;
            break;
        }
    }

    
     mIsPlaying = found;
     mFrame = 0;
     mTime = 0;
     mLooped = looped;
     mIsFinishedPlaying = !found;

    return found;
}

void AnimationPlayer::PauseAnimation()
{
    if (!mIsFinishedPlaying)
    {
        mIsPlaying = false;
    }
}

void AnimationPlayer::ResumeAnimation()
{
    if (!mIsFinishedPlaying)
    {
        mIsPlaying = true;
    }
}

void AnimationPlayer::StopAnimation()
{
    mIsPlaying = false;
    mTime = 0;
    mFrame = 0;
    mIsFinishedPlaying = true;
}



AnimationFrame AnimationPlayer::GetCurrentAnimationFrame() const
{
    if (mAnimations.empty())
    {
        return AnimationFrame();
    }

    return mAnimations[mCurrentAnimation].GetAnimationFrame(GetCurrentFrameNumber());
}
