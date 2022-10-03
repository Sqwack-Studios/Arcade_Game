//=================================================================================
// Namespace		: Arcade_Game
// Name				: Actor.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 03/10/2022 13:54:33
//=================================================================================

#ifndef _Arcade_Game_Actor_H_
#define _Arcade_Game_Actor_H_

#pragma once
#include "Vec2D.h"
#include "PacmanGameUtils.h"
#include "AnimatedSprite.h"
#include "AARectangle.h"

class Screen;



class Actor
{
private:
	Vec2D mDelta;
	PacmanMovement mMovementDirection;
	uint32_t mMovementSpeed;
	bool mUpdateSpriteOnUpdate;
protected:

	inline void ResetDelta() { mDelta = Vec2D::Zero; }
	inline void SetMovementSpeed(const uint32_t& movementSpeed) { mMovementSpeed = movementSpeed; }

	void Play(const std::string& animationName, bool looped);

	AnimatedSprite mSprite;

public:

	virtual void Init(
		const SpriteSheet& spriteSheet, 
		const std::string& animationsPath, 
		const Vec2D& initialPos, 
		const uint32_t& movementSpeed, 
		bool updateSpriteOnMovement, 
		const Color& spriteColor = Color::White()
					) = 0;

	virtual void Update(const uint32_t& deltaTime);
	virtual void Draw(Screen& screen);

	virtual void Stop();
	AARectangle GetEatingBoundingBox() const;

	inline bool IsFinishedAnimation() const { return mSprite.IsFinishedPlayingAnimation(); }
	inline const AARectangle GetBoundingBox() const { return mSprite.GetBoundingBox(); }
	inline void MoveBy(const Vec2D& delta) { return mSprite.MoveBy(delta); }
	inline void MoveTo(const Vec2D& position) { return mSprite.SetPosition(position); }
	inline Vec2D Position() const { return mSprite.Position(); }
	inline PacmanMovement GetMovementDirection() const { return mMovementDirection; }
	inline const Color& GetSpriteColor() const { return mSprite.GetColor(); }
	virtual inline void SetMovementDirection(PacmanMovement direction) { mMovementDirection = direction; }





};
#endif // !_Arcade_Game_Actor_H_

