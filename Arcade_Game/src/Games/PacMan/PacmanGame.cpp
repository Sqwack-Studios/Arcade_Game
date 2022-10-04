#include "PacmanGame.h"
#include "GameController.h"
#include "App.h"



void PacmanGame::Init(GameController& controller)
{
    mPacmanSpriteSheet.Load("PacmanSprites");

    mPacman.Init(
        mPacmanSpriteSheet,
        App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt",
        Vec2D(108, 204),
        PACMAN_MOVEMENT_SPEED,
        false);

    mLevel.Init(App::Singleton().GetBasePath() + "Assets/Pacman_level.txt", &mPacman);
   

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
    UpdatePacmanMovement();
    mPacman.Update(deltaTime);
    mLevel.Update(deltaTime);
}

void PacmanGame::Draw(Screen& theScreen)
{
    
    mLevel.Draw(theScreen);
    mPacman.Draw(theScreen);

    //Draw Score
    {
        Vec2D levelOffset = mLevel.GetLayoutOffset();
        AARectangle highScoreRect = AARectangle(Vec2D(0, 4), SCREEN_WIDTH, levelOffset.GetY());

        const BitmapFont& font = App::Singleton().GetFont();
        Vec2D textDrawPosition;

        std::string scoreStr = std::to_string(mPacman.Score());

        textDrawPosition = font.GetDrawPosition(SCORE_STR + scoreStr, highScoreRect, BFXA_CENTER, BFYA_CENTER);

        theScreen.Draw(font, SCORE_STR + scoreStr, textDrawPosition);
    }
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
        if (!mLevel.WillCollide(mPacman.GetBoundingBox(), mPressedDirection))
        {
            mPacman.SetMovementDirection(mPressedDirection);
        }
 
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

