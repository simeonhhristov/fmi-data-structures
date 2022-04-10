#include "../helper_functions.cpp"

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


int main()
{
    std::vector<int> testArray = {1, 4, 2, 3, 1, 8, 5};

    insertionSort(testArray);

    printArr(testArray);
}