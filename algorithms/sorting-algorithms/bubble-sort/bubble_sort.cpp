#include "../helper_functions.cpp"

// Optimized bubble sort
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

int main()
{
    std::vector<int> testArray = {121, 432, 564, 23, 1, 45, 788};

    bubbleSort(testArray);

    printArr(testArray);
}