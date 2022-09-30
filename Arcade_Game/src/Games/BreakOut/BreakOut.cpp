#include "App.h"
#include "BreakOut.h"
#include "GameController.h"
#include <iostream>
#include "Circle.h"



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

    ButtonAction serveAction;
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (mGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                mGameState = IN_PLAY;

                if (mPaddle.IsMovingLeft())
                {
                    mBall.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
                else
                {
                    mBall.SetVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }

            }
        }
        else if (mGameState == IN_GAME_OVER)
        {
            if (GameController::IsPressed(state))
            {
                ResetGame();
            }
        }
    };
    controller.AddInputActionForKey(serveAction);

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (mGameState == IN_PLAY || mGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                mPaddle.SetMovementDirection(PaddleDirection::LEFT);

            }
            else
            {

                mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
            }
        }

    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (mGameState == IN_PLAY || mGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {

                mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
            }
            else
            {

                mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
            }
        }
    };
    controller.AddInputActionForKey(rightKeyAction);

    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (mGameState == IN_SERVE || mGameState == IN_GAME_OVER)
        {
            if (GameController::IsPressed(state))
            {
                App::Singleton().PopScene();
            }
        }

    };
    controller.AddInputActionForKey(backAction);
}
void BreakOut::Update(uint32_t deltaTime)
{
    //std::cout << "BreakOut Game Update()" << std::endl;

    if (mGameState == IN_SERVE)
    {
        mPaddle.Update(deltaTime, mBall);
        SetToServeState();
    }
    else if (mGameState == IN_PLAY)
    {
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

        if (IsBallPassedCutoffY())
        {
            ReduceLifeByOne();
            if (!IsGameOver())
            {
                SetToServeState();
            }
            else
            {
                mGameState = IN_GAME_OVER;
            }
        }
        else if (GetCurrentLevel().IsLevelCompleted())
        {
            mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
            ResetGame(mCurrentLevel);
        }
    }
  


    
}

void BreakOut::Draw(Screen& screen)
{
    //std::cout << "BreakOut Game Draw()" << std::endl;
    mPaddle.Draw(screen);
    mBall.Draw(screen);
    GetCurrentLevel().Draw(screen);
    screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());

    Circle lifeCircle(Vec2D(9, SCREEN_HEIGHT - 10), 3);
    Line2D cutOff(Vec2D(0, mYCutoff), Vec2D(SCREEN_WIDTH, mYCutoff));

    for (size_t i = 0; i < mLives; i++)
    {
        screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
        lifeCircle.MoveBy(Vec2D(17, 0));
        screen.Draw(cutOff, Color::White());
    }
}

const std::string& BreakOut::GetName() const
{
    static std::string name{ "BreakOut" };
    return name;
}

void BreakOut::ResetGame(size_t toLevel)
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
    mYCutoff = SCREEN_HEIGHT - 2 * Paddle::PADDLE_HEIGHT;
 
    mCurrentLevel = toLevel;
    mLives = MAX_LIVES;

    mLevelBoundary = { levelBoundary };

    mPaddle.Init(paddleRect, levelBoundary);
    mBall.MoveTo(Vec2D::CentreScreen());

    SetToServeState();
}

void BreakOut::SetToServeState()
{
    mGameState = IN_SERVE;
    mBall.Stop();

    mBall.MoveTo(Vec2D(mPaddle.GetAARectangle().GetCenterPoint().GetX(), mPaddle.GetAARectangle().GetTopLeftPoint().GetY() - mBall.GetRadius()));
}

bool BreakOut::IsBallPassedCutoffY() const
{
    return mBall.GetPosition().GetY() > mYCutoff;
}

void BreakOut::ReduceLifeByOne()
{
    if (mLives >= 0)
    {
        --mLives;
    }
}
