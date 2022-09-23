#include "BreakOut.h"
#include "GameController.h"
#include <iostream>



/*
*   Paddle
*       -Can move side to side (by the user)
*       -Stops at the edge of the screen
*       -Width and Height
*       -Bounces the ball
*       -Bounces the ball differently based on the position that was hit on the paddle
* 
*   Ball
*       -Bounces off the walls and the paddle
*       -Width and height
*       -Velocity and position (xd?)
*       
*   Block
*       -Part of the level
*       -Has HP - One hit by the ball is -1HP (minus 1)
*       -Color and position, width and height (AARectangles)
*   Level
*       -Container that holds all of the blocks
*       -Should be able to load a level from the levels.txt
*       -Handle collisions of  the blocks?
*       -Contain the walls/edges of the screens
*       -Reset level?
*   Game
*       -Contains all of the objects (Paddle, Ball, Levels)
*       -Player which has 3 lives
*       -States - Serve the ball, In Game, Game Over...
*       -Reset game?
* 
*       
*       
* 
*/
void BreakOut::Init(GameController& controller)
{
    std::cout << "BreakOut Game Init()" << std::endl;
    controller.ClearAll();

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            mPaddle.SetMovementDirection(PaddleDirection::LEFT);
        }
        else
        {
            mPaddle.SetMovementDirection(PaddleDirection::NONE);
        }
    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    leftKeyAction.key = GameController::RightKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
        }
        else
        {
            mPaddle.SetMovementDirection(PaddleDirection::NONE);
        }
    };
    controller.AddInputActionForKey(rightKeyAction);
}
void BreakOut::Update(uint32_t deltaTime)
{
    std::cout << "BreakOut Game Update()" << std::endl;
    mPaddle.Update(deltaTime);
}

void BreakOut::Draw(Screen& screen)
{
    std::cout << "BreakOut Game Draw()" << std::endl;
    mPaddle.Draw(screen);
}

std::string BreakOut::GetName() const
{
    return "BreakOut";
}

void BreakOut::ResetGame()
{
    AARectangle paddleRect 
    { 
        Vec2D(SCREEN_WIDTH / 2 - Paddle::PADDLE_WIDTH / 2, SCREEN_HEIGHT - 3 * Paddle::PADDLE_HEIGHT), 
        Paddle::PADDLE_WIDTH, 
        Paddle::PADDLE_HEIGHT 
    };

    mPaddle.Init(paddleRect);
}