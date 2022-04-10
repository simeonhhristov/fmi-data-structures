#include "../helper_functions.cpp"

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

int main()
{
    std::vector<int> testArray = {155, 334, 856, 65, 111, 677, 545};

    radixSort(testArray);

    printArr(testArray);
}