#include "BMPImage.h"
#include "SDL.h"


BMPImage::BMPImage():
	mWidth(0),
	mHeight(0)
{

}

bool BMPImage::Load(const std::string& path)
{
	SDL_Surface* bmpSurface = SDL_LoadBMP(path.c_str());

	if (!bmpSurface)
		return false;

	mWidth = bmpSurface->w;
	mHeight = bmpSurface->h;

	uint32_t numOfPixels = mWidth * mHeight;

	mPixels.reserve(numOfPixels);

	SDL_LockSurface(bmpSurface);

	uint32_t* pixels = static_cast<uint32_t*>(bmpSurface->pixels);

	for (uint32_t i = 0; i < numOfPixels; i++)
	{
		mPixels.push_back(Color(pixels[i]));
	}

	SDL_UnlockSurface(bmpSurface);

	SDL_FreeSurface(bmpSurface);
	return true;
}
