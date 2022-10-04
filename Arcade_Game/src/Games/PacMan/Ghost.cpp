#include "Ghost.h"

namespace {

	const uint32_t NUM_POINTS_FOR_GHOST = 200;
}


Ghost::Ghost():
	mInitialPosition(Vec2D::Zero),
	mPoints(0)
{
}

void Ghost::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, const uint32_t& movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor)
{
	Actor::Init(spriteSheet, animationsPath, initialPos, movementSpeed, updateSpriteOnMovement, spriteColor);
	mInitialPosition = initialPos;
	mPoints = NUM_POINTS_FOR_GHOST;
	ResetToFirstPosition();
	
}

void Ghost::Update(const uint32_t& deltaTime)
{
	Vec2D position = Position();
	Actor::Update(deltaTime);

	mCanChangeDirection = position != Position();

	if (IsVulnerable())
	{
		mVulnerabilityTimer += deltaTime;
		if (mState == GHOST_STATE_VULNERABLE && mVulnerabilityTimer >= VULNERABILITY_TIME)
		{
			SetGhostState(GHOST_STATE_VULNERABLE_ENDING);

		}

		if (mState == GHOST_STATE_VULNERABLE_ENDING && mVulnerabilityTimer >= VULNERABILITY_ENDING_TIME)
		{
			SetGhostState(GHOST_STATE_ALIVE);
		}
	}
}

void Ghost::Draw(Screen& screen)
{
}

void Ghost::StopAnimation()
{
	SetMovementDirection(PACMAN_MOVEMENT_NONE);
}

void Ghost::SetMovementDirection(const PacmanMovement& direction)
{
	Actor::SetMovementDirection(direction);

	PacmanMovement movementDir = GetMovementDirection();

	if (mState == GHOST_STATE_ALIVE)
	{
		switch (movementDir)
		{
		case PACMAN_MOVEMENT_NONE:
			break;
		case PACMAN_MOVEMENT_UP:
			PlayAnimation("ghost_movement_up", true);
			break;
		case PACMAN_MOVEMENT_LEFT:
			PlayAnimation("ghost_movement_left", true);
			break;
		case PACMAN_MOVEMENT_DOWN:
			PlayAnimation("ghost_movement_down", true);
			break;
		case PACMAN_MOVEMENT_RIGHT:
			PlayAnimation("ghost_movement_right", true);
			break;
		default:
			break;
		}

	}
	else if (mState == GHOST_STATE_DEAD)
	{
		switch (movementDir)
		{
		case PACMAN_MOVEMENT_NONE:
			break;
		case PACMAN_MOVEMENT_UP:
			PlayAnimation("ghost_dead_up", true);
			break;
		case PACMAN_MOVEMENT_LEFT:
			PlayAnimation("ghost_dead_left", true);
			break;
		case PACMAN_MOVEMENT_DOWN:
			PlayAnimation("ghost_dead_down", true);
			break;
		case PACMAN_MOVEMENT_RIGHT:
			PlayAnimation("ghost_dead_right", true);
			break;
		default:
			break;
		}
	}

}

void Ghost::EatenByPacman()
{
	SetGhostState(GHOST_STATE_DEAD);
}

void Ghost::ResetToFirstPosition()
{
	mSprite.SetPosition(mInitialPosition);
	SetMovementDirection(PACMAN_MOVEMENT_NONE);
	mVulnerabilityTimer = 0;
	SetGhostState(GHOST_STATE_ALIVE);
	mCanChangeDirection = true;
}

void Ghost::SetStateToVulnerable()
{
	if (mState != GHOST_STATE_DEAD)
	{
		SetGhostState(GHOST_STATE_VULNERABLE);
	}
}

void Ghost::SetGhostState(const GhostState& state)
{
	mState = state;

	switch (mState)
	{
	case GHOST_STATE_ALIVE:
		SetMovementDirection(GetMovementDirection());
		SetMovementSpeed(GHOST_MOVEMENT_SPEED);
		break;
	case GHOST_STATE_VULNERABLE:
		mSprite.PlayAnimation("ghost_vulnerable", true);
		mVulnerabilityTimer = 0;
		SetMovementSpeed(GHOST_VULNERABLE_SPEED);
		break;
	case GHOST_STATE_VULNERABLE_ENDING:
		mSprite.PlayAnimation("ghost_vulnerable_ending", true);
		mVulnerabilityTimer = 0;
		break;
	case GHOST_STATE_DEAD:
		SetMovementDirection(GetMovementDirection());
		SetMovementSpeed(GHOST_BACK_TO_PEN_SPEED);
		break;
	default:
		break;
	}
}
