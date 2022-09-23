//=================================================================================
// Namespace		: Arcade_Game
// Name				: Ball.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 23/09/2022 17:32:02
//=================================================================================

#ifndef _Arcade_Game_Ball_H_
#define _Arcade_Game_Ball_H_

#pragma once
#include "AARectangle.h"
#include "Circle.h"

class Screen;
class Circle;
struct BoundaryEdge;


class Ball
{
private:
	AARectangle mBoundaryBox; //collision box
	Circle mCircle; //Actual shape on screen
	Vec2D mVelocity;

	static const float RADIUS;
protected:

public:
	Ball();
	Ball(const Vec2D& pos, float radius);

	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
	inline void Stop() { mVelocity = Vec2D::Zero; }
	void MoveTo(const Vec2D& point);
	
	void Bounce(const BoundaryEdge& edge);

	inline const AARectangle GetBoundaryBox() const { return mBoundaryBox; }
	inline void SetVelocity(const Vec2D& vel) { mVelocity = vel; }
	inline Vec2D GetVelocity() const { return mVelocity; }
	inline float GetRadius() const { return mBoundaryBox.GetWidth() / 2.0; }
	inline Vec2D GetPosition() const { return mBoundaryBox.GetCenterPoint(); }
};
#endif // !_Arcade_Game_Ball_H_

