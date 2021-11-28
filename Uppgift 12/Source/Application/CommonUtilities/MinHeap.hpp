#pragma once
#include <array>
#include "GrowingArray.h"
#include <assert.h>
namespace CommonUtilities
{
	template<class T>
	class MinHeap
	{
	public:
		int GetSize() const; //returnerar antal element i heapen
		int Enqueue(const T& aElement);	  //l�gger till elementet i heapen
		const T& GetTop() const;	  //returnerar det st�rsta elementet i heapen
		T Dequeue(); 	  //tar bort det st�rsta elementet ur heapen och returnerar det
		bool HasValue(const T& aElement);
		void Remake();
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
	inline int MinHeap<T>::GetSize() const
	{
		return myItems.Size();
	}

	template<class T>
	inline int MinHeap<T>::Enqueue(const T& aElement)
	{
		myItems.Add(aElement);
		BubbleUp();
		return myItems.Size() - 1;
	}

	template<class T>
	inline const T& MinHeap<T>::GetTop() const
	{
		assert(myItems.Size() > 0 && "Heap is empty");
		return myItems[0];
	}
	
	template<class T>
	inline T MinHeap<T>::Dequeue()
	{
		assert(myItems.Size() > 0 && "Heap is empty");
		T item = myItems[0];
		myItems[0] = myItems[myItems.Size() - 1];
		myItems.RemoveCyclicAtIndex(myItems.Size() - 1);
		BubbleDown();

		return item;
	}

	template<class T>
	inline bool MinHeap<T>::HasValue(const T& aElement)
	{
		int index = 0;
		while (HasLeftChild(index))
		{
			unsigned int smallerChildIndex = GetLeftChildIndex(index);
			if (HasRightChild(index) && RightChild(index) < LeftChild(index))
			{
				smallerChildIndex = GetRightChildIndex(index);
			}
			if (myItems[index] == aElement)
			{
				return true;
			}
		}
		return false;
	}

	template<class T>
	inline void MinHeap<T>::Remake()
	{
		GrowingArray<T> tempItems = myItems;
		myItems.RemoveAll();
		for (size_t i = 0; i < tempItems.Size(); i++)
		{
			Enqueue(tempItems[i]);
		}
	}
	
	template<class T>
	inline void MinHeap<T>::Swap(const int& aIndexOne, const int& aIndexTwo)
	{
		T temp = myItems[aIndexOne];
		myItems[aIndexOne] = myItems[aIndexTwo];
		myItems[aIndexTwo] = temp;
	}
	
	template<class T>
	inline void MinHeap<T>::BubbleUp()
	{
		unsigned int index = myItems.Size() - 1;
		while (HasParent(index) &&  myItems[index]<Parent(index) )
		{
			Swap(GetParentIndex(index), index);
			index = GetParentIndex(index);
		}
	}
	
	template<class T>
	inline void MinHeap<T>::BubbleDown()
	{
		unsigned int index = 0;
		while (HasLeftChild(index))
		{
			unsigned int smallerChildIndex = GetLeftChildIndex(index);
			if (HasRightChild(index) && RightChild(index)< LeftChild(index))
			{
				smallerChildIndex = GetRightChildIndex(index);
			}
			if (myItems[index]< myItems[smallerChildIndex])
			{
				break;
			}
			else
			{
				Swap(index, smallerChildIndex);
				index = smallerChildIndex;
			}
		}
	}
	
	template<class T>
	inline  int MinHeap<T>::GetLeftChildIndex(const int& aParentIndex)
	{
		return 2 * aParentIndex + 1;
	}
	template<class T>
	inline  int MinHeap<T>::GetRightChildIndex(const int& aParentIndex)
	{
		return 2 * aParentIndex + 2;
	}
	template<class T>
	inline  int MinHeap<T>::GetParentIndex(const int& aChildIndex)
	{
		return (aChildIndex - 1) / 2;
	}
	template<class T>
	inline bool MinHeap<T>::HasLeftChild(const int& aIndex)
	{
		return GetLeftChildIndex(aIndex) < myItems.Size();
	}
	template<class T>
	inline bool MinHeap<T>::HasRightChild(const int& aIndex)
	{
		return GetRightChildIndex(aIndex) < myItems.Size();
	}
	template<class T>
	inline bool MinHeap<T>::HasParent(const int& aIndex)
	{
		return GetParentIndex(aIndex)>=0;
	}
	template<class T>
	inline T MinHeap<T>::LeftChild(const int& aIndex)
	{
		return myItems[GetLeftChildIndex(aIndex)];
	}
	template<class T>
	inline T MinHeap<T>::RightChild(const int& aIndex)
	{
		return myItems[GetRightChildIndex(aIndex)];
	}
	template<class T>
	inline T MinHeap<T>::Parent(const int& aIndex)
	{
		return myItems[GetParentIndex(aIndex)];
	}
}

