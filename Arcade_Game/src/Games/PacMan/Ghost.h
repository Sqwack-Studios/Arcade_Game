//=================================================================================
// Namespace		: Arcade_Game
// Name				: Ghost.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 04/10/2022 16:33:48
//=================================================================================

#ifndef _Arcade_Game_Ghost_H_
#define _Arcade_Game_Ghost_H_

#pragma once
#include "Actor.h"

enum GhostNames
{
	BLINKY = 0,
	PINKY,
	INKY,
	CLYDE,
	NUM_GHOSTS
};

enum GhostState
{
	GHOST_STATE_ALIVE = 0,
	GHOST_STATE_VULNERABLE,
	GHOST_STATE_VULNERABLE_ENDING,
	GHOST_STATE_DEAD
};


class Ghost: public Actor
{
private:
	void SetGhostState(const GhostState& state);



	uint32_t mVulnerabilityTimer;
	uint32_t mPoints;
	GhostState mState;
	bool mCanChangeDirection;
	Vec2D mInitialPosition;
protected:

public:

	Ghost();
	virtual void Init(
		const SpriteSheet& spriteSheet,
		const std::string& animationsPath,
		const Vec2D& initialPos,
		const uint32_t& movementSpeed,
		bool updateSpriteOnMovement,
		const Color& spriteColor = Color::White()
	) override;

	virtual void Update(const uint32_t& deltaTime) override;
	virtual void Draw(Screen& screen) override;
	
	virtual void StopAnimation() override;
	virtual void SetMovementDirection(const PacmanMovement& direction) override;


	void EatenByPacman();
	void ResetToFirstPosition();
	void SetStateToVulnerable();

	inline bool IsDead() const { return mState == GHOST_STATE_DEAD; }
	inline bool IsVulnerable() const { return mState == GHOST_STATE_VULNERABLE || mState == GHOST_STATE_VULNERABLE_ENDING; }
	inline bool IsAlive() const { return mState == GHOST_STATE_ALIVE; }
	inline uint32_t GetPoints() const { return mPoints; }
	inline void LockCanChangeDirection() { mCanChangeDirection = false; }

	static const uint32_t VULNERABILITY_TIME = 6000;
	static const uint32_t VULNERABILITY_ENDING_TIME = 4000;

};
#endif // !_Arcade_Game_Ghost_H_

