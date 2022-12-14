#include "Screen.h"
#include "Vec2D.h"
#include "SDL.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "Line2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "BitmapFont.h"
#include "Utils.h"

Screen::Screen(): 
	mWidth(0), 
	mHeight(0), 
	moptrWindow(nullptr), 
	mnoptrWindowSurface(nullptr),
	mRenderer(nullptr),
	mPixelFormat(nullptr),
	mTexture(nullptr)
{}

Screen::~Screen()
{
	mBackBuffer.FreeBuffer();

	if (mRenderer)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
	if (mPixelFormat)
	{
		SDL_FreeFormat(mPixelFormat);
		mPixelFormat = nullptr;
	}
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
	if (moptrWindow)
	{
		SDL_DestroyWindow(moptrWindow);
		moptrWindow = nullptr;
	}

	
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag, bool fast)
{
	mFast = fast;
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
		//Clear color is black
		uint8_t rClear = 0;
		uint8_t gClear = 0;
		uint8_t bClear = 0;
		uint8_t aClear = 255;

		if (mFast)//Gpu accelerated
		{
			mRenderer = SDL_CreateRenderer(moptrWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (mRenderer)
			{
				InitPixelFormat();
				mTexture = SDL_CreateTexture(mRenderer, mPixelFormat->format, SDL_TEXTUREACCESS_STREAMING, w, h);
				SDL_SetRenderDrawColor(mRenderer, rClear, gClear, bClear, aClear);
			}
			else
			{
				std::cout << "SDL_CreateRenderer failed." << std::endl;
				return nullptr;
			}
		}
		else//Non-gpu accelerated 
		{
			mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
		}
		
	
		

		Color::InitColorFormat(mPixelFormat);

		//set clear color
		mClearColor = Color(rClear, gClear, bClear, aClear);

		//initialize back buffer
		mBackBuffer.Init(mPixelFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);
	}

	return moptrWindow;
}

void Screen::InitPixelFormat()
{
	std::vector<std::string> s_preferredPixelFormats{

		"SDL_PIXELFORMAT_ARGB8888",
		"SDL_PIXELFORMAT_RGBA8888",
		"SDL_PIXELFORMAT_BGRA8888"
	};

	SDL_RendererInfo info;
	SDL_GetRendererInfo(mRenderer, &info);

	int32_t foundIndex {-1};

	for(Uint32 i = 0; i < info.num_texture_formats; i++)
	{
		auto iterator = std::find(s_preferredPixelFormats.begin(), s_preferredPixelFormats.end(), std::string(SDL_GetPixelFormatName(info.texture_formats[i])));
		if (iterator != s_preferredPixelFormats.end())
		{
			foundIndex = i;
			break;
		}
	}


	
	assert(foundIndex != -1);

	mPixelFormat = SDL_AllocFormat(info.texture_formats[foundIndex]);
}
void Screen::ClearScreen()
{
	assert(moptrWindow);
	if(moptrWindow)
	{
		if (mFast)
		{
			SDL_RenderClear(mRenderer);
		}
		else
		{
			SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
		}

	}

}

void Screen::FillPoly(const std::vector<Vec2D>& points, FillPolyFunc func)
{
	if (points.size() > 0)
	{
		float top = points[0].GetY();
		float bottom = points[0].GetY();
		float right = points[0].GetX();
		float left = points[0].GetX();

		for (size_t i = 1; i < points.size(); ++i)
		{
			if (points[i].GetY() < top)
			{
				top = points[i].GetY();
			}

			if (points[i].GetY() > bottom)
			{
				bottom = points[i].GetY();
			}

			if (points[i].GetX() < left)
			{
				left = points[i].GetX();
			}

			if (points[i].GetX() > right)
			{
				right = points[i].GetX();
			}
		}

		for (int pixelY = top; pixelY < bottom; ++pixelY)
		{
			std::vector<float> nodeXVec;

			size_t j = points.size() - 1;

			for (size_t i = 0; i < points.size(); ++i)
			{
				float pointiY = points[i].GetY();
				float pointjY = points[j].GetY();

				
				if ((pointiY <= (float)pixelY && pointjY > (float)pixelY) || (pointjY <= (float)pixelY && pointiY > (float)pixelY))
				{
					float denom = pointjY - pointiY;
					if (IsEqual(denom, 0))
					{
						continue;
					}

					float x = points[i].GetX() + (pixelY - pointiY) / (denom) * (points[j].GetX() - points[i].GetX());
					nodeXVec.push_back(x);
				}

				j = i;
			}

			std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

			for (size_t k = 0; k < nodeXVec.size(); k += 2)
			{
				if (nodeXVec[k] > right)
				{
					break;
				}

				if (nodeXVec[k + 1] > left)
				{
					if (nodeXVec[k] < left)
					{
						nodeXVec[k] = left;
					}
					if (nodeXVec[k + 1] > right)
					{
						nodeXVec[k + 1] = right;
					}

					//Line2D line = {Vec2D(nodeXVec[k], pixelY), Vec2D(nodeXVec[k+1], pixelY)};
					//Draw(line, color);
					for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; ++pixelX)
					{
						Draw(pixelX, pixelY, func(pixelX, pixelY));
					}
				}
			}
		}




	}
}


void Screen::SwapScreen()
{
	assert(moptrWindow);
	if (moptrWindow)
	{
		ClearScreen();

		if (mFast)
		{
			uint8_t* textureData = nullptr;
			int texturePitch = 0;

			if (SDL_LockTexture(mTexture, nullptr, (void**) &textureData, &texturePitch) >= 0)
			{
				SDL_Surface* surface = mBackBuffer.GetSurface();

				memcpy(textureData, surface->pixels, surface->w* surface->h* mPixelFormat->BytesPerPixel);

				SDL_UnlockTexture(mTexture);
				SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
				SDL_RenderPresent(mRenderer);
			}
		}
		else
		{
			SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);

			SDL_UpdateWindowSurface(moptrWindow);

			
		}
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

	int x = std::roundf(point.GetX());
	int y = std::roundf(point.GetY());
	mBackBuffer.SetPixel(color, x, y);
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

void Screen::Draw(const Triangle& triangle, const Color& color, bool fill, const Color& fillColor)
{
	if (fill)
	{
		FillPoly(triangle.GetPoints(), [&](uint32_t x, uint32_t y) { return fillColor; });
	}
	Line2D p0p1(triangle.GetP0(), triangle.GetP1());
	Line2D p1p2(triangle.GetP1(), triangle.GetP2());
	Line2D p2p0(triangle.GetP2(), triangle.GetP0());

	Draw(p0p1, color);
	Draw(p1p2, color);
	Draw(p2p0, color);


}

void Screen::Draw(const AARectangle& rect, const Color& color, bool fill, const Color& fillColor)
{
	std::vector<Vec2D> points(rect.GetPoints());

	if (fill)
	{
		FillPoly(points, [&](uint32_t x, uint32_t y) { return fillColor; });
	}

	Line2D p0p1(points[0], points[1]);
	Line2D p1p2(points[1], points[2]);
	Line2D p2p3(points[2], points[3]);
	Line2D p3p0(points[3], points[0]);

	Draw(p0p1, color);
	Draw(p1p2, color);
	Draw(p2p3, color);
	Draw(p3p0, color);


}

void Screen::Draw(const Circle& circle, const Color& color, bool fill, const Color& fillColor)
{
	std::vector<Vec2D> circlePoints;
	std::vector<Line2D> lines;

	Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY() + circle.GetRadius());
	Vec2D p1(p0);
	float step = TWO_PI / NUM_CIRCLE_SEGMENTS;
	Line2D nextLineToDraw;
	bool withinX;
	bool withinY;


	for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; i++)
	{
		p1.Rotate(step, circle.GetCenterPoint());

		withinX = IsGreaterThanOrEqual(p1.GetX(), 0.f) && IsLessThanOrEqual(p1.GetX(), (float)SCREEN_WIDTH);
		withinY = IsGreaterThanOrEqual(p1.GetY(), 0.f) && IsLessThanOrEqual(p1.GetY(), (float)SCREEN_HEIGHT);

		if (withinX && withinY)
		{
			nextLineToDraw.SetP0(p0);
			nextLineToDraw.SetP1(p1);

			lines.push_back(nextLineToDraw);
			circlePoints.push_back(p0);

			p0 = p1;
		}
	}

	if (fill)
		FillPoly(circlePoints, [&](uint32_t x, uint32_t y) { return fillColor; });


	for (const Line2D& line : lines)
	{
		Draw(line, color);
	}
}


void Screen::Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor)
{
	float rVal = static_cast<float>(overlayColor.GetRed() / 255.0f);
	float gVal = static_cast<float>(overlayColor.GetGreen() / 255.0f);
	float bVal = static_cast<float>(overlayColor.GetBlue() / 255.0f);
	float aVal = static_cast<float>(overlayColor.GetAlpha() / 255.0f);

	uint32_t width = sprite.width;
	uint32_t height = sprite.height;

	const std::vector<Color>& pixels = image.GetPixels();

	Vec2D topLeft = pos;
	Vec2D topRight = pos + Vec2D(width, 0);
	Vec2D bottomLeft = pos + Vec2D(0, height);
	Vec2D bottomRight = pos + Vec2D(width, height);

	std::vector<Vec2D> points = { topLeft, bottomLeft, bottomRight, topRight };

	Vec2D xAxis = topRight - topLeft;
	Vec2D yAxis = bottomLeft - topLeft;

	const float invXAxisLengthSq = 1.0f / xAxis.Mag2();
	const float invYAxisLengthSq = 1.0f / yAxis.Mag2();

	//U-V MAPS to draw images in any scale or transformation
	FillPoly(points, [&](uint32_t px, uint32_t py) {

		Vec2D p = { static_cast<float>(px), static_cast<float>(py) };
		Vec2D d = p - topLeft;

		float u = invXAxisLengthSq * d.Dot(xAxis);
		float v = invYAxisLengthSq * d.Dot(yAxis);

		u = Clamp(u, 0.0f, 1.0f);
		v = Clamp(v, 0.0f, 1.0f);

		float tx = roundf(u * static_cast<float>(sprite.width));
		float ty = roundf(v * static_cast<float>(sprite.height));

		Color imageColor = pixels[GetIndex(image.GetWidth(), ty + sprite.yPos, tx + sprite.xPos)];

		uint8_t newRed = static_cast<uint8_t>(imageColor.GetRed() * rVal);
		uint8_t newGreen = static_cast<uint8_t>(imageColor.GetGreen() * gVal);
		uint8_t newBlue = static_cast<uint8_t>(imageColor.GetBlue() * bVal);
		uint8_t newAlpha = static_cast<uint8_t>(imageColor.GetAlpha() * aVal);

		Color newColor(newRed, newGreen, newBlue, newAlpha);

		return newColor;
		});

}

void Screen::Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor)
{
	Draw(ss.GetBMPImage(), ss.GetSprite(spriteName), pos, overlayColor);
}

void Screen::Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor)
{
	uint32_t xPos = pos.GetX();

	const SpriteSheet& ss = font.GetSpriteSheet();

	for (const char& c : textLine)
	{
		if (c == ' ')
		{
			xPos += font.GetFontSpacingBetweenWords();
			continue;
		}

		Sprite sprite = ss.GetSprite(std::string("") + c);

		Draw(ss.GetBMPImage(), sprite, Vec2D(xPos, pos.GetY()), overlayColor);

		xPos += sprite.width + font.GetFontSpacingBetweenLetters();
	}
}

