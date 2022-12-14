//=================================================================================
// Namespace		: Arcade_Game
// Name				: ArcadeScene.h
// Author			: Daniel Crespo Mu?oz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 21/09/2022 20:44:34
//=================================================================================

#ifndef _Arcade_Game_ArcadeScene_H_
#define _Arcade_Game_ArcadeScene_H_

#pragma once
#include "ButtonOptionsScene.h"
#include <memory>
#include "BMPImage.h"
#include "AnimatedSprite.h"


enum eGame
{
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class ArcadeScene: public ButtonOptionsScene
{
private:
	std::unique_ptr<Scene> GetScene(eGame game);

	//temp

	AnimatedSprite mAnimatedSprite;
	SpriteSheet mSpriteSheet;

protected:

public:
	ArcadeScene();
	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;
};
#endif // !_Arcade_Game_ArcadeScene_H_

