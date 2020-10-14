#pragma once
	
namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedListNode
	{
		template <class U>
		friend class DoublyLinkedList;
		
	public:
		// Copy-konstruktorn och assignment-operatorn �r borttagna, s� att det enda
		// s�ttet att skapa en nod �r genom att stoppa in ett v�rde i en lista.
		DoublyLinkedListNode<T>(const DoublyLinkedListNode<T>&) = delete;
		DoublyLinkedListNode<T>& operator=(const DoublyLinkedListNode<T>&) =
			delete;
		// Returnerar nodens v�rde
		const T& GetValue() const;
		T& GetValue();
		// Returnerar n�sta nod i listan, eller nullptr om noden �r sist i listan
		DoublyLinkedListNode<T>* GetNext() const;
		// Returnerar f�reg�ende nod i listan, eller nullptr om noden �r f�rst i
		// listan
		DoublyLinkedListNode<T>* GetPrevious() const;
	private:
		// Konstruktorn och destruktorn �r privat, s� att man inte kan skapa eller
		// ta bort noder utifr�n. List-klassen �r friend, s� att den kan skapa
		// eller ta bort noder.
		
		
		DoublyLinkedListNode(const T& aValue);
		~DoublyLinkedListNode() {}
		T myValue;
		DoublyLinkedListNode* myNextNode;
		DoublyLinkedListNode* myPrevNode;
	};
	template<class T>
	inline const T& DoublyLinkedListNode<T>::GetValue() const
	{
		return myValue;
	}
	template<class T>
	inline T& DoublyLinkedListNode<T>::GetValue()
	{
		return myValue;
	}
	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::GetNext() const
	{
		return myNextNode;
	}
	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::GetPrevious() const
	{
		return myPrevNode;
	}
	template<class T>
	inline DoublyLinkedListNode<T>::DoublyLinkedListNode(const T& aValue)
	{
		myValue = aValue;
		myNextNode = nullptr;
		myPrevNode = nullptr;
	}
}