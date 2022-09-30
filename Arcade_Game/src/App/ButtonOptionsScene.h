//=================================================================================
// Namespace		: Arcade_Game
// Name				: ButtonOptionsScene.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 30/09/2022 11:02:25
//=================================================================================

#ifndef _Arcade_Game_ButtonOptionsScene_H_
#define _Arcade_Game_ButtonOptionsScene_H_

#pragma once
#include "Scene.h"
#include "Button.h"
#include <string>
#include <vector>

class Screen;

class ButtonOptionsScene: public Scene
{
private:
	std::vector<Button> mButtons;
	int mHighlightedOption;

	void SetNextButtonHighlighted();
	void SetPreviousButtonHighlighted();
	void ExecuteCurrentButtonAction();
	void HighlightCurrentButton();
protected:

public:

	ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor);

	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& theScreen) override;

	void SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions);


};
#endif // !_Arcade_Game_ButtonOptionsScene_H_

