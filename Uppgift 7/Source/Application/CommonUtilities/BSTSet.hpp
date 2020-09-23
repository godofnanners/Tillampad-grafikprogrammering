#pragma once
//node
namespace CommonUtilities
{
	template <class T>
	class BSTSetNode
	{
	public:
		BSTSetNode(const BSTSetNode&) = delete;
		BSTSetNode& operator=(const BSTSetNode&) = delete;
		const T& GetData() const;

		const BSTSetNode<T>* GetLeft() const;
		const BSTSetNode<T>* GetRight() const;

	private:
		BSTSetNode<T>() {};
		template <class U>
		friend class BSTSet;
		BSTSetNode(T aValue);
		~BSTSetNode() {};
		T myValue;
		BSTSetNode<T>* myRightNode;
		BSTSetNode<T>* myLeftNode;
	};

	template<class T>
	inline const T& BSTSetNode<T>::GetData() const
	{
		return myValue;
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSetNode<T>::GetLeft() const
	{
		return myLeftNode;
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSetNode<T>::GetRight() const
	{
		return myRightNode;
	}

	template<class T>
	inline BSTSetNode<T>::BSTSetNode(T aValue)
	{
		myValue = aValue;
		myRightNode = nullptr;
		myLeftNode = nullptr;
	}

	template <class T>
	class BSTSet
	{
	public:
		BSTSet();
		~BSTSet();
		const BSTSetNode<T>* GetRoot() const;
		//Returnerar true om elementet finns i mängden, och false annars.
		bool HasElement(const T& aValue);
		//Stoppar in elementet i mängden, om det inte redan finns där. Gör
		//ingenting annars.
		void Insert(const T& aValue);
		//Plockar bort elementet ur mängden, om det finns. Gör ingenting annars.
		void Remove(const T& aValue);
		void DSWBalance();
	private:
		BSTSetNode<T>* RotateRight(BSTSetNode<T>* aGrandparent, BSTSetNode<T>* aParent, BSTSetNode<T>* aLeftChild);
		void RotateLeft(BSTSetNode<T>* aGrandparent, BSTSetNode<T>* aParent, BSTSetNode<T>* aRightChild);
		void CreateBackbone();
		void CreateBalancedTree();
		void MakeBalancingRotations(int aBound);
		int GreatestPowerOf2LessThanN(int aN);
		int MSB(int n);
		BSTSetNode<T>* myRootNode;
	};

	template<class T>
	inline BSTSet<T>::BSTSet()
	{
		myRootNode = nullptr;
	}

	template<class T>
	inline BSTSet<T>::~BSTSet()
	{
	}

	template<class T>
	inline const BSTSetNode<T>* BSTSet<T>::GetRoot() const
	{
		return myRootNode;
	}

	template<class T>
	inline bool BSTSet<T>::HasElement(const T& aValue)
	{
		BSTSetNode<T>* Node = myRootNode;
		while (Node != nullptr)
		{
			if (!(Node->myValue < aValue) && !(aValue < Node->myValue))
			{
				return true;
			}
			else if (aValue < Node->myValue)
			{
				Node = Node->myLeftNode;
			}
			else
			{
				Node = Node->myRightNode;
			}
		}
		return false;
	}

	template<class T>
	inline void BSTSet<T>::Insert(const T& aValue)
	{

		if (myRootNode == nullptr)
		{
			myRootNode = new BSTSetNode<T>(aValue);
		}
		else
		{
			BSTSetNode<T>* Node = myRootNode;
			while (!(!(Node->myValue < aValue) && !(aValue < Node->myValue)))
			{
				if (aValue < Node->myValue)
				{
					if (Node->myLeftNode == nullptr)
					{
						Node->myLeftNode = new BSTSetNode<T>(aValue);
					}
					Node = Node->myLeftNode;
				}
				else if (Node->myValue < aValue)
				{
					if (Node->myRightNode == nullptr)
					{
						Node->myRightNode = new BSTSetNode<T>(aValue);
					}
					Node = Node->myRightNode;
				}
			}
		}
	}

	template<class T>
	inline void BSTSet<T>::Remove(const T& aValue)
	{
		if (myRootNode == nullptr)
			return;
		BSTSetNode<T>* prevNode = nullptr;
		BSTSetNode<T>* steppingNode = myRootNode;
		BSTSetNode<T>* removeValueNode = nullptr;
		//Find Node
		while (!(!(steppingNode->myValue < aValue) && !(aValue < steppingNode->myValue)))
		{
			if (steppingNode->myValue < aValue)
			{
				if (steppingNode->myRightNode != nullptr)
				{
					prevNode = steppingNode;
					steppingNode = steppingNode->myRightNode;
				}
				else
				{
					return;
				}
			}
			else
			{
				if (steppingNode->myLeftNode != nullptr)
				{
					prevNode = steppingNode;
					steppingNode = steppingNode->myLeftNode;
				}
				else
				{
					return;
				}
			}
		}
		removeValueNode = steppingNode;

		//Delete Node
		if (steppingNode->myLeftNode == nullptr && steppingNode->myRightNode == nullptr)
		{
			//if both nodes below are empty
			if (removeValueNode != myRootNode)
			{
				if (prevNode->myLeftNode == removeValueNode)
				{
					delete removeValueNode;
					prevNode->myLeftNode = nullptr;
				}
				else
				{
					delete removeValueNode;
					prevNode->myRightNode = nullptr;
				}
			}
			else
			{
				delete myRootNode;
				myRootNode = nullptr;
			}
		}
		else if (steppingNode->myLeftNode != nullptr && steppingNode->myRightNode == nullptr)
		{
			//if only right node is empty
			if (removeValueNode != myRootNode)
			{
				if (prevNode->myLeftNode == removeValueNode)
				{
					prevNode->myLeftNode = steppingNode->myLeftNode;
				}
				else
				{
					prevNode->myRightNode = steppingNode->myLeftNode;
				}
			}
			else
			{
				myRootNode = steppingNode->myLeftNode;
			}
			delete removeValueNode;
		}
		else if (steppingNode->myLeftNode == nullptr && steppingNode->myRightNode != nullptr)
		{
			//if only left node is empty
			if (removeValueNode != myRootNode)
			{
				if (prevNode->myLeftNode == removeValueNode)
				{
					prevNode->myLeftNode = steppingNode->myRightNode;
				}
				else
				{
					prevNode->myRightNode = steppingNode->myRightNode;
				}
			}
			else
			{
				myRootNode = steppingNode->myRightNode;
			}
			delete removeValueNode;
		}
		else
		{
			//if both nodes are occupied

			//step right once and then find the most left node in the branch of the node that is to be deleted
			prevNode = steppingNode;
			steppingNode = steppingNode->myRightNode;

			while (steppingNode->myLeftNode != nullptr)
			{
				prevNode = steppingNode;
				steppingNode = steppingNode->myLeftNode;
			}

			removeValueNode->myValue = steppingNode->myValue;

			if (steppingNode->myRightNode != nullptr)
			{
				if (prevNode->myLeftNode == steppingNode)
				{
					prevNode->myLeftNode = steppingNode->myRightNode;
					delete steppingNode;
				}
				else
				{
					prevNode->myRightNode = steppingNode->myRightNode;
					delete steppingNode;
				}
			}
			else
			{
				if (prevNode->myLeftNode == steppingNode)
				{
					delete steppingNode;
					prevNode->myLeftNode = nullptr;
				}
				else
				{
					delete steppingNode;
					prevNode->myRightNode = nullptr;
				}
			}
		}
	}

	template<class T>
	inline void BSTSet<T>::DSWBalance()
	{
		CreateBackbone();
		CreateBalancedTree();
	}

	template<class T>
	inline BSTSetNode<T>* BSTSet<T>::RotateRight(BSTSetNode<T>* aGrandparent, BSTSetNode<T>* aParent, BSTSetNode<T>* aLeftChild)
	{
		if (nullptr != aGrandparent)
		{
			aGrandparent->myRightNode = aLeftChild;
		}
		else
		{
			myRootNode = aLeftChild;
		}
		aParent->myLeftNode = aLeftChild->myRightNode;
		aLeftChild->myRightNode = aParent;
		return aGrandparent;
	}

	template<class T>
	inline void BSTSet<T>::RotateLeft(BSTSetNode<T>* aGrandparent, BSTSetNode<T>* aParent, BSTSetNode<T>* aRightChild)
	{
		if (nullptr != aGrandparent)
		{
			aGrandparent->myRightNode = aRightChild;
		}
		else
		{
			myRootNode = aRightChild;
		}
		aParent->myRightNode = aRightChild->myLeftNode;
		aRightChild->myLeftNode = aParent;
	}

	template<class T>
	inline void BSTSet<T>::CreateBackbone()
	{
		BSTSetNode<T>* grandParent = nullptr;
		BSTSetNode<T>* parent = myRootNode;
		BSTSetNode<T>* leftChild;

		while (nullptr != parent)
		{
			leftChild = parent->myLeftNode;
			if (nullptr != leftChild)
			{
				grandParent = RotateRight(grandParent, parent, leftChild);
				parent = leftChild;
			}
			else
			{
				grandParent = parent;
				parent = parent->myRightNode;
			}
		}
	}
	template<class T>
	inline void BSTSet<T>::CreateBalancedTree()
	{
		int n = 0;
		for (BSTSetNode<T>* tmp = myRootNode; nullptr != tmp; tmp = tmp->myRightNode)
		{
			n++;
		}
		//m = 2^floor[lg(n+1)]-1, ie the greatest power of 2 less than n: minus 1
		int m = GreatestPowerOf2LessThanN(n + 1) - 1;
		MakeBalancingRotations(n - m);

		while (m > 1)
		{
			MakeBalancingRotations(m /= 2);
		}
	}
	template<class T>
	inline void BSTSet<T>::MakeBalancingRotations(int aBound)
	{
		BSTSetNode<T>* grandParent = nullptr;
		BSTSetNode<T>* parent = myRootNode;
		BSTSetNode<T>* child = myRootNode->myRightNode;
		for (; aBound > 0; aBound--)
		{
				if (nullptr != child)
				{
					RotateLeft(grandParent, parent, child);
					grandParent = child;
					parent = grandParent->myRightNode;
					child = parent->myRightNode;
				}
				else
				{
					break;
				}
		}
	}
	template<class T>
	inline int BSTSet<T>::GreatestPowerOf2LessThanN(int aN)
	{
		int x = MSB(aN);//MSB
		return (1 << x);//2^x
	}
	template<class T>
	inline int BSTSet<T>::MSB(int n)
	{
		int ndx = 0;
		while (1 < n)
		{
			n = (n >> 1);
			ndx++;
		}
		return ndx;
	}
}


