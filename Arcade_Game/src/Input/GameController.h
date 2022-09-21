//=================================================================================
// Namespace		: Arcade_Game
// Name				: GameController.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 21/09/2022 22:40:30
//=================================================================================

#ifndef _Arcade_Game_GameController_H_
#define _Arcade_Game_GameController_H_

#pragma once
#include "InputAction.h"
#include <vector>

class GameController
{
private:
	std::vector<ButtonAction> mButtonAction;
protected:

public:
	GameController();
	InputAction GetActionForKey(InputKey key);
	void AddInputActionForKey(const ButtonAction& buttonAction);
	void ClearAll();


	//SDL wrapping
	static bool IsPressed(InputState state);
	static bool IsReleased(InputState state);
	static InputKey ActionKey();
	static InputKey CancelKey();
	static InputKey LeftKey();
	static InputKey RightKey();
	static InputKey UpKey();
	static InputKey DownKey();
};
#endif // !_Arcade_Game_GameController_H_

