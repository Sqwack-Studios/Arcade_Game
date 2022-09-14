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

const int SCREEN_WIDTH = 250;
const int SCREN_HEIGHT = 250;



int main(int arg, char *argv[])
{	

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init Failed" << std::endl;
		return 1;
	}

	SDL_Window* optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREN_HEIGHT, 0);

	if (optrWindow == nullptr)
	{
		std::cout << "Could not create window, got error: " << SDL_GetError() << std::endl;
	}

	SDL_Surface* noptrWindowSurface = SDL_GetWindowSurface(optrWindow);
	

	SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	
	Color::InitColorFormat(pixelFormat);
	ScreenBuffer screenBuffer;
	
	screenBuffer.Init(pixelFormat->format, noptrWindowSurface->w, noptrWindowSurface->h);
	screenBuffer.SetPixel(Color::Red(), SCREEN_WIDTH / 2, SCREN_HEIGHT / 2);

	
	SDL_BlitSurface(screenBuffer.GetSurface(), nullptr, noptrWindowSurface, nullptr);





	uint32_t color = 0xFF0000;


	SDL_UpdateWindowSurface(optrWindow);

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



	SDL_DestroyWindow(optrWindow);
	SDL_Quit();

	return 0;
}



