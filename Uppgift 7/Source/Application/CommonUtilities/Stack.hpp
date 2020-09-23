#pragma once
#include "GrowingArray.h"
#include <assert.h>
namespace CommonUtilities
{
	template <class T>
	class Stack
	{
	public:
		//Skapar en tom stack
		Stack();
		//Returnerar antal element i stacken
		int GetSize() const;
		//Returnerar det �versta elementet i stacken. Kraschar med en assert om
		//stacken �r tom.
		const T& GetTop() const;
		//Returnerar det �versta elementet i stacken. Kraschar med en assert om
		//stacken �r tom.
		T& GetTop();
		//L�gger in ett nytt element �verst p� stacken
		void Push(const T& aValue);
		//Tar bort det �versta elementet fr�n stacken och returnerar det. Kraschar
		//med en assert om stacken �r tom.
		T Pop();
	private:
		CommonUtilities::GrowingArray<T>myStack;
	};

	template<class T>
	inline Stack<T>::Stack()
	{
		myStack = CommonUtilities::GrowingArray<T>();
	}

	template<class T>
	inline int Stack<T>::GetSize() const
	{
		return myStack.Size();
	}

	template<class T>
	inline const T& Stack<T>::GetTop() const
	{
		assert(myStack.Size() > 0 && "Your stack is empty");
		return myStack.GetLast();
		// TODO: insert return statement here
	}

	template<class T>
	inline T& Stack<T>::GetTop()
	{
		assert(myStack.Size() > 0 && "Your stack is empty");

		return myStack.GetLast();
		// TODO: insert return statement here
	}

	template<class T>
	inline void Stack<T>::Push(const T& aValue)
	{
		myStack.Add(aValue);
	}

	template<class T>
	inline T Stack<T>::Pop()
	{
		assert(myStack.Size() > 0 && "Your stack is empty");
		T firstValueOnStack = myStack.GetLast();
		myStack.RemoveCyclicAtIndex(myStack.Size()-1);
		return firstValueOnStack;
	}
}