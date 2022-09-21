//=================================================================================
// Namespace		: Arcade_Game
// Name				: Scene.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 21/09/2022 20:28:41
//=================================================================================

#ifndef _Arcade_Game_Scene_H_
#define _Arcade_Game_Scene_H_

#pragma once
#include <string>
#include <stdint.h>
#include "GameController.h"
class Screen;

//Interface Scene Class
class Scene
{
private:

protected:
	GameController mGameController;

public:
	virtual ~Scene() {}
	virtual void Init() = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& theScreen) = 0;
	virtual const std::string& GetSceneName() const = 0;

	GameController* GetGameController() { return &mGameController; }
};
#endif // !_Arcade_Game_Scene_H_

