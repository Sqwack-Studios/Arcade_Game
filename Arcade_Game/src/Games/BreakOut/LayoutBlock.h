//=================================================================================
// Namespace		: Arcade_Game
// Name				: LayoutBlock.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 27/09/2022 16:56:32
//=================================================================================

#ifndef _Arcade_Game_LayoutBlock_H_
#define _Arcade_Game_LayoutBlock_H_

#pragma once
#include "Color.h"

struct LayoutBlock
{
	char symbol = '-';
	int hp = 0;
	Color color = Color::Black();
};
#endif // !_Arcade_Game_LayoutBlock_H_

