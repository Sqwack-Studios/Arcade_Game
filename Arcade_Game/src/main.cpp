//=================================================================================
// Namespace		: Arcade_Game
// Name				: main.cpp
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 14/09/2022 20:41:00
//=================================================================================


#include <iostream>
#include <SDL.h>
#include "Vec2D.h"
#include "Color.h"
#include "ScreenBuffer.h"
#include "Screen.h"

const int SCREEN_WIDTH = 250;
const int SCREEN_HEIGHT = 250;
const int MAGNIFICATION = 3;



int main(int arg, char *argv[])
{	

	Screen theScreen;
	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	theScreen.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::Yellow());
	theScreen.SwapScreen();

	SDL_Event sdlEvent;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}



	theScreen.~Screen();

	return 0;
}



