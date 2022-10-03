//=================================================================================
// Namespace		: Arcade_Game
// Name				: Pacman.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 03/10/2022 17:00:07
//=================================================================================

#ifndef _Arcade_Game_Pacman_H_
#define _Arcade_Game_Pacman_H_

#pragma once
#include "Actor.h"

class Screen;
class SpriteSheet;

class Pacman: public Actor
{
private:

	void AddToScore(const uint32_t& value);


	uint32_t mScore;
	uint32_t mGhostMultiplier;
	bool mIsDying; //dying animation


protected:

public:

	virtual void Init(
		const SpriteSheet& spriteSheet,
		const std::string& animationsPath,
		const Vec2D& initialPos,
		const uint32_t& movementSpeed,
		bool updateSpriteOnMovement,
		const Color& spriteColor = Color::White()		) override;

	virtual void Update(const uint32_t& deltaTime) override;
	virtual void SetMovementDirection(const PacmanMovement& movementDir) override;

	void ResetToFirstAnimation();
	void EatenByGhost();
	void ResetScore();
	void AteItem(const uint32_t& value);
	void AteGhost(const uint32_t& value);

	inline void ResetGhostEatenMultiplier() { mGhostMultiplier = 1; }
	inline const uint32_t& Score() const { return mScore; }
};
#endif // !_Arcade_Game_Pacman_H_

