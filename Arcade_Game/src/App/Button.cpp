#include "Button.h"
#include "Screen.h"


Button::Button(const BitmapFont& bitmapFont, const Color& textcolor, const Color& highlightColor):
	mBitmapFont(bitmapFont),
	mTextColor(textcolor),
	mHighlightcolor(highlightColor),
	mTitle(""),
	mHighlighted(false),
	mAction(nullptr)
{

}

void Button::Init(Vec2D topLeft, unsigned int width, unsigned int height)
{
	mBBox = AARectangle(topLeft, width, height);
}



void Button::Draw(Screen& theScreen)
{
	theScreen.Draw(mBitmapFont, mTitle, mBitmapFont.GetDrawPosition(mTitle, mBBox, BFXA_CENTER, BFYA_CENTER), mTextColor);

	if (mHighlighted)
	{
		theScreen.Draw(mBBox, mHighlightcolor);
	}
}

void Button::ExecuteAction()
{
	mAction();
}
