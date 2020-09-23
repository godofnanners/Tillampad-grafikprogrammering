#pragma once
namespace QuickSortTools
{
	
    template<typename T>
    int Partition(std::vector<T>& aVector, int low, int high)
    {
        int pivot = aVector[high]; // pivot  
        int i = (low - 1); // Index of smaller element  

        for (int j = low; j <= high - 1; j++)
        {
            // If current element is smaller than the pivot  
            if (aVector[j] < pivot)
            {
                i++; // increment index of smaller element  
                std::swap(aVector[i], aVector[j]);
            }
        }
        std::swap(aVector[i + 1], aVector[high]);
        return (i + 1);
    }
    template<typename T>
    void QuickSort(std::vector<T>& aVector, int low, int high)
    {
        if (low < high)
        {
            /* pi is partitioning index, arr[p] is now
            at right place */
            int pi = Partition(aVector, low, high);

            // Separately sort elements before  
            // partition and after partition  
            QuickSort(aVector, low, pi - 1);
            QuickSort(aVector, pi + 1, high);
        }
    }
}

namespace CommonUtilities
{
    template<typename T>
    void QuickSort(std::vector<T>& aVector)
    {
        QuickSortTools::QuickSort(aVector,0,aVector.size()-1);
    }
}