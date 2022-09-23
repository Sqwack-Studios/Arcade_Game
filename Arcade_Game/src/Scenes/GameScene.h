//=================================================================================
// Namespace		: Arcade_Game
// Name				: GameScene.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 22/09/2022 13:50:53
//=================================================================================

#ifndef _Arcade_Game_GameScene_H_
#define _Arcade_Game_GameScene_H_

#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>




class GameScene: public Scene
{
private:
	std::unique_ptr<Game> mGame;
protected:

public:
	GameScene(std::unique_ptr<Game> optrGame);
	virtual ~GameScene() {}
	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetSceneName() const override;
};
#endif // !_Arcade_Game_GameScene_H_

