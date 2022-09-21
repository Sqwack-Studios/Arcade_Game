//=================================================================================
// Namespace		: Arcade_Game
// Name				: App.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 21/09/2022 18:12:42
//=================================================================================

#ifndef _Arcade_Game_App_H_
#define _Arcade_Game_App_H_

#pragma once
#include "Screen.h"
#include <stdint.h>

struct SDL_Window;

class App
{
private:
	Screen mScreen;
	SDL_Window* mnoptrWindow; //Screen owns it

	uint32_t mWidth;
	uint32_t mHeight;

protected:

public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();

	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }
};
#endif // !_Arcade_Game_App_H_

