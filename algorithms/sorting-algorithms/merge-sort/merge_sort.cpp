#include "../helper_functions.cpp"
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


int main()
{
    std::vector<int> testArray = {1, 4, 2, 3, 1, 8, 5};

    mergeSort(testArray);

    printArr(testArray);
}