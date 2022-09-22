//=================================================================================
// Namespace		: Arcade_Game
// Name				: InputController.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 22/09/2022 12:14:20
//=================================================================================

#ifndef _Arcade_Game_InputController_H_
#define _Arcade_Game_InputController_H_

#pragma once
#include "InputAction.h"

class GameController;

class InputController
{
private:
	InputAction mQuit;
	GameController* mnoptrCurrentController;
protected:

public:
	InputController();
	void Init(InputAction quitAction);
	void Update(uint32_t deltaTime);

	void SetGameController(GameController* controller);
};
#endif // !_Arcade_Game_InputController_H_

