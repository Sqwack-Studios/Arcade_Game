#include "ScreenBuffer.h"
#include <SDL.h>
#include <assert.h>


ScreenBuffer::ScreenBuffer() : mSurface(nullptr) {}

ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenBuffer)
{
	CopyBuffer(screenBuffer);
}

ScreenBuffer::~ScreenBuffer()
{

}

ScreenBuffer::ScreenBuffer(ScreenBuffer&& otherScreenBuffer) noexcept:
	mSurface(otherScreenBuffer.mSurface)
{
	otherScreenBuffer.mSurface = nullptr;
}

ScreenBuffer& ScreenBuffer::operator=(ScreenBuffer&& otherArray) noexcept
{
	if (this == &otherArray)
		return *this;

	delete mSurface;

	mSurface = otherArray.mSurface;

	otherArray.mSurface = nullptr;

	return *this;
}

void ScreenBuffer::CopyBuffer(const ScreenBuffer& screenBuffer)
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(
		0,
		screenBuffer.mSurface->w,
		screenBuffer.mSurface->h,
		0,
		screenBuffer.mSurface->format->format);

	SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
}



ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screenBuffer)
{
	if (this == &screenBuffer)
		return *this;

	if (mSurface != nullptr)
	{
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}

	if (screenBuffer.mSurface != nullptr)
	{
		CopyBuffer(screenBuffer);
	}
	return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height)
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
	Clear();
}

void ScreenBuffer::Clear(const Color& color)
{
	assert(mSurface);
	if (mSurface)
	{
		SDL_FillRect(mSurface, nullptr, color.GetPixelColor());
	}
}

void ScreenBuffer::FreeBuffer()
{
	if (mSurface)
	{
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}
}

size_t ScreenBuffer::GetIndex(int r, int c)
{
	assert(mSurface);
	if (mSurface)
	{
		return r * mSurface->w + c;
	}

	return 0;
}


void ScreenBuffer::SetPixel(const Color& color, int x, int y)
{
	assert(mSurface);
	if (mSurface && (y < mSurface->h) && (y >= 0) && (x < mSurface->w) && (x >= 0))
	{
		SDL_LockSurface(mSurface);

		uint32_t* pixels = (uint32_t*)mSurface->pixels;

		size_t index = GetIndex(y, x);

		//pixels[index] = color.GetPixelColor();
		Color surfaceColor = Color(pixels[index]); //destination color
		pixels[index] = Color::EvaluateMinueSourceAlpha(color, surfaceColor).GetPixelColor();

		SDL_UnlockSurface(mSurface);
	}
}
