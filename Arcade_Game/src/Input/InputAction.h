//=================================================================================
// Namespace		: Arcade_Game
// Name				: InputAction.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 21/09/2022 22:37:02
//=================================================================================

#ifndef _Arcade_Game_InputAction_H_
#define _Arcade_Game_InputAction_H_

#pragma once
#include <functional>
#include <stdint.h>

using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;


using InputAction = std::function<void(uint32_t deltaTime, InputState)>;


struct ButtonAction
{
	InputKey key;
	InputAction action;
};


struct MousePosition
{
	int32_t xPos, yPos;

};

using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition& position)>;

struct MouseButtonAction
{
	MouseButton mouseButton;
	MouseInputAction mouseInputAction;
};

#endif // !_Arcade_Game_InputAction_H_

