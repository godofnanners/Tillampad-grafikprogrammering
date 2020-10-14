#pragma once

namespace CommonUtilities
{

	template<typename T>
	void BubbleSort(std::vector<T>& aVector)
	{
		bool swapped;
		for (size_t i = 0; i < aVector.size() - 1; i++)
		{
			swapped = false;
			for (size_t j = 0; j < aVector.size() - i - 1; j++)
			{
				if (aVector[j + 1] < aVector[j])
				{
					std::swap(aVector[j], aVector[j + 1]);
					swapped = true;
				}
			}
			if (swapped == false)
			{
				break;
			}
		}
	}

}