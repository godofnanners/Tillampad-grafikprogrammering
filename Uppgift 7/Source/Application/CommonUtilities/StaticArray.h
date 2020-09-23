#pragma once
#include <initializer_list>
#include <assert.h>
namespace CommonUtilities
{
	template <typename T, int size>
	class StaticArray
	{
	public:
		StaticArray() = default;
		StaticArray(const StaticArray& aStaticArray);
		StaticArray(const std::initializer_list<T>& aInitList);
		~StaticArray() = default;
		StaticArray& operator=(const StaticArray& aStaticArray);
		inline const T& operator[](const int aIndex) const;
		inline T& operator[](const int aIndex);
		inline void Insert(const int aIndex, const T& aObject);
	protected:
		T myObjects[size] = {0};
	};


	template<typename T, int size>
	inline StaticArray<T, size>::StaticArray(const StaticArray& aStaticArray)
	{
		for (int i = 0; i < size; i++)
		{
			myObjects[i] = aStaticArray[i];
		}
	}

	template<typename T, int size>
	inline StaticArray<T, size>::StaticArray(const std::initializer_list<T>& aInitList)
	{
		assert(size >= aInitList.size());

		for (int i = 0; i < size; i++)
		{
			myObjects[i] = *(aInitList.begin()+i);
		}
	}

	template<typename T, int size>
	inline StaticArray<T, size>& StaticArray<T, size>::operator=(const StaticArray& aStaticArray)
	{
		for (int i = 0; i < size; i++)
		{
			myObjects[i] = aStaticArray[i];
		}
		return *this;
	}

	template<typename T, int size>
	inline const T& StaticArray<T, size>::operator[](const int aIndex) const
	{
		assert(size > aIndex);
		assert(aIndex >= 0);
		return myObjects[aIndex];
	}

	template<typename T, int size>
	inline T& StaticArray<T, size>::operator[](const int aIndex)
	{
		assert(size > aIndex );
		assert(aIndex >= 0 );
		return myObjects[aIndex];
	}

	template<typename T, int size>
	inline void StaticArray<T, size>::Insert(const int aIndex, const T& aObject)
	{
		assert(size > aIndex);
		assert(aIndex >= 0);
		for (int i = size-1; i > aIndex; i--)
		{
				myObjects[i] = myObjects[i - 1];
		}
		myObjects[aIndex] = aObject;
	}

}