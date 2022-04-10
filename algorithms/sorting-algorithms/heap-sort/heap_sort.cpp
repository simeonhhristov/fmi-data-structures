#include "../helper_functions.cpp"


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
    std::vector<int> testArray = {1, 4, 2, 3, 1, 8, 5};

    heapSort(testArray);

    printArr(testArray);
}