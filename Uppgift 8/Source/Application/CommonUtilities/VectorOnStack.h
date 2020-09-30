#pragma once
#include <initializer_list>
#include <assert.h>
namespace CommonUtilities
{
	template <typename T, int capacity, typename
		CountType = unsigned short, bool UseSafeModeFlag = true>
		class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<T>& aInitList);
		~VectorOnStack();
		VectorOnStack& operator=(const VectorOnStack&
			aVectorOnStack);
		inline const T& operator[](const CountType aIndex) const;
		inline T& operator[](const CountType aIndex);
		inline void Add(const T& aObject);
		inline void Insert(const CountType aIndex, const T&
			aObject);
		inline void RemoveCyclic(const T& aObject);
		inline void RemoveCyclicAtIndex(const CountType aIndex);
		inline void Clear();
		inline CountType Size() const;
	private:
		T myObjects[capacity];
		CountType mySize;
	};
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		mySize = 0;
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		mySize = aVectorOnStack.Size();
		if (UseSafeModeFlag)
		{
			for (int i = 0; i < mySize; i++)
			{
				myObjects[i] = aVectorOnStack[i];
			}
		}
		else
		{
			for (int i = 0; i < mySize; i++)
			{
				memcpy(&myObjects[i], &aVectorOnStack[i], sizeof(T));
			}
		}
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::VectorOnStack(const std::initializer_list<T>& aInitList)
	{
		assert(aInitList.size() <= capacity && "initilizer list size is above capacity of vector");

		mySize = aInitList.size();

		if (UseSafeModeFlag)
		{
			for (int i = 0; i < mySize; i++)
			{
				myObjects[i] = *(aInitList.begin() + i);
			}
		}
		else
		{
			for (int i = 0; i < mySize; i++)
			{
				memcpy(&myObjects[i], (aInitList.begin() + i), sizeof(T));
			}
		}

	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		mySize = 0;
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<T, capacity, CountType, UseSafeModeFlag>&
		VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		mySize = aVectorOnStack.mySize;
		if (UseSafeModeFlag)
		{
			for (int i = 0; i < mySize; i++)
			{
				myObjects[i] = aVectorOnStack[i];
			}
		}
		else
		{
			for (int i = 0; i < mySize; i++)
			{
				memcpy(&myObjects[i], &aVectorOnStack[i], sizeof(T));
			}
		}
		return *this;
		
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline const T& VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::operator[](const CountType aIndex) const
	{
		assert(aIndex >= 0 && "Index is below zero, Not a a valid number");
		assert(aIndex <= mySize && "Index is above Size of vector");
		return myObjects[aIndex];
		
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline T& VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::operator[](const CountType aIndex)
	{
		assert(aIndex >= 0 && "Index is below zero, Not a a valid number");
		assert(aIndex <= mySize - 1 && "Index is above Size of vector");
		return myObjects[aIndex];
		
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::Add(const T& aObject)
	{
		assert(mySize + 1 <= capacity && "Size is bigger than capacity on this vector on stack");
		if (UseSafeModeFlag)
		{
			
			myObjects[mySize] = aObject;
		}
		else
		{
			memcpy(&myObjects[mySize], &aObject, sizeof(T));
		}
		mySize += 1;
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::Insert(const CountType aIndex, const T& aObject)
	{
		assert(mySize < capacity && "Size is bigger than capacity on this vector on stack");
		assert(aIndex <= mySize && "index is bigger than capacity on this vector on stack");
		if (UseSafeModeFlag)
		{
			for (int i = mySize; i > aIndex; i--)
			{
				myObjects[i] = myObjects[i - 1];
			}
			myObjects[aIndex] = aObject;
		}
		else
		{
			for (int i = mySize; i > aIndex; i--)
			{
				memcpy(&myObjects[i], &myObjects[i - 1], sizeof(T));
			}
			memcpy(&myObjects[aIndex], &aObject, sizeof(T));
		}

		mySize++;
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::RemoveCyclic(const T& aObject)
	{

		assert(mySize >= 2 && "Size is to small for a cyclic remove");
		if (UseSafeModeFlag)
		{
			for (int i = 0; i < mySize; i++)
			{
				if (aObject == myObjects[i])
				{
					myObjects[i] = myObjects[mySize - 1];
					mySize--;
				}
			}
		}
		else
		{
			for (int i = 0; i < mySize; i++)
			{
				if (aObject == myObjects[i])
				{
					memcpy(&myObjects[i], &myObjects[mySize - 1], sizeof(T));
					mySize--;
				}
			}
		}
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(const CountType aIndex)
	{
		assert(mySize > 0 && "Vector is empty");
		assert(aIndex <= mySize - 1 && "index is bigger than the size on this vector on stack");

		if (UseSafeModeFlag)
		{
			myObjects[aIndex] = myObjects[mySize - 1];
		}
		else
		{
			memcpy(&myObjects[aIndex], &(myObjects[mySize - 1]), sizeof(T));
		}
		mySize--;
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::Clear()
	{
		mySize = 0;
	}
	template<typename T, int capacity, typename CountType, bool UseSafeModeFlag>
	inline CountType VectorOnStack<T, capacity, CountType, UseSafeModeFlag>::Size() const
	{
		return mySize;
	}
}
