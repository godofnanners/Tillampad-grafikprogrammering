#pragma once
namespace SelectionSortTools
{
	template<typename T>
	void Swap(T& aNumber1, T& aNumber2)
	{
		int temp = aNumber1;
		aNumber1 = aNumber2;
		aNumber2 = temp;

	}
}

namespace CommonUtilities
{
	template<typename T>
	void SelectionSort(std::vector<T>& aVector)
	{
		int min_index;

		for (int i = 0; i < aVector.size() - 1; i++)
		{
			min_index = i;
			for (int j = i + 1; j < aVector.size(); j++)
			{
				if (aVector[j] < aVector[min_index])
				min_index = j;
			}  
			std::swap(aVector[min_index], aVector[i]);
		}
	}
}