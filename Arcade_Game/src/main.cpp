#include <iostream>
#include <SDL.h>
#include "Vec2D.h"
#include "DynamicIntArray.h"

int main(int arg, char *argv[])
{	
	Vec2D gordo(32,45);
	Vec2D cipote;

	cipote = 4 * gordo;

	std::cout << -gordo;
	std::cout << cipote;
	
	return 0;
}