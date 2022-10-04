//=================================================================================
// Namespace		: Arcade_Game
// Name				: App.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 21/09/2022 18:12:42
//=================================================================================

#ifndef _Arcade_Game_App_H_
#define _Arcade_Game_App_H_

#pragma once
#include "Screen.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "InputController.h"
#include "BitmapFont.h"

struct SDL_Window;
class Scene;

class App
{
private:
	Screen mScreen;
	SDL_Window* mnoptrWindow; //Screen owns it

	std::vector<std::unique_ptr<Scene>> mSceneStack;

	InputController mInputController;

	BitmapFont mFont;

protected:

public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	~App();
	void Run();

	inline uint32_t Width() const { return mScreen.Width(); }
	inline uint32_t Height() const { return mScreen.Height(); }

	void PushScene(std::unique_ptr<Scene> scene); //move semantic function, take ownership of the scene
	void PopScene();
	Scene* TopScene(); //current Scene

	static const std::string& GetBasePath();
	inline const BitmapFont& GetFont() const { return mFont; }
};
#endif // !_Arcade_Game_App_H_

