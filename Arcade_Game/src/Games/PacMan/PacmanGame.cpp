#include "PacmanGame.h"
#include "App.h"

void PacmanGame::Init(GameController& controller)
{
    
    mLevel.Init(App::Singleton().GetBasePath() + "Assets/Pacman_level.txt");
}

void PacmanGame::Update(uint32_t deltaTime)
{
    mLevel.Update(deltaTime);
}

void PacmanGame::Draw(Screen& theScreen)
{
    
    mLevel.Draw(theScreen);
}

const std::string& PacmanGame::GetName() const
{
    static std::string name = "Pacman";

    return name;
    // TODO: Insertar una instrucción "return" aquí
}
