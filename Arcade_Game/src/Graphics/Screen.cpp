#include "Screen.h"
#include "Vec2D.h"
#include "SDL.h"
#include <assert.h>

Screen::Screen() : mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr) {}

Screen::~Screen()
{
	if (moptrWindow)
	{
		SDL_DestroyWindow(moptrWindow);
		moptrWindow = nullptr;
	}
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}

	mWidth = w;
	mHeight = h;

	moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

	if (moptrWindow)
	{
		//initialize surface and colors
		mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
		SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
		Color::InitColorFormat(pixelFormat);
		//set clear color
		mClearColor = Color::Black();

		//initialize back buffer
		mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);
	}

	return moptrWindow;
}

void Screen::ClearScreen()
{
	assert(moptrWindow);
	if(moptrWindow)
	{
		SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
	}

}

void Screen::SwapScreen()
{
	assert(moptrWindow);
	if (moptrWindow)
	{
		ClearScreen();

		SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);

		SDL_UpdateWindowSurface(moptrWindow);

		mBackBuffer.Clear(mClearColor);
	}
}

void Screen::Draw(int x, int y, const Color& color)
{
	assert(moptrWindow);
	if (!moptrWindow)
		return;

	mBackBuffer.SetPixel(color, x, y);
}

void Screen::Draw(const Vec2D& point, const Color& color)
{
	assert(moptrWindow);
	if (!moptrWindow)
		return;

	mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
}
