#pragma once

namespace MergeSortTools
{
	template<typename T>
	void Merge(std::vector<T>& aVector, int aLeft, int aRight, int aIndexDivide)
	{
		int FirstSubVecSize = aIndexDivide - aLeft + 1;
		int SecondSubVecSize = aRight - aIndexDivide;

		std::vector<T> aLeftVec;
		std::vector<T> aRightVec;
		aLeftVec.resize(FirstSubVecSize);
		aRightVec.resize(SecondSubVecSize);

		for (int i = 0; i < FirstSubVecSize; i++)
		{
			aLeftVec[i] = aVector[aLeft + i];
		}

		for (int j = 0; j < SecondSubVecSize; j++)
		{
			aRightVec[j] = aVector[aIndexDivide + 1 + j];
		}

		int FirstSubVectorIndex = 0; // Initial index of first subarray 
		int SecondSubVectorIndex = 0; // Initial index of second subarray 
		int MergedSubVectorIndex = aLeft; // Initial index of merged subarray 
		while (FirstSubVectorIndex < FirstSubVecSize && SecondSubVectorIndex < SecondSubVecSize)
		{
			if (aLeftVec[FirstSubVectorIndex] < aRightVec[SecondSubVectorIndex] || 
				(!(aLeftVec[FirstSubVectorIndex] < aRightVec[SecondSubVectorIndex]) && !(aRightVec[SecondSubVectorIndex] < aLeftVec[FirstSubVectorIndex])) )
			{
				aVector[MergedSubVectorIndex] = aLeftVec[FirstSubVectorIndex];
				FirstSubVectorIndex++;
			}
			else
			{
				aVector[MergedSubVectorIndex] = aRightVec[SecondSubVectorIndex];
				SecondSubVectorIndex++;
			}
			MergedSubVectorIndex++;
		}

		while (FirstSubVectorIndex < FirstSubVecSize)
		{
			aVector[MergedSubVectorIndex] = aLeftVec[FirstSubVectorIndex];
			FirstSubVectorIndex++;
			MergedSubVectorIndex++;
		}

		while (SecondSubVectorIndex < SecondSubVecSize)
		{
			aVector[MergedSubVectorIndex] = aRightVec[SecondSubVectorIndex];
			SecondSubVectorIndex++;
			MergedSubVectorIndex++;
		}
	}

	template<typename T>
	void Divide(std::vector<T>& aVector, int aLeft, int aRight)
	{
		if (aLeft < aRight)
		{
			int nextIndexDivide = aLeft + (aRight - aLeft) / 2;
			Divide(aVector, aLeft, nextIndexDivide);
			Divide(aVector, nextIndexDivide + 1, aRight);
			Merge(aVector, aLeft, aRight, nextIndexDivide);
		}
	}
}

namespace CommonUtilities
{
	template<typename T>
	void MergeSort(std::vector<T>& aVector)
	{
		MergeSortTools::Divide(aVector, 0, aVector.size() - 1);
	}
}