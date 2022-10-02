//=================================================================================
// Namespace		: Arcade_Game
// Name				: AnimatedSprite.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 02/10/2022 12:41:28
//=================================================================================

#ifndef _Arcade_Game_AnimatedSprite_H_
#define _Arcade_Game_AnimatedSprite_H_

#pragma once
#include "AnimationPlayer.h"

class AARectangle;
class Screen;
class SpriteSheet;


class AnimatedSprite
{
private:

	const SpriteSheet* mnoptrSpriteSheet;
	AnimationPlayer mAnimationPlayer;
	Vec2D mPosition;
	Color mColor;

protected:

public:

	AnimatedSprite();
	void Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color = Color::White());

	void Update(uint32_t deltaTime);
	void Draw(Screen& theScreen);

	void Play(const std::string& animationName, bool looped);
	Vec2D Size() const;
	void Pause();
	void Resume();
	void Stop();
	const AARectangle GetBoundingBox() const;

	inline Vec2D Position() const { return mPosition; }
	inline void SetPosition(const Vec2D& position) { mPosition = position; }
	inline void MoveBy(const Vec2D& delta) { mPosition += delta; }
	inline bool IsFinishedPlayingAnimation() const { return mAnimationPlayer.IsFinishedPlaying(); }
	inline const Color& GetColor() const { return mColor; }
	const SpriteSheet* GetSpriteSheet() const { return mnoptrSpriteSheet; }
};
#endif // !_Arcade_Game_AnimatedSprite_H_

