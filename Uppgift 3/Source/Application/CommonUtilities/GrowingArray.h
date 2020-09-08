#pragma once
#include <assert.h>
namespace CommonUtilities
{
	template<typename ObjectType, typename SizeType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(SizeType aNrOfRrecommendedItems, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray);

		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);
		GrowingArray& operator=(GrowingArray&& aGrowingArray) noexcept;

		void Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
		inline ObjectType& operator[](const SizeType& aIndex);
		inline const ObjectType& operator[](const SizeType& aIndex) const;

		inline void Add(const ObjectType& aObject);
		inline void Insert(SizeType aIndex, const ObjectType& aObject);
		inline void RemoveCyclic(const ObjectType& aObject);
		inline void RemoveCyclicAtIndex(SizeType aItemNumber);
		inline SizeType Find(const ObjectType& aObject);

		inline ObjectType& GetLast();
		inline const ObjectType& GetLast()const;
		static const SizeType FoundNone = -1;

		inline void RemoveAll();

		void Optimize();
		__forceinline SizeType Size() const;
		inline void Reserve(SizeType aNewSize);
		void Resize(SizeType aNewSize);
	private:
		SizeType myCapacity;
		SizeType mySize;
		ObjectType* myObjects = nullptr;
		bool myUseSafeModeFlag;

	};
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray()
	{
		mySize = 0;
		myCapacity = 0;
		myObjects = nullptr;
		myUseSafeModeFlag = true;
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNrOfRrecommendedItems, bool aUseSafeModeFlag)
	{
		mySize = 0;
		myCapacity = aNrOfRrecommendedItems;
		myUseSafeModeFlag = aUseSafeModeFlag;
		myObjects = new ObjectType[aNrOfRrecommendedItems];
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(const GrowingArray& aGrowingArray)
	{
		if (myObjects != nullptr)
		{
			delete[]myObjects;
		}
		myUseSafeModeFlag = aGrowingArray.myUseSafeModeFlag;
		myCapacity = aGrowingArray.myCapacity;
		myObjects = new ObjectType[myCapacity];
		mySize = aGrowingArray.Size();
		if (myUseSafeModeFlag || aGrowingArray.myUseSafeModeFlag)
		{
			for (SizeType i = 0; i < aGrowingArray.Size(); i++)
			{
				myObjects[i] = aGrowingArray[i];
			}
		}
		else
		{
			memcpy(&myObjects[0], &aGrowingArray.myObjects[0], sizeof(ObjectType) * aGrowingArray.Size());
		}

	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(GrowingArray&& aGrowingArray)
	{
		myUseSafeModeFlag = aGrowingArray.myUseSafeModeFlag;
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;

		myObjects = aGrowingArray.myObjects;

		aGrowingArray.myObjects = nullptr;
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::~GrowingArray()
	{
		delete[] myObjects;
		myObjects = nullptr;
		mySize = 0;
		myCapacity = 0;
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(const GrowingArray<typename ObjectType, typename SizeType>& aGrowingArray)
	{
		if (myObjects != nullptr)
		{
			delete[]myObjects;
		}
		mySize = aGrowingArray.mySize;
		myCapacity = aGrowingArray.myCapacity;
		myObjects = new ObjectType[myCapacity];
		if (myUseSafeModeFlag || aGrowingArray.myUseSafeModeFlag)
		{
			for (SizeType i = 0; i < aGrowingArray.Size(); i++)
			{
				myObjects[i] = aGrowingArray.myObjects[i];
			}
		}
		else
		{
			memcpy(&myObjects, &aGrowingArray.myObjects, sizeof(ObjectType) * aGrowingArray.Size());
		}
		return *this;	// TODO: insert return statement here
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(GrowingArray<typename ObjectType, typename SizeType>&& aGrowingArray) noexcept
	{
		if (myObjects != nullptr)
		{
			delete[]myObjects;
		}
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;

		myObjects = aGrowingArray.myObjects;

		aGrowingArray.myCapacity = 0;
		aGrowingArray.mySize = 0;
		aGrowingArray.myObjects = nullptr;

		return *this;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag)
	{
		myCapacity = aNrOfRecomendedItems;
		myUseSafeModeFlag = aUseSafeModeFlag;
		myObjects = new ObjectType[aNrOfRecomendedItems];
	}
	template<typename ObjectType, typename SizeType>
	inline ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex)
	{
		assert(aIndex >= 0 && "Index is below zero");
		assert(aIndex < mySize && "Index is above size");
		return myObjects[aIndex];
		// TODO: insert return statement here
	}
	template<typename ObjectType, typename SizeType>
	inline const ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex) const
	{
		assert(aIndex >= 0 && "Index is below zero");
		assert(aIndex < mySize && "Index is above size");
		return myObjects[aIndex];
		// TODO: insert return statement here
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Add(const ObjectType& aObject)
	{
		if (mySize + 1 > myCapacity)
		{
			if (myCapacity == 0)
			{
				myCapacity++;
			}
			Reserve(myCapacity * 2);
		}
		if (myUseSafeModeFlag)
		{
			myObjects[mySize] = aObject;
		}
		else
		{
			memcpy(myObjects + mySize, &aObject, sizeof(ObjectType));
		}
		mySize++;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Insert(SizeType aIndex, const ObjectType& aObject)
	{
		assert(aIndex <= mySize && "Index is bigger than size which is out of vectors size range");
		assert(aIndex >= 0 && "Index is negative which is out of vectors size range");
		if (mySize + 1 > myCapacity)
			if (mySize + 1 > myCapacity)
			{
				if (myCapacity == 0)
				{
					myCapacity++;
				}
				Reserve(myCapacity * 2);
			}

		if (myUseSafeModeFlag)
		{
			for (int i = mySize; i > aIndex; i--)
			{
				myObjects[i] = myObjects[i - 1];
			}
			myObjects[aIndex] = aObject;
		}
		else
		{

			memcpy(myObjects + aIndex + 1, myObjects + aIndex, sizeof(ObjectType) * (mySize - aIndex));

			memcpy(myObjects + aIndex, &aObject, sizeof(ObjectType));
		}

		mySize++;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclic(const ObjectType& aObject)
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
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclicAtIndex(SizeType aItemNumber)
	{
		assert(mySize > 0 && "Vector is empty");
		assert(aItemNumber <= mySize - 1 && "index is bigger than the size on this vector on stack");

		myObjects[aItemNumber] = myObjects[mySize - 1];
		mySize--;
	}
	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Find(const ObjectType& aObject)
	{

		for (SizeType i = 0; i < mySize; i++)
		{
			if (myObjects[i] == aObject)
			{
				return i;
			}
		}
		return FoundNone;
	}
	template<typename ObjectType, typename SizeType>
	inline ObjectType& GrowingArray<ObjectType, SizeType>::GetLast()
	{
		return myObjects[mySize - 1];
		// TODO: insert return statement here
	}
	template<typename ObjectType, typename SizeType>
	inline const ObjectType& GrowingArray<ObjectType, SizeType>::GetLast() const
	{
		return myObjects[mySize - 1];
		// TODO: insert return statement here
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveAll()
	{
		mySize = 0;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Optimize()
	{
		ObjectType* tempObjectHolder;
		tempObjectHolder = new ObjectType[mySize];
		for (SizeType i = 0; i < mySize; i++)
		{
			tempObjectHolder[i] = myObjects[i];
		}
		myCapacity = mySize;
		if (myObjects != nullptr)
		{
			delete[]myObjects;
		}

		if (myUseSafeModeFlag)
		{
			myObjects = tempObjectHolder;
		}
		else
		{
			memcpy(&myObjects, &tempObjectHolder, sizeof(ObjectType*));
		}
	}
	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Size() const
	{
		return mySize;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Reserve(SizeType aNewSize)
	{
		assert(aNewSize > mySize && "Error: You're trying to make the vector smaller than the amount of elements in it");
		ObjectType* tempObjectHolder;
		tempObjectHolder = new ObjectType[aNewSize];
		for (SizeType i = 0; i < Size(); i++)
		{
			tempObjectHolder[i] = myObjects[i];
		}
		myCapacity = aNewSize;
		delete[] myObjects;
		myObjects = tempObjectHolder;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Resize(SizeType aNewSize)
	{
		if (aNewSize > myCapacity)
		{
			Reserve(aNewSize * 2);
		}

		for (SizeType i = mySize; i < aNewSize; i++)
		{
			myObjects[i] = ObjectType();
		}
		mySize = aNewSize;
	}
};