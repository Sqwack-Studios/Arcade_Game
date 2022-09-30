//=================================================================================
// Namespace		: Arcade_Game
// Name				: NotImplementedScene.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 30/09/2022 11:40:25
//=================================================================================

#ifndef _Arcade_Game_NotImplementedScene_H_
#define _Arcade_Game_NotImplementedScene_H_

#pragma once
#include "Scene.h"

class NotImplementedScene: public Scene
{
private:

protected:

public:

	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;



};
#endif // !_Arcade_Game_NotImplementedScene_H_

