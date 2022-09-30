#include "ButtonOptionsScene.h"
#include "App.h"
#include "BitmapFont.h"
#include "Utils.h"



ButtonOptionsScene::ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor):
	mHighlightedOption(0)
{
	const BitmapFont& font = App::Singleton().GetFont();

	for (size_t i = 0; i < optionNames.size(); i++)
	{
		mButtons.push_back(Button(font, textColor));
		mButtons.back().SetButtonText(optionNames[i]);
	}

	if (optionNames.size() > 0)
	{
		mButtons[mHighlightedOption].SetHighlighted(true);
	}
}

void ButtonOptionsScene::Init()
{
	ButtonAction upAction;
	upAction.key = GameController::UpKey();
	upAction.action = [this](uint32_t deltaTime, InputState state) {

		if (GameController::IsPressed(state))
		{
			SetPreviousButtonHighlighted();
		}
	};
	mGameController.AddInputActionForKey(upAction);

	ButtonAction downAction;
	downAction.key = GameController::DownKey();
	downAction.action = [this](uint32_t deltaTime, InputState state) {

		if (GameController::IsPressed(state))
		{
			SetNextButtonHighlighted();
		}
	};
	mGameController.AddInputActionForKey(downAction);

	ButtonAction executeAction;
	executeAction.key = GameController::ActionKey();
	executeAction.action = [this](uint32_t deltaTime, InputState state) {

		if (GameController::IsPressed(state))
		{
			ExecuteCurrentButtonAction();
		}
	};
	mGameController.AddInputActionForKey(executeAction);

	uint32_t height = SCREEN_HEIGHT;
	uint32_t width = SCREEN_WIDTH;

	const BitmapFont& font = App::Singleton().GetFont();
	Size fontSize = font.GetSizeOf(mButtons[0].GetButtonText());

	const int BUTTON_PADDING = 10;
	const int Y_PADDING = 1;

	unsigned int butonHeight = fontSize.height + BUTTON_PADDING * 2;

	uint32_t maxButtonWidth = fontSize.width;


	for (const auto& button : mButtons)
	{
		Size s = font.GetSizeOf(button.GetButtonText());

		if (s.width > maxButtonWidth)
		{
			maxButtonWidth = s.width;
		}
	}

	maxButtonWidth += BUTTON_PADDING * 2;

	uint32_t yOffset = height / 2 - ((butonHeight + Y_PADDING) * static_cast<uint32_t>(mButtons.size())) / 2;

	for (auto& button : mButtons)
	{
		button.Init(Vec2D(width / 2 - maxButtonWidth / 2, yOffset), maxButtonWidth, butonHeight);

		yOffset += butonHeight + Y_PADDING;
	}

	mButtons[mHighlightedOption].SetHighlighted(true);
}

void ButtonOptionsScene::Update(uint32_t deltaTime)
{
}

void ButtonOptionsScene::Draw(Screen& theScreen)
{
	for (auto& button : mButtons)
	{
		button.Draw(theScreen);
	}
}

void ButtonOptionsScene::SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions)
{
	for (size_t i = 0; i < mButtons.size(); i++)
	{
		mButtons[i].SetButtonAction(buttonActions[i]);
	}
}

void ButtonOptionsScene::SetNextButtonHighlighted()
{
	mHighlightedOption = (mHighlightedOption + 1) % mButtons.size();
	HighlightCurrentButton();
}

void ButtonOptionsScene::SetPreviousButtonHighlighted()
{
	--mHighlightedOption;

	if (mHighlightedOption < 0)
	{
		mHighlightedOption = static_cast<int>(mButtons.size() - 1);
	}

	HighlightCurrentButton();
}

void ButtonOptionsScene::ExecuteCurrentButtonAction()
{
	mButtons[mHighlightedOption].ExecuteAction();
}

void ButtonOptionsScene::HighlightCurrentButton()
{
	for (auto& button : mButtons)
	{
		button.SetHighlighted(false);
	}

	mButtons[mHighlightedOption].SetHighlighted(true);
}
