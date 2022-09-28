#include "App.h"
#include "BreakOut.h"
#include "GameController.h"
#include <iostream>
#include "Color.h"
#include "Screen.h"



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

    ResetGame();

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
 
            mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
        }
    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsPressed(state))
        {

            mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
        }
        else
        {
 
            mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
        }
    };
    controller.AddInputActionForKey(rightKeyAction);
}
void BreakOut::Update(uint32_t deltaTime)
{
    //std::cout << "BreakOut Game Update()" << std::endl;
    mPaddle.Update(deltaTime, mBall);
    mBall.Update(deltaTime);

    BoundaryEdge edge;

    if (mPaddle.Bounce(mBall))
    {
        return;
    }
    if (mLevelBoundary.HasCollided(mBall, edge))
    {
        mBall.Bounce(edge);
        return;
    }
    GetCurrentLevel().Update(deltaTime, mBall);

    
}

void BreakOut::Draw(Screen& screen)
{
    //std::cout << "BreakOut Game Draw()" << std::endl;
    mPaddle.Draw(screen);
    mBall.Draw(screen);
    GetCurrentLevel().Draw(screen);
    screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());
}

const std::string& BreakOut::GetName() const
{
    static std::string name{ "BreakOut" };
    return name;
}

void BreakOut::ResetGame()
{
    AARectangle paddleRect 
    { 
        Vec2D(SCREEN_WIDTH / 2 - Paddle::PADDLE_WIDTH / 2, SCREEN_HEIGHT - 3 * Paddle::PADDLE_HEIGHT), 
        Paddle::PADDLE_WIDTH, 
        Paddle::PADDLE_HEIGHT 
    };

    AARectangle levelBoundary
    {
        Vec2D::Zero,
        static_cast<unsigned int>(SCREEN_WIDTH),
        static_cast<unsigned int>(SCREEN_HEIGHT)
    };

    mLevels = BreakoutGameLevel::LoadLevelsFromFile(App::GetBasePath() + "Assets/BreakoutLevels.txt");
    mCurrentLevel = 1;

    mLevelBoundary = { levelBoundary };

    mPaddle.Init(paddleRect, levelBoundary);
    mBall.MoveTo(Vec2D::CentreScreen());
    mBall.SetVelocity(INITIAL_BALL_VEL);
}