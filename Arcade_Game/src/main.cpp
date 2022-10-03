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

#include "DynamicIntArray.h"
#include "App.h"


const int SCREEN_WIDTH = 225;
const int SCREEN_HEIGHT = 300;
const int MAGNIFICATION = 3;


void Consume(DynamicIntArray movedArray)
{
	std::cout << "---------------------------------------" << std::endl;
	std::cout << "Moved array : " << std::endl;
	movedArray.Display();

	std::cout << "---------------------------------------" << std::endl;
}

int main(int arg, char *argv[])
{	

	if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION))
	{
		App::Singleton().Run();
	}

	///DynamicArray MOVE SEMANTIC TESTS

	//DynamicIntArray arrayA;
	//DynamicIntArray arrayB;
	//arrayB.Init();
	//std::cout << arrayB.Capacity();
	//int length = arrayB.Capacity() * 2;
	//
	//for (size_t i = 0; i < length; i++)
	//{
	//	arrayB.PushBack(i);
	//}
	//arrayB.Display();

	////Consume(std::move(arrayB));
	//arrayA = std::move(arrayB);

	//arrayA.Display();
	//std::cout << "hehe";
	//arrayB.Display();
	 
	///



	return 0;
}



