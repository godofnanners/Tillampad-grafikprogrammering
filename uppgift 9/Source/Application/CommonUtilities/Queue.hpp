#pragma once
#include "GrowingArray.h"
#include <assert.h>
namespace CommonUtilities {

	template <class T>
	class Queue
	{
	public:
		//Skapar en tom kö
		Queue();
		//Returnerar antal element i kön
		int GetSize() const;
		//Returnerar elementet längst fram i kön. Kraschar med en assert om kön är
		//tom
		const T& GetFront() const;
		//Returnerar elementet längst fram i kön. Kraschar med en assert om kön är
		//tom
		T& GetFront();
		//Lägger in ett nytt element längst bak i kön
		void Enqueue(const T& aValue);
		//Tar bort elementet längst fram i kön och returnerar det. Kraschar med en
		//assert om kön är tom.
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