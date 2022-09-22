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
	std::vector<ButtonAction> mButtonActions;
	std::vector<MouseButtonAction> mMouseButtonActions;

	MouseMovedAction mMouseMovedAction;
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

	inline const MouseMovedAction& GetMouseMovedAction() { return mMouseMovedAction; }
	inline void SetMouseMovedAction(const MouseMovedAction& mouseMovedAction) { mMouseMovedAction = mouseMovedAction; }

	MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
	void AddMouseButtonAction(const MouseButtonAction& mouseButtonAction);

	static MouseButton LeftMouseButton();
	static MouseButton RightMouseButton();

};
#endif // !_Arcade_Game_GameController_H_

