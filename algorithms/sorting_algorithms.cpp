/*
 * Common sorting algorithms
 * Provided examples with C++'s STL vector
 * For detailed information about each algorithm visit: https://www.programiz.com/dsa/sorting-algorithm
 */

#include <iostream>
#include <vector>

void printArr(std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// get largest element in an array
int getMax(std::vector<int> &arr)
{
    if (!arr.size())
    {
        throw std::runtime_error("Empty array!");
    }

    int max = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

//__________________ Slow sorting algorithms __________________

// Optimized bubble sort
// Time complexity - O(n^2)
// Space Complexity - O(1)
// Stability - Yes
void bubbleSort(std::vector<int> &arr)
{
    // loop to access each array element
    for (int i = 0; i < arr.size(); i++)
    {
        // check if swapping occurs
        bool swapped = 0;
        // loop to compare array elements
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            // compare two adjacent elements
            // change > to < to sort in descending order
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = 1;
            }
        }
        // no swapping means the array is already sorted
        // so no need of further comparison
        if (!swapped)
        {
            break;
        }
    }
}

// Selection sort
// Time complexity - O(n^2)
// Space Complexity - O(1)
// Stability - No
void selectionSort(std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int minimumIdx = i;
        for (int j = i; j < arr.size(); j++)
        {
            // To sort in descending order, change > to < in this line.
            // Select the minimum element in each loop.
            if (arr[minimumIdx] > arr[j])
            {
                minimumIdx = j;
            }
        }
        // put min at the correct position
        std::swap(arr[minimumIdx], arr[i]);
    }
}

// Insertion sort (Best among all slow sorting alogorithms)
// Time complexity - O(n^2)
// Space Complexity - O(1)
// Stability - Yes
void insertionSort(std::vector<int> &arr)
{
    for (int step = 1; step < arr.size(); step++)
    {
        int key = arr[step];
        int j = step - 1;

        // Compare key with each element on the left of it until an element smaller than
        // it is found.
        // For descending order, change key<array[j] to key>array[j].
        while (key < arr[j] && j >= 0)
        {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

//__________________ Fast sorting algorithms __________________

// Merge sort
// Time complexity - O(n*log n)
// Space Complexity - O(n)
// Stability - Yes
void mergeSort(std::vector<int> &arr)
{
    if (arr.size() > 1)
    {
        int mid = arr.size() / 2;

        // Create leftHalf ← arr[p..q] and rightHalf ← arr[q+1..r]
        std::vector<int> leftHalf(arr.begin(), arr.begin() + mid);
        std::vector<int> rightHalf(arr.begin() + mid, arr.begin() + arr.size());

        mergeSort(leftHalf);
        mergeSort(rightHalf);

        // Maintain current index of sub-arrays and main array
        int i = 0;
        int j = 0;
        int k = 0;

        // Until we reach either end of either leftHalf or rightHalf, pick larger among
        // elements leftHalf and rightHalf and place them in the correct position at arr[p..r]
        while (i < leftHalf.size() && j < rightHalf.size())
        {
            if (leftHalf[i] < rightHalf[j])
            {
                arr[k] = leftHalf[i];
                i++;
            }
            else
            {
                arr[k] = rightHalf[j];
                j++;
            }
            k++;
        }

        // When we run out of elements in either leftHalf or rightHalf,
        // pick up the remaining elements and put them in arr[p..r]
        while (i < leftHalf.size())
        {
            arr[k] = leftHalf[i];
            i++;
            k++;
        }

        while (j < rightHalf.size())
        {
            arr[k] = rightHalf[j];
            j++;
            k++;
        }
    }
}

// Quick sort
// Time complexity - O(n*log n) // If array is already sorted time complexity rises to O(n^2)
// Space Complexity - O(log n)
// Stability - No
int Partition(std::vector<int> &arr, int start, int end)
{
    int pivot = end;
    int j = start;
    for (int i = start; i < end; ++i)
    {
        if (arr[i] < arr[pivot])
        {
            std::swap(arr[i], arr[j]);
            ++j;
        }
    }
    std::swap(arr[j], arr[pivot]);
    return j;
}
void quickSort(std::vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int p = Partition(arr, start, end);
        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }
}

// Counting sort (Doesn't work for arrays with negative integers)
// Time complexity - O(n + k)
// Space Complexity - O(n + k)
// Stability - Yes
void countingSort(std::vector<int> &arr)
{
    // find the largest element in the array
    int max = getMax(arr);

    // initialize new output array
    std::vector<int> output(arr.size(), 0);

    // initialize count array with all zeros
    std::vector<int> count(max + 1, 0);

    // Store the count of each element
    for (int i = 0; i < arr.size(); i++)
    {
        count[arr[i]]++;
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = output[i];
    }
}
/*One approach to making it work with negatives is to keep them in a separate array and
make them positive, use counting sort on them and reverse them, then add them back to the original array*/

// Radix Sort (Uses counting sort)
// Time complexity - O(n + k)
// Space Complexity - O(d*(n + b))
// Stability - Yes
//'b' is base (in our case b = 10)
//'d' is the number of digits in the largest element
void rCountingSort(std::vector<int> &arr, int place)
{
    const int max = 10;
    // initialize new output array
    std::vector<int> output(arr.size(), 0);
    // initialize count array with all zeros
    std::vector<int> count(max + 1, 0);

    // Calculate count of elements
    for (int i = 0; i < arr.size(); i++)
    {
        count[(arr[i] / place) % 10]++;
    }

    // Calculate cumulative count
    for (int i = 1; i < max; i++)
    {
        count[i] += count[i - 1];
    }

    // Place the elements in sorted order
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--;
    }

    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = output[i];
    }
}
void radixSort(std::vector<int> &arr)
{
    // find largest element in the array
    int max = getMax(arr);

    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10)
    {
        rCountingSort(arr, place);
    }
}

// Heap sort
// Time complexity - O(n*log n)
// Space Complexity - O(1)
// Stability - No
void heapify(std::vector<int> &arr, int idx, int size)
{
    // Find largest among root, left child and right child
    int largest = idx;
    int left = (idx * 2) + 1;
    int right = left + 1;

    if (left < size && arr[largest] < arr[left])
    {
        largest = left;
    }

    if (right < size && arr[largest] < arr[right])
    {
        largest = right;
    }

    // Swap and continue heapifying if root is not largest
    if (largest != idx)
    {
        std::swap(arr[largest], arr[idx]);
        heapify(arr, largest, size);
    }
}
void heapSort(std::vector<int> &arr)
{
    int size = arr.size();
    // create max heap
    for (int i = (size / 2); i >= 0; i--)
    {
        heapify(arr, i, size);
    }
    // heap sort array
    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        size--;
        heapify(arr, 0, size);
    }
}

int main()
{
    std::vector<int> testArray = {121, 432, 564, 23, 1, 45, 788};

    // bubbleSort(testArray);
    // selectionSort(testArray);
    // insertionSort(testArray);

    // mergeSort(testArray);
    // quickSort(testArray);
    // countingSort(testArray);
    // radixSort(testArray);
    // heapSort(testArray);

    printArr(testArray);
}
