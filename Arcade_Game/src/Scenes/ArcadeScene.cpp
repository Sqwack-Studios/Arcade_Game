#include "ArcadeScene.h"
#include "Screen.h"
#include "Vec2D.h"
#include "Star2D.h"
#include "GameController.h"
#include <iostream>

#include "Utils.h"
#include "Color.h"
#include "App.h"



ArcadeScene::ArcadeScene()
{
}

void ArcadeScene::Init()
{
	mTempImage.Load(App::GetBasePath() + "Assets/ArcadeFont.bmp");

	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t deltaTime, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			std::cout << "Action button was pressed" << std::endl;
		}
		
	};
	mGameController.AddInputActionForKey(action);

	MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position)
	{
		if (GameController::IsPressed(state))
		{
			std::cout << "Left Mouse button pressed!" << std::endl;
		}
	};

	mGameController.AddMouseButtonAction(mouseAction);
	mGameController.SetMouseMovedAction([](const MousePosition& mousePosition)
		{
			std::cout << "Mouse position x: " << mousePosition.xPos << " , y: " << mousePosition.yPos << std::endl;
		});
}

void ArcadeScene::Draw(Screen& theScreen)
{

	//Star2D star(Vec2D::CentreScreen(), 60, 30, 5, 0.0f);
	//star.SetIsRotating(true);
	//star.SetRotationRate(-2 * PI * 120 / 360);
	//theScreen.Draw(star.SendToBuffer(), Color::Blue());

	theScreen.Draw(mTempImage, Vec2D::Zero);

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
