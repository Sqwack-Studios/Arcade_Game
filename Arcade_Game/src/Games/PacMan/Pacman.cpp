#include "Pacman.h"


void Pacman::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, const uint32_t& movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor)
{
	Actor::Init(spriteSheet, animationsPath, initialPos, movementSpeed, false);

	ResetToFirstAnimation();
	ResetScore();
	ResetGhostEatenMultiplier();
	mIsDying = false;
	
}

void Pacman::Update(const uint32_t& deltaTime)
{
	if (mIsDying)
	{
		mSprite.Update(deltaTime);
		mIsDying = !IsFinishedAnimation();
		return;
	}

	Actor::Update(deltaTime);
}

void Pacman::SetMovementDirection(const PacmanMovement& movementDir)
{
	PacmanMovement currentDirection = GetMovementDirection();

	if (movementDir == PACMAN_MOVEMENT_LEFT && currentDirection != PACMAN_MOVEMENT_LEFT)
	{
		PlayAnimation("move_left", true);
	}
	else if (movementDir == PACMAN_MOVEMENT_RIGHT && currentDirection != PACMAN_MOVEMENT_RIGHT)
	{
		PlayAnimation("move_right", true);
	}
	else if (movementDir == PACMAN_MOVEMENT_DOWN && currentDirection != PACMAN_MOVEMENT_DOWN)
	{
		PlayAnimation("move_down", true);
	}
	else if (movementDir == PACMAN_MOVEMENT_UP && currentDirection != PACMAN_MOVEMENT_UP)
	{
		PlayAnimation("move_up", true);
	}

	/*ResetDelta();*/


	Actor::SetMovementDirection(movementDir);
}

void Pacman::ResetToFirstAnimation()
{
	PlayAnimation("move_left", true);
	StopAnimation();
}

void Pacman::EatenByGhost()
{
	PlayAnimation("death", false);
	mIsDying = true;
	ResetGhostEatenMultiplier();
}

void Pacman::ResetScore()
{
	mScore = 0;
}

void Pacman::AddToScore(const uint32_t& value)
{
	mScore += value;
}

void Pacman::AteItem(const uint32_t& value)
{
	AddToScore(value);
}

void Pacman::AteGhost(const uint32_t& value)
{
	AddToScore(value * mGhostMultiplier);
	mGhostMultiplier *= 2;
}
