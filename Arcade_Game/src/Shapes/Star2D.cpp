#include "Star2D.h"
#include "Line2D.h"
#include "Utils.h"



Vec2D Star2D::DEFAULT_STAR_POSITION = Vec2D::CentreScreen();

Star2D::Star2D() : 
	Star2D(DEFAULT_STAR_POSITION, DEFAULT_INNER_RADII, DEFAULT_OUTER_RADII, DEFAULT_NUM_SPIKES)
{
}
Star2D::Star2D(const Vec2D& center) :
	Star2D(center, DEFAULT_INNER_RADII, DEFAULT_OUTER_RADII, DEFAULT_NUM_SPIKES)
{
}
Star2D::Star2D(const Vec2D& center, const int& outerRadii, const int& innerRadii, const int& numSpikes, const float& angle) :
	mCenter(center),
	mOuterRadii(outerRadii),
	mInnerRadii(innerRadii),
	mNumSpikes(numSpikes)
{
	BuildStar();
	if (angle > EPSILON)
	{
		Rotate(angle, mCenter);
	}
}

void Star2D::BuildStar()
{
	//Get first points
	//1st spike
	Vec2D spike = Vec2D(mCenter.GetX(), mCenter.GetY() - mOuterRadii);
	//1st innerSpike
	Vec2D innerSpike = Vec2D(mCenter.GetX(), mCenter.GetY() - mInnerRadii);
	float step = (2 * PI) / mNumSpikes;

	innerSpike.Rotate(step / 2 , mCenter);

	Line2D line;
	mLines.clear();

	//Draws 2 lines per step. If spike number is even, we could optimize this by symmetry
	for (size_t i = 0; i < mNumSpikes; i++)
	{

		line.SetP0(spike);
		line.SetP1(innerSpike);

	
		mLines.push_back(line);


		spike.Rotate(step, mCenter);


		line.SetP0(innerSpike);
		line.SetP1(spike);


		mLines.push_back(line);

		innerSpike.Rotate(step, mCenter);
	
	}
	 
	 

}
void Star2D::Rotate(const float& angle, const Vec2D& aroundPoint)
{
	for (Line2D& line : mLines)
	{
		line.Rotate(angle, aroundPoint);
	}
}

void Star2D::Update(const int &deltaTime)
{
	if (mIsRotating)
		Rotate(mRotationRate * deltaTime /1000,mCenter);
}


