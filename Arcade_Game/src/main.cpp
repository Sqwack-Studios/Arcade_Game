//=================================================================================
// Namespace		: Arcade_Game
// Name				: main.cpp
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 14/09/2022 20:41:00
//=================================================================================


#pragma once
#include <iostream>
#include <SDL.h>


#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Star2D.h"
#include "Utils.h"



const int SCREEN_WIDTH = 250;
const int SCREEN_HEIGHT = 250;
const int MAGNIFICATION = 4;



int main(int arg, char *argv[])
{	

	Screen theScreen;
	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	Vec2D center = Vec2D::CentreScreen();
	theScreen.Draw(center, Color::Yellow());


	Star2D star(Vec2D::CentreScreen(), 100, 30, 5, 0.0f);
	theScreen.Draw(star.SendToBuffer(), Color::Red());


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



