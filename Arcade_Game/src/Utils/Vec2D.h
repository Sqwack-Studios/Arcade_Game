#ifndef UTILS_VEC2D_H_
#define UTILS_VEC2D_H_

//Include headers
#include <iostream>

/////////////////////////////////////////////////////
class Vec2D {

public:
	static const Vec2D Zero;

	Vec2D() : Vec2D(0.f, 0.f) {}
	Vec2D(float x, float y) : mX(x), mY(y) {}


	inline void SetX(float x) { mX = x; }
	inline void SetY(float y) { mY = y; }
	inline float GetX() const { return mX; }
	inline float GetY() const { return mY; }

	friend std::ostream& operator<< (std::ostream& OutConsole, Vec2D& vec);

	bool operator == (const Vec2D& vec2) const;
	bool operator != (const Vec2D& vec2) const;



private:

	float mX, mY;

};


#endif // !UTILS_VEC2D_H_




