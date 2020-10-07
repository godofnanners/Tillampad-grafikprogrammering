#pragma once
#include "DoublyLinkedListNode.hpp"
namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList
	{
	public:
		// Skapar en tom lista
		DoublyLinkedList();
		// Frigör allt minne som listan allokerat
		~DoublyLinkedList();
		// Returnerar antalet element i listan
		int GetSize() const;
		// Returnerar första noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T>* GetFirst();
		// Returnerar sista noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T>* GetLast();
		// Skjuter in ett nytt element först i listan
		void InsertFirst(const T& aValue);
		// Skjuter in ett nytt element sist i listan
		void InsertLast(const T& aValue);
		// Skjuter in ett nytt element innan aNode
		void InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue);
		// Skjuter in ett nytt element efter aNode
		void InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue);
		// Plockar bort noden ur listan och frigör minne. (Det är ok att anta att
		// aNode är en nod i listan, och inte från en annan lista)
		void Remove(DoublyLinkedListNode<T>* aNode);
		// Hittar första elementet i listan som har ett visst värde. Jämförelsen
		// görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T>* FindFirst(const T& aValue);
		// Hittar sista elementet i listan som har ett visst värde. Jämförelsen
		// görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T>* FindLast(const T& aValue);
		// Plockar bort första elementet i listan som har ett visst värde.
		// Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
		// Returnerar true om ett element plockades bort, och false annars.
		bool RemoveFirst(const T& aValue);
		// Plockar bort sista elementet i listan som har ett visst värde.
		// Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
		// Returnerar true om ett element plockades bort, och false annars.
		bool RemoveLast(const T& aValue);
	private:
		DoublyLinkedListNode<T>* myFirst;
		DoublyLinkedListNode<T>* myLast;
		unsigned int mySize;
	};

	template<class T>
	inline DoublyLinkedList<T>::DoublyLinkedList()
	{
		mySize = 0;
		myFirst = NULL;
		myLast = NULL;
	}

	template<class T>
	inline DoublyLinkedList<T>::~DoublyLinkedList()
	{
		DoublyLinkedListNode<T>* node = myFirst;
		DoublyLinkedListNode<T>* SecondNode = nullptr;
		for (unsigned int i = 0; i < mySize; i++)
		{
			SecondNode = node->myNextNode;
			delete node;
			node = SecondNode;
		}
		node = nullptr;
		SecondNode = nullptr;
	}

	template<class T>
	inline int DoublyLinkedList<T>::GetSize() const
	{
		return mySize;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::GetFirst()
	{
		return myFirst;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::GetLast()
	{
		return myLast;
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
		node->myPrevNode = NULL;
		node->myNextNode = myFirst;
		if (mySize > 0)
		{
			myFirst->myPrevNode = node;
		}
		else
		{
			myLast = node;
		}
		myFirst = node;
		++mySize;
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
		node->myPrevNode = myLast;
		node->myNextNode = NULL;
		if (mySize > 0)
		{
			myLast->myNextNode = node;
		}
		else
		{
			myFirst = node;
		}
		myLast = node;
		++mySize;
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue)
	{
		if (aNode != myFirst)
		{
			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
			node->myPrevNode = aNode->myPrevNode;
			node->myNextNode = aNode;
			aNode->myPrevNode->myNextNode = node;
			aNode->myPrevNode = node;
			++mySize;
		}
		else
		{
			InsertFirst(aValue);
		}
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue)
	{
		if (aNode != myLast)
		{
			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
			node->myPrevNode = aNode;
			node->myNextNode = aNode->myNextNode;
			aNode->myNextNode->myPrevNode = node;
			aNode->myNextNode = node;
			++mySize;
		}
		else
		{
			InsertLast(aValue);
		}
	}

	template<class T>
	inline void DoublyLinkedList<T>::Remove(DoublyLinkedListNode<T>* aNode)
	{
		if (mySize == 1)
		{
			myFirst = nullptr;
			myLast = nullptr;
		}
		else if (aNode == myFirst)
		{
			aNode->myNextNode->myPrevNode = NULL;
			myFirst = aNode->myNextNode;
		}
		else if (aNode == myLast)
		{
			aNode->myPrevNode->myNextNode = NULL;
			myLast = aNode->myPrevNode;
		}
		else
		{
			aNode->myNextNode->myPrevNode = aNode->myPrevNode;
			aNode->myPrevNode->myNextNode = aNode->myNextNode;
		}
		--mySize;
		delete aNode;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::FindFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = myFirst;
		for (size_t i = 0; i < mySize; i++)
		{
			if (node->myValue == aValue)
			{
				return node;
			}
			else
			{
				node = node->myNextNode;
			}
		}
		return nullptr;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::FindLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = myLast;
		for (int i = mySize - 1; i >= 0; i--)
		{
			if (node->myValue == aValue)
			{
				return node;
			}
			else
			{
				node = node->myPrevNode;
			}
		}
		return nullptr;
	}

	template<class T>
	inline bool DoublyLinkedList<T>::RemoveFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = myFirst;
		for (int i = 0; i < mySize; i++)
		{
			if (node->myValue == aValue)
			{
				Remove(node);
				return true;
			}
			else
			{
				node = node->myNextNode;
			}
		}
		return false;
	}

	template<class T>
	inline bool DoublyLinkedList<T>::RemoveLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = myLast;
		for (int i = mySize - 1; i >= 0; i--)
		{
			if (node->myValue == aValue)
			{
				Remove(node);
				return true;
			}
			else
			{
				node = node->myPrevNode;
			}
		}
		return false;
	}

}