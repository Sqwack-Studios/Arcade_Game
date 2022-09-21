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

	Vec2D center = Vec2D::CentreScreen();
	mScreen.Draw(center, Color::Yellow());


	Star2D star(Vec2D::CentreScreen(), 60, 60, 28, 0.0f);
	Star2D star2(Vec2D::CentreScreen(), 100, 30, 25, PI / 2);
	Star2D star3(Vec2D::CentreScreen(), 100, 30, 25, PI / 4);

	star.SetIsRotating(true);
	star2.SetIsRotating(true);
	star3.SetIsRotating(true);

	star.SetRotationRate(-2 * PI * 60 / 360);
	star2.SetRotationRate(-2 * PI * 20 / 360);
	star3.SetRotationRate(-2 * PI * 40 / 360);

	Vec2D vert1(Vec2D::CentreScreen());
	Vec2D vert2(170, 125);
	Vec2D vert3(140, -50);

	Triangle cipoteAlado(vert1, vert2, vert3);
	AARectangle rect(vert3, 100, 50);
	Circle circle(Vec2D::CentreScreen(), 90);
	mScreen.Draw(circle, Color::Green(), true);
	mScreen.Draw(rect, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
	mScreen.Draw(cipoteAlado, Color::Red(), true, Color::Pink());
	//theScreen.Draw(star.SendToBuffer(), Color::Red());
	mScreen.SwapScreen();
	SDL_Event sdlEvent;
	bool running = true;

	while (running)
	{
		//deltaTime = SDL_GetTicks() - currentTime;
		//currentTime = SDL_GetTicks();

		//star.Update(deltaTime);
		//star2.Update(deltaTime);
		//star3.Update(deltaTime);


		//theScreen.Draw(star2.SendToBuffer(), Color::Blue());
		//theScreen.Draw(star3.SendToBuffer(), Color::Green());



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

	mScreen.~Screen();
}
