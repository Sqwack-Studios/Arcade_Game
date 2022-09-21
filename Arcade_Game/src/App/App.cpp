#include "App.h"
#include <SDL.h>

#include "Vec2D.h"
#include "Line2D.h"
#include "Color.h"
#include "Utils.h"

#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"
#include "Star2D.h"


App& App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
    mnoptrWindow = mScreen.Init(width, height, mag);

    return mnoptrWindow != nullptr;
}

void App::Run()
{
	if (!mnoptrWindow)
		return;

	Star2D star(Vec2D::CentreScreen(), 60, 30, 5, 0.0f);
	star.SetIsRotating(true);
	star.SetRotationRate(-2 * PI * 120 / 360);


	SDL_Event sdlEvent;
	bool running = true;

	uint32_t lastTick{ SDL_GetTicks() };
	uint32_t currentTick {lastTick};

	uint32_t deltaTime{ 10 };
	uint32_t accumulator{ 0 };

	while (running)
	{
		currentTick = SDL_GetTicks();
		uint32_t frameTime = currentTick - lastTick;

		if (frameTime > 300)
		{
			frameTime = 300;
		}

		lastTick = currentTick;
		accumulator += frameTime;


		//Input
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		//Update state
		while (accumulator >= deltaTime)
		{
			//update current scene by deltaTime
			star.Update(deltaTime);

			accumulator -= deltaTime;
		}

		//Render

		mScreen.Draw(star.SendToBuffer(), Color::Blue());
		mScreen.SwapScreen();
	}

	mScreen.~Screen();
}
