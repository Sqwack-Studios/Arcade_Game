#ifndef UTILS_VEC2D_H_
#define UTILS_VEC2D_H_

#pragma once
//Include headers
#include <iostream>


/////////////////////////////////////////////////////
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
/////////////////////////////////////////////////////

class Vec2D {

public:
	static const Vec2D Zero;
	static const Vec2D Up;
	static const Vec2D Down;
	static const Vec2D Left;
	static const Vec2D Right;
	static Vec2D CentreScreen() { return Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); };


	Vec2D() : Vec2D(0.f, 0.f) {}
	Vec2D(float x, float y) : mX(x), mY(y) {}


	inline void SetX(float x) { mX = x; }
	inline void SetY(float y) { mY = y; }
	inline float GetX() const { return mX; }
	inline float GetY() const { return mY; }

	friend std::ostream& operator<<(std::ostream& OutConsole, const Vec2D& vec);

	//Operator overloads
	//Comparision operators
	bool operator == (const Vec2D& vec2) const;
	bool operator != (const Vec2D& vec2) const;

	//Vector arithmetic
	Vec2D operator-() const;
	Vec2D operator*(float scale) const;
	Vec2D operator/(float scale) const;
	Vec2D& operator*=(float scale);
	Vec2D& operator/=(float scale);

	Vec2D operator+(const Vec2D& vec) const;
	Vec2D operator-(const Vec2D& vec) const;
	Vec2D& operator+=(const Vec2D& vec);
	Vec2D& operator-=(const Vec2D& vec);

	float Mag2() const;
	float Mag() const;

	Vec2D GetUnitVec() const;
	Vec2D& Normalize();

	float Distance(const Vec2D& vec) const;
	float Dot(const Vec2D& vec) const;
	float Cross(const Vec2D& vec) const;
	Vec2D ProjectOnto(const Vec2D& vec2) const;
	float AngleBetween(const Vec2D& vec2) const;

	Vec2D Reflect(const Vec2D& normal) const;

	void Rotate(float angle, const Vec2D& aroundPoint);
	Vec2D RotationResult(float angle, const Vec2D& aroundPoint) const;

	friend Vec2D operator*(float scale, const Vec2D& vec);
private:

	float mX, mY;


};


#endif // !UTILS_VEC2D_H_




