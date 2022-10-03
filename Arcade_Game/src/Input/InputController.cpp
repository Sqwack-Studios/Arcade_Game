#include "InputController.h"
#include "GameController.h"
#include <SDL.h>


InputController::InputController(): 
	mnoptrCurrentController(nullptr),
	mQuit(nullptr)
{
}

void InputController::Init(InputAction quitAction)
{
	mQuit = quitAction;
}

void InputController::Update(uint32_t deltaTime)
{
	SDL_Event sdlEvent;


	//*Functional aproach to the input controller "component" (e.g check Breakout::Init() implementation)
	//*Lambda functions implement the functionality(actions) per key, per scene.
	/////////////////
	//Another aproach would be to bind each key with a pointer referenced to a function...
	//this approach makes easier implementation for different mappings

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
				mQuit(deltaTime, SDL_PRESSED);
			case SDL_MOUSEMOTION:
				if (mnoptrCurrentController)
				{
					MouseMovedAction mouseMoved = mnoptrCurrentController->GetMouseMovedAction();
					if (mouseMoved)
					{
						MousePosition position;
						position.xPos = sdlEvent.motion.x;
						position.yPos = sdlEvent.motion.y;
						mouseMoved(position);
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				if (mnoptrCurrentController)
				{
					MouseInputAction action = mnoptrCurrentController->GetMouseButtonActionForMouseButton(static_cast<MouseButton>(sdlEvent.button.button));

					MousePosition position;
					position.xPos = sdlEvent.button.x;
					position.yPos = sdlEvent.button.y;

					action(static_cast<InputState>(sdlEvent.button.state), position);
				}
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if (mnoptrCurrentController)
				{
					InputAction action = mnoptrCurrentController->GetActionForKey(sdlEvent.key.keysym.sym);
					action(deltaTime, static_cast<InputState>(sdlEvent.key.state));
				}
				break;
			default:
				break;
		}
	}
}

void InputController::SetGameController(GameController* controller)
{
	mnoptrCurrentController = controller;
}
