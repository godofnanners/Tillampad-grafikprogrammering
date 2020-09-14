#pragma once
#include "GrowingArray.h"
#include <assert.h>
namespace CommonUtilities {

	template <class T>
	class Queue
	{
	public:
		//Skapar en tom k�
		Queue();
		//Returnerar antal element i k�n
		int GetSize() const;
		//Returnerar elementet l�ngst fram i k�n. Kraschar med en assert om k�n �r
		//tom
		const T& GetFront() const;
		//Returnerar elementet l�ngst fram i k�n. Kraschar med en assert om k�n �r
		//tom
		T& GetFront();
		//L�gger in ett nytt element l�ngst bak i k�n
		void Enqueue(const T& aValue);
		//Tar bort elementet l�ngst fram i k�n och returnerar det. Kraschar med en
		//assert om k�n �r tom.
		T Dequeue();
	private:
		CommonUtilities::GrowingArray<T>myQueue;
	};

	template<class T>
	inline Queue<T>::Queue()
	{
		myQueue = CommonUtilities::GrowingArray<T>();
	}

	template<class T>
	inline int Queue<T>::GetSize() const
	{
		return myQueue.Size();
	}

	template<class T>
	inline const T& Queue<T>::GetFront() const
	{
		assert(myQueue.Size() > 0 && "Your queue is empty");
		return myQueue.GetLast();
		// TODO: insert return statement here
	}

	template<class T>
	inline T& Queue<T>::GetFront()
	{
		assert(myQueue.Size() > 0 && "Your queue is empty");
		return myQueue.GetLast();
		// TODO: insert return statement here
	}

	template<class T>
	inline void Queue<T>::Enqueue(const T& aValue)
	{
		myQueue.Insert(0, aValue);
	}

	template<class T>
	inline T Queue<T>::Dequeue()
	{
		assert(myQueue.Size() > 0 && "Your queue is empty");
		T FirstQueueValue = myQueue.GetLast();
		myQueue.RemoveCyclicAtIndex(myQueue.Size()-1);
		return FirstQueueValue;
	}

}