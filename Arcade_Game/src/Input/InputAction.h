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
using InputAction = std::function<void(uint32_t deltaTime, InputState)>;

struct ButtonAction
{
	InputKey key;
	InputAction action;
};

#endif // !_Arcade_Game_InputAction_H_

