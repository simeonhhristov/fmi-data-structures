#include "../helper_functions.cpp"

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

int main()
{
    std::vector<int> testArray = {1, 4, 2, 3, 1, 8, 5};

    countingSort(testArray);

    printArr(testArray);
}