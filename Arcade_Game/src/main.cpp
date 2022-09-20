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
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"


const int SCREEN_WIDTH = 250;
const int SCREEN_HEIGHT = 250;
const int MAGNIFICATION = 3;
int deltaTime = 0;
int currentTime = 0;


int main(int arg, char *argv[])
{	

	Screen theScreen;
	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	Vec2D center = Vec2D::CentreScreen();
	theScreen.Draw(center, Color::Yellow());


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
	Vec2D vert3(140,50);

	Triangle cipoteAlado(vert1, vert2, vert3);
	AARectangle rect(vert3, 100, 50);
	Circle circle(Vec2D::CentreScreen(), 80);
	theScreen.Draw(circle, Color::Green(), true);
	theScreen.Draw(rect, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
	/*theScreen.Draw(cipoteAlado, Color::Red(), true);*/
	//theScreen.Draw(star.SendToBuffer(), Color::Red());
	theScreen.SwapScreen();
	SDL_Event sdlEvent;
	bool running = true;

	while (running)
	{
		deltaTime = SDL_GetTicks() - currentTime;
		currentTime = SDL_GetTicks();

		star.Update(deltaTime);
		star2.Update(deltaTime);
		star3.Update(deltaTime);

		
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



	theScreen.~Screen();

	return 0;
}



