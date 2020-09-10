#pragma once
#include <array>
#include "GrowingArray.h"
#include <assert.h>
namespace CommonUtilities
{
	template<class T>
	class Heap
	{
	public:
		int GetSize() const; //returnerar antal element i heapen
		void Enqueue(const T& aElement);	  //lägger till elementet i heapen
		const T& GetTop() const;	  //returnerar det största elementet i heapen
		T Dequeue(); 	  //tar bort det största elementet ur heapen och returnerar det
	private:
		GrowingArray<T> myItems;
		int GetLeftChildIndex(const int& aParentIndex);
		int GetRightChildIndex(const int& aParentIndex);
		int GetParentIndex(const int& aChildIndex);

		bool HasLeftChild(const int& index);
		bool HasRightChild(const int& index);
		bool HasParent(const int& index);

		T LeftChild(const int& aIndex);
		T RightChild(const int& aIndex);
		T Parent(const int& aIndex);

		void Swap(const int& aIndexOne, const int& aIndexTwo);
		void BubbleUp();
		void BubbleDown();
	};

	template<class T>
	inline int Heap<T>::GetSize() const
	{
		return myItems.Size();
	}

	template<class T>
	inline void Heap<T>::Enqueue(const T& aElement)
	{
		myItems.Add(aElement);
		BubbleUp();
	}

	template<class T>
	inline const T& Heap<T>::GetTop() const
	{
		assert(myItems.Size() > 0 && "Heap is empty");
		return myItems[0];
	}
	
	template<class T>
	inline T Heap<T>::Dequeue()
	{
		assert(myItems.Size() > 0 && "Heap is empty");
		T item = myItems[0];
		myItems[0] = myItems[myItems.Size() - 1];
		myItems.RemoveCyclicAtIndex(myItems.Size() - 1);
		BubbleDown();

		return item;
	}
	
	template<class T>
	inline void Heap<T>::Swap(const int& aIndexOne, const int& aIndexTwo)
	{
		T temp = myItems[aIndexOne];
		myItems[aIndexOne] = myItems[aIndexTwo];
		myItems[aIndexTwo] = temp;
	}
	
	template<class T>
	inline void Heap<T>::BubbleUp()
	{
		unsigned int index = myItems.Size() - 1;
		while (HasParent(index) && Parent(index) < myItems[index])
		{
			Swap(GetParentIndex(index), index);
			index = GetParentIndex(index);
		}
	}
	
	template<class T>
	inline void Heap<T>::BubbleDown()
	{
		unsigned int index = 0;
		while (HasLeftChild(index))
		{
			unsigned int biggerChildIndex = GetLeftChildIndex(index);
			if (HasRightChild(index) && LeftChild(index) < RightChild(index))
			{
				biggerChildIndex = GetRightChildIndex(index);
			}
			if (myItems[biggerChildIndex] < myItems[index])
			{
				break;
			}
			else
			{
				Swap(index, biggerChildIndex);
				index = biggerChildIndex;
			}
		}
	}
	
	template<class T>
	inline  int Heap<T>::GetLeftChildIndex(const int& aParentIndex)
	{
		return 2 * aParentIndex + 1;
	}
	template<class T>
	inline  int Heap<T>::GetRightChildIndex(const int& aParentIndex)
	{
		return 2 * aParentIndex + 2;
	}
	template<class T>
	inline  int Heap<T>::GetParentIndex(const int& aChildIndex)
	{
		return (aChildIndex - 1) / 2;
	}
	template<class T>
	inline bool Heap<T>::HasLeftChild(const int& aIndex)
	{
		return GetLeftChildIndex(aIndex) < myItems.Size();
	}
	template<class T>
	inline bool Heap<T>::HasRightChild(const int& aIndex)
	{
		return GetRightChildIndex(aIndex) < myItems.Size();
	}
	template<class T>
	inline bool Heap<T>::HasParent(const int& aIndex)
	{
		return GetParentIndex(aIndex)>=0;
	}
	template<class T>
	inline T Heap<T>::LeftChild(const int& aIndex)
	{
		return myItems[GetLeftChildIndex(aIndex)];
	}
	template<class T>
	inline T Heap<T>::RightChild(const int& aIndex)
	{
		return myItems[GetRightChildIndex(aIndex)];
	}
	template<class T>
	inline T Heap<T>::Parent(const int& aIndex)
	{
		return myItems[GetParentIndex(aIndex)];
	}
}

