#include "Screen.h"
#include "Vec2D.h"
#include "SDL.h"
#include <assert.h>
#include <cmath>
#include "Line2D.h"

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

void Screen::Draw(const Line2D& line, const Color& color)
{
	assert(moptrWindow);
	if (!moptrWindow)
		return;

	int dx, dy;

	int x0 = std::roundf(line.GetP0().GetX());
	int y0 = std::roundf(line.GetP0().GetY());
	int x1 = std::roundf(line.GetP1().GetX());
	int y1 = std::roundf(line.GetP1().GetY());

	dx = x1 - x0;
	dy = y1 - y0;

	signed const char ix{ (dx > 0) - (dx < 0) }; //evaluate to 1 or -1
	signed const char iy{ (dy > 0) - (dy < 0) };

	dx = abs(dx) * 2;
	dy = abs(dy) * 2;

	Draw(x0, y0, color);

	if (dx >= dy)
	{
		//go along in the x
		int d = dy - dx / 2;

		while (x0 != x1)
		{
			if (d >= 0)
			{
				d -= dx;
				y0 += iy;
			}

			d += dy;
			x0 += ix;

			Draw(x0, y0, color);
		}
	}
	else
	{
		//go along in the y

		int d = dx - dy / 2;

		while (y0 != y1)
		{
			if (d >= 0)
			{
				d -= dy;
				x0 += ix;
			}
			d += dx;
			y0 += iy;

			Draw(x0, y0, color);

		}
	}
}

void Screen::Draw(const std::vector<Line2D>& lines, const Color& color)
{
	for (const Line2D& line : lines)
	{
		Draw(line, color);
	}
}
