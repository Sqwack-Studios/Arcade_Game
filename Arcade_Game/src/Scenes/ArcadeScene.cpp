#include "ArcadeScene.h"
#include "Screen.h"
#include "Vec2D.h"
#include "Star2D.h"

#include "Utils.h"
#include "Color.h"



ArcadeScene::ArcadeScene()
{
}

void ArcadeScene::Init()
{
}

void ArcadeScene::Draw(Screen& theScreen)
{

	Star2D star(Vec2D::CentreScreen(), 60, 30, 5, 0.0f);
	star.SetIsRotating(true);
	star.SetRotationRate(-2 * PI * 120 / 360);
	theScreen.Draw(star.SendToBuffer(), Color::Blue());

	theScreen.SwapScreen();
}

void ArcadeScene::Update(uint32_t deltaTime)
{
	/*star.Update(deltaTime);*/
}



const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade Scene";
    return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
	switch (game)
	{
		case TETRIS:

			break;
		case BREAK_OUT:

			break;
		case ASTEROIDS:

			break;
		case PACMAN:

			break;
		case NUM_GAMES:

			break;
		default:
			break;
	}
	return nullptr;
}
