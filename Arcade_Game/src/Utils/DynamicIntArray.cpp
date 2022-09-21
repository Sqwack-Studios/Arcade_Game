#include "DynamicIntArray.h"
#include <assert.h>
#include <iostream>



DynamicIntArray::DynamicIntArray() :
	moptrData(nullptr),
	mSize(0),
	mCapacity(0)
{

}

DynamicIntArray::DynamicIntArray(const DynamicIntArray& otherArray):
	moptrData(nullptr)
{
	Copy(otherArray);
}

DynamicIntArray::DynamicIntArray(DynamicIntArray&& otherArray) noexcept :
	moptrData(otherArray.moptrData),
	mSize(otherArray.mSize),
	mCapacity(otherArray.mCapacity)
{
	otherArray.moptrData = nullptr;
	otherArray.mSize = 0;
	otherArray.mCapacity = 0;
}

DynamicIntArray::~DynamicIntArray()
{
	if(moptrData != nullptr)
		delete[] moptrData;

	moptrData = nullptr;
}

void DynamicIntArray::Copy(const DynamicIntArray& otherArray)
{

	bool result = Init(otherArray.mCapacity);

	assert(result);

	mSize = otherArray.mSize;

	for (int i = 0; i < mSize; i++)
	{
		moptrData[i] = otherArray.moptrData[i]++;
	}
}
DynamicIntArray& DynamicIntArray::operator=(const DynamicIntArray& otherArray)
{
	if (this == &otherArray)
		return *this;

	if (moptrData != nullptr)
		delete[] moptrData;

	Copy(otherArray);

	return *this;
}

DynamicIntArray& DynamicIntArray::operator=(DynamicIntArray&& otherArray) noexcept
{
	if (this == &otherArray)
	{
		return *this;
	}

	delete[] moptrData;

	moptrData = otherArray.moptrData;
	mSize = otherArray.mSize;
	mCapacity = otherArray.mCapacity;

	otherArray.moptrData = nullptr;
	otherArray.mSize = 0;
	otherArray.mCapacity = 0;

	return *this;

}


bool DynamicIntArray::Init(const int& capacity)
{
	
	if (capacity == 0)
	{

		return false;
	}

	if (mCapacity == capacity)
	{

		return true;
	}
		

	if (moptrData)
	{
		std::cout << "hola1";
		delete[] moptrData;
		std::cout << "hola2";
		moptrData = nullptr;
		mCapacity = 0;
		mSize = 0;
	}

	moptrData = new int[capacity];
	
	if (!moptrData)
		return false;

	mSize = 0;
	mCapacity = capacity;
	return true;
}

bool DynamicIntArray::Reserve(int capacity)
{
	if (mCapacity < capacity)
	{
		int* oldData = moptrData;

		moptrData = new (std::nothrow) int[capacity];

		if (!moptrData)
		{
			moptrData = oldData;
			return false;
		}

		for (int i = 0; i < mSize; i++)
			moptrData[i] = oldData[i];

		delete[] oldData;
		mCapacity = capacity;
	}
	return true;
}

bool DynamicIntArray::Resize(int newSize)
{
	if (mCapacity < newSize)
	{
		//Reallocate

		bool reserveSucceeded = Reserve(newSize);

		if (!reserveSucceeded)
			return false;

	}

	for (int i = mSize; i < newSize; i++)
	{
		moptrData[i] = 0;
	}

	mSize = newSize;
	return true;
}

bool DynamicIntArray::PushBack(int newVal)
{
	//assert only works in debug. If is for release
	assert(moptrData && "Has not been Initialized or corrupted - call Init()?");
	if (!moptrData)
	{
		return false;
	}

	if (mSize == mCapacity)
	{
		//we reallocate

		bool reserveSucceeded = Reserve(mCapacity * RESIZE_MULTIPLIER);

		if (!reserveSucceeded)
			return false;
	}

	//once its allocated, we push the new value to mSize + 1
	moptrData[mSize++] = newVal;

	return true;
}

bool DynamicIntArray::PopBack(int& value)
{
	assert(moptrData && "Has not been Initialized or corrupted - call Init()?");
	if (!moptrData)
	{
		return false;
	}

	if (mSize > 0)
	{
		value = moptrData[--mSize];
		return true;
	}
	return false;
}



void DynamicIntArray::Display()
{
	if (moptrData)
	{
		std::cout << "---------------------------------------" << std::endl;
		std::cout << "Capacity: " << mCapacity << std::endl;
		std::cout << "Size: " << mSize << std::endl;
		for (size_t i = 0; i < mSize; i++)
		{
			std::cout << "val[" << i << "]: " << operator[](i) << std::endl;
		}
		std::cout << "---------------------------------------" << std::endl;
	}
}

const int& DynamicIntArray::operator[](int index) const
{
	assert(moptrData && index < mSize);
	return moptrData[index];
}

int& DynamicIntArray::operator[](int index)
{
	assert(moptrData && index < mSize);
	return moptrData[index];
}