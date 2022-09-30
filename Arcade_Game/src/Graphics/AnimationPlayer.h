//=================================================================================
// Namespace		: Arcade_Game
// Name				: AnimationPlayer.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 30/09/2022 14:48:32
//=================================================================================

#ifndef _Arcade_Game_AnimationPlayer_H_
#define _Arcade_Game_AnimationPlayer_H_

#pragma once
#include "Animation.h"
#include <stdint.h>

class AnimationPlayer
{
private:
	uint32_t mTime;
	std::vector<Animation> mAnimations;
	size_t mCurrentAnimation;
	uint32_t mFrame;

	bool mLooped;
	bool mIsPlaying;
	bool mIsFinishedPlaying;
protected:

public:

	AnimationPlayer();
	bool Init(const std::string& animationPath);
	bool Play(const std::string& animationName, const bool& looped);
	void Pause();
	void Resume();
	void Stop();
	void Update(uint32_t deltaTime);
	AnimationFrame GetCurrentAnimationFrame() const;

	inline bool IsFinishedPlaying() const { return mIsFinishedPlaying; }
	inline uint32_t GetCurrentFrameNumber() const { return mFrame; }

	inline size_t GetNumOfAnimations() const { return mAnimations.size(); }
};
#endif // !_Arcade_Game_AnimationPlayer_H_

