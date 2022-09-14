//=================================================================================
// Namespace		: Arcade_Game
// Name				: DynamicIntArray.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 14/09/2022 11:43:30
//=================================================================================

#ifndef _Arcade_Game_DynamicIntArray_H_
#define _Arcade_Game_DynamicIntArray_H_

#pragma once

class DynamicIntArray
{
private:
	static const int INITIAL_CAPACITY{ 10 };
	int* moptrData;
	int mSize;
	int mCapacity;

protected:

public:

	DynamicIntArray();
	DynamicIntArray(const DynamicIntArray& otherArray);
	~DynamicIntArray();

	inline int Size() const { return mSize; }
	inline int Capacity() const { return mCapacity; }

	bool Init(int capacity = INITIAL_CAPACITY);

	bool Reserve(int capacity);

	bool Resize(int newSize);

	bool PushBack(int newVal);
	bool PopBack(int& value);

	const int& operator[](int index) const;
	int& operator[](int index);
};
#endif // !_Arcade_Game_DynamicIntArray_H_

