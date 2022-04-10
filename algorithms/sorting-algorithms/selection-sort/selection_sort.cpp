#include "../helper_functions.cpp"

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


int main()
{
    std::vector<int> testArray = {155, 334, 856, 65, 111, 677, 545};

    selectionSort(testArray);

    printArr(testArray);
}