#include "PacmanGame.h"
#include "GameController.h"
#include "App.h"



void PacmanGame::Init(GameController& controller)
{
    mPacmanSpriteSheet.Load("PacmanSprites");
    mLevel.Init(App::Singleton().GetBasePath() + "Assets/Pacman_level.txt");
    mPacman.Init(
        mPacmanSpriteSheet,
        App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt",
        Vec2D::Zero,
        PACMAN_MOVEMENT_SPEED,
        false);

    ResetGame();

    ButtonAction leftAction;
    leftAction.key = GameController::LeftKey();
    leftAction.action = [this](uint32_t deltaTime, InputState state) {

        HandleGameControllerState(deltaTime, state, PACMAN_MOVEMENT_LEFT);
    };
    controller.AddInputActionForKey(leftAction);

    ButtonAction rightAction;
    rightAction.key = GameController::RightKey();
    rightAction.action = [this](uint32_t deltaTime, InputState state) {

        HandleGameControllerState(deltaTime, state, PACMAN_MOVEMENT_RIGHT);
    };
    controller.AddInputActionForKey(rightAction);

    ButtonAction upAction;
    upAction.key = GameController::UpKey();
    upAction.action = [this](uint32_t deltaTime, InputState state) {

        HandleGameControllerState(deltaTime, state, PACMAN_MOVEMENT_UP);
    };
    controller.AddInputActionForKey(upAction);

    ButtonAction downAction;
    downAction.key = GameController::DownKey();
    downAction.action = [this](uint32_t deltaTime, InputState state) {

        HandleGameControllerState(deltaTime, state, PACMAN_MOVEMENT_DOWN);
    };
    controller.AddInputActionForKey(downAction);
}

void PacmanGame::Update(uint32_t deltaTime)
{
    mLevel.Update(deltaTime);
    mPacman.Update(deltaTime);
    UpdatePacmanMovement();
}

void PacmanGame::Draw(Screen& theScreen)
{
    
    mLevel.Draw(theScreen);
    mPacman.Draw(theScreen);
}

const std::string& PacmanGame::GetName() const
{
    static std::string name = "Pacman";

    return name;
 
}


void PacmanGame::ResetGame()
{
    mPressedDirection = PACMAN_MOVEMENT_NONE;
    mPacman.ResetScore();
}

void PacmanGame::UpdatePacmanMovement()
{
    if (mPressedDirection != PACMAN_MOVEMENT_NONE)
    {
        mPacman.SetMovementDirection(mPressedDirection);
    }
}

void PacmanGame::HandleGameControllerState(const uint32_t& deltaTime, const InputState& state, const PacmanMovement& direction)
{
    if (GameController::IsPressed(state))
    {
        mPressedDirection = direction;
    }
    else if (GameController::IsReleased(state) && mPressedDirection == direction)
    {
        mPressedDirection = PACMAN_MOVEMENT_NONE;
    }
}

