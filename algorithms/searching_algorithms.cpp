/*
* Common searching algorithms
* Provided examples with C++'s STL vector
* For detailed information about each algorithm visit: https://www.programiz.com/dsa/
*/

#include <iostream>
#include <vector>

// Binary search
// Time complexity - O(log n)
// Space complexity - O(1);
// iterative implementation
int iterBinarySearch(std::vector<int> &arr, int elem)
{
    int low = 0;
    int high = arr.size() - 1;
    int mid;

    // Repeat until the pointers low and high meet each other
    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == elem)
        {
            return mid;
        }

        if (arr[mid] < elem)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    return -1;
}
// recursive implementation
int recurBinarySearch(std::vector<int> &arr, int elem, int low, int high)
{
    if (!arr.size())
    {
        throw std::runtime_error("BinarySearch: Empty array");
    }

    if (high >= low)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == elem)
        {
            return mid;
        }

        if (arr[mid] > elem)
        {
            return recurBinarySearch(arr, elem, low, mid - 1);
        }
        else
        {
            return recurBinarySearch(arr, elem, mid + 1, high);
        }
    }
    return -1;
}

// Ternary search (works like Binary search, but splits the array in 3 instead)
// Time complexity - O(log3 n)
// Space complexity - O(1);
// iterative implementation
int iterTernarySearch(std::vector<int> &arr, int elem)
{
    int low = 0;
    int high = arr.size() - 1;
    int mid1, mid2;

    // repeat the low and high pointers meet each other
    while (low <= high)
    {
        mid1 = low + (high - low) / 3;
        mid2 = high - (high - low) / 3;

        // check if elem is present at any mid
        if (arr[mid1] == elem)
        {
            return mid1;
        }
        if (arr[mid2] == elem)
        {
            return mid2;
        }

        // since it isn't present, check in which region it is present
        if (elem < arr[mid1])
        {
            // elem is between low and mid1
            high = mid1 - 1;
        }
        else if (elem > arr[mid2])
        {
            // elem is between mid2 and high
            low = mid2 + 1;
        }
        else
        {
            // elem is between mid1 and mid2
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}
// recursive implementation
int recurTernarySearch(std::vector<int> &arr, int elem, int low, int high)
{
    if (!arr.size())
    {
        throw std::runtime_error("TernarySearch: Empty array");
    }

    if (low <= high)
    {
        // find mid1 and mid2
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        // check if elem is present at any mid
        if (arr[mid1] == elem)
        {
            return mid1;
        }
        if (arr[mid2] == elem)
        {
            return mid2;
        }

        // since it isn't present, check in which region it is present
        if (elem < arr[mid1])
        {
            // elem is between low and mid1
            return recurTernarySearch(arr, elem, low, mid1 - 1);
        }
        else if (elem > arr[mid2])
        {
            // elem is between mid2 and high
            return recurTernarySearch(arr, elem, mid2 + 1, high);
        }
        else
        {
            // elem is between mid1 and mid2
            return recurTernarySearch(arr, elem, mid1 + 1, mid2 - 1);
        }
    }
    return -1;
}

// Interpolation Search
// Time complexity - O(log(log n)) // O(n) for worst case
// Space complexity - O(1);
// iterative implementation
int iterInterpolationSearch(std::vector<int> &arr, int elem)
{
    int low = 0;
    int high = arr.size() - 1;
    int pos;

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    while (low <= high && elem >= arr[low] && elem <= arr[high])
    {

        if (low == high)
        {
            if (arr[low] == elem)
                return low;
            return -1;
        }

        // Probing the position with keeping
        // uniform distribution in mind.
        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (elem - arr[low]));

        // Target found
        if (arr[pos] == elem)
        {
            return pos;
        }
        // Target is larger, so it's in the upper part
        if (arr[pos] < elem)
        {
            low = pos + 1;
        }
        // Target is smaller, so it's in the lower part
        else
        {
            high = pos - 1;
        }
    }
    return -1;
}
// recursive implementation
int recurInterpolationSearch(std::vector<int> &arr, int elem, int low, int high)
{
    if (!arr.size())
    {
        throw std::runtime_error("InterpolationSearch: Empty array");
    }
    int pos;

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (low <= high && elem >= arr[low] && elem <= arr[high])
    {
        // Probing the position with keeping
        // uniform distribution in mind.
        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (elem - arr[low]));

        if (arr[pos] == elem)
        {
            return pos;
        }
        if (arr[pos] < elem)
        {
            return recurInterpolationSearch(arr, elem, pos + 1, high);
        }
        if (arr[pos] > elem)
        {
            return recurInterpolationSearch(arr, elem, low, pos - 1);
        }
    }
    return -1;
}
// Works like Binary search, but instead of going to the middle, it goes to a location based on the value of the key

// Quick-Select
// Time complexity - O(n) //Worst case O(n^2)
// Space complexity - O(1)
int partition(std::vector<int> &arr, int low, int high)
{
    // consider last element as pivot
    int pivot = high;
    int i = low;

    for (int j = 0; j <= high - 1; j++)
    {
        // move all smaller elements to the left of the pivot
        // and all larger to the right of it
        if (arr[j] <= arr[pivot])
        {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[pivot], arr[i]);
    return i;
}
int quickSelect(std::vector<int> &arr, int low, int high, int k)
{
    // If k is smaller than number of
    // elements in array
    if (k > 0 && k <= high - low + 1)
    {
        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int idx = partition(arr, low, high);

        // if position is same as k
        // return index of k'th smallest element
        if (idx - low == k - 1)
        {
            return idx;
        }

        // If position is more, recur
        // for left subarray
        if (idx - low > high - 1)
        {
            return quickSelect(arr, low, idx - 1, k);
        }

        // Else recur for right array
        return quickSelect(arr, idx + 1, high, k - idx + low - 1);
    }
    // If k is more than number of
    // elements in array
    return -1;
}
/* This algorithm is used to return k'th smallest element in an unsorted array arr[low...high] using a QuickSort based method.*/
int main()
{
    std::vector<int> testArray = {1, 5, 6, 7, 10, 18, 31, 45, 46, 71, 79, 85, 89, 91, 102, 130, 137};

    // Following calls to the searching functions return the index at which the element is present;

    std::cout << iterBinarySearch(testArray, 89) << "\n";
    std::cout << recurBinarySearch(testArray, 89, 0, testArray.size() - 1) << "\n";
    std::cout << iterTernarySearch(testArray, 89) << "\n";
    std::cout << recurTernarySearch(testArray, 89, 0, testArray.size() - 1) << "\n";
    std::cout << iterInterpolationSearch(testArray, 89) << "\n";
    std::cout << recurInterpolationSearch(testArray, 89, 0, testArray.size() - 1) << "\n";
    std::cout << quickSelect(testArray, 0, testArray.size() - 1, 5) << "\n";
}
