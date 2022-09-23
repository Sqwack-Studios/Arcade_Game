#include "BreakOut.h"
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
}

void BreakOut::Update(uint32_t deltaTime)
{
    std::cout << "BreakOut Game Update()" << std::endl;
}

void BreakOut::Draw(Screen& screen)
{
    std::cout << "BreakOut Game Draw()" << std::endl;
}

std::string BreakOut::GetName() const
{
    return "BreakOut";
}
