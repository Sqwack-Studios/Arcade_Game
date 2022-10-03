//=================================================================================
// Namespace		: Arcade_Game
// Name				: PacmanStartScene.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 03/10/2022 11:26:17
//=================================================================================

#ifndef _Arcade_Game_PacmanStartScene_H_
#define _Arcade_Game_PacmanStartScene_H_

#pragma once
#include "ButtonOptionsScene.h"

class PacmanStartScene: public ButtonOptionsScene
{
private:

protected:

public:
	PacmanStartScene();

	virtual void Init() override;
	void Update(uint32_t deltaTime) override;
	void Draw(Screen& theScreen) override;
	const std::string& GetSceneName() const override;
};
#endif // !_Arcade_Game_PacmanStartScene_H_

