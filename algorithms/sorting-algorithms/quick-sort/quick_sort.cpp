#include "../helper_functions.cpp"

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


int main()
{
    std::vector<int> testArray = {1, 4, 2, 3, 1, 8, 5};

    quickSort(testArray, 0, testArray.size() - 1);

    printArr(testArray);
}