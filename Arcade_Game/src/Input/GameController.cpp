#include "GameController.h"
#include <SDL.h>

GameController::GameController()
{
}

InputAction GameController::GetActionForKey(InputKey key)
{
    for (const ButtonAction& buttonAction : mButtonAction)
    {
        if (buttonAction.key == key  )
        {
            return buttonAction.action;
        }
    }
    //return "nothing" if the key is not found 
    return [](uint32_t, InputState){};
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
    mButtonAction.push_back(buttonAction);
}

void GameController::ClearAll()
{
    mButtonAction.clear();
}

//SDL wrapping
bool GameController::IsPressed(InputState state)
{
    return state == SDL_PRESSED;
}

bool GameController::IsReleased(InputState state)
{
    return state == SDL_RELEASED;
}

InputKey GameController::ActionKey()
{
    return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::CancelKey()
{
    return static_cast<InputKey>(SDLK_s);
}

InputKey GameController::LeftKey()
{
    return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameController::RightKey()
{
    return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameController::UpKey()
{
    return static_cast<InputKey>(SDLK_UP);
}

InputKey GameController::DownKey()
{
    return static_cast<InputKey>(SDLK_DOWN);
}
