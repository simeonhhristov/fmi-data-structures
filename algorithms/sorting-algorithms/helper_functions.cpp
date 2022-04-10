#include <iostream>
#include <vector>

// print array
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

