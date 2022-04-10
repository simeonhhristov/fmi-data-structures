# Bubble Sort

## Complexity

- Time complexity - `O(n^2)`
- Space Complexity - `O(1)`
- Stability - `Yes`

## Idea Behind The Algorithm 
### Suppose we are trying to sort the elements in ascending order.

1. **First Iteration (Compare and Swap)**

    Starting from the first index, compare the first and the second elements.
    If the first element is greater than the second element, they are swapped.
    Now, compare the second and the third elements. Swap them if they are not in order.
    The above process goes on until the last element. 
    
![Image1.](https://cdn.programiz.com/cdn/farfuture/kn1zM7ZGIj60jcTe3mv8gAtbrvFHqxgqfQ7F9MdjPuA/mtime:1582112622/sites/tutorial2program/files/Bubble-sort-0.png)

2. **Remaining Iteration**

The same process goes on for the remaining iterations.

After each iteration, the largest element among the unsorted elements is placed at the end.

![Image2.](https://cdn.programiz.com/cdn/farfuture/LzbPYkOXS-DjqwLqtIrixMZCD1XLdU-JWWedrL1YIpw/mtime:1582112622/sites/tutorial2program/files/Bubble-sort-1.png)

In each iteration, the comparison takes place up to the last unsorted element. The array is sorted when all the unsorted elements are placed at their correct positions.



## Bubble Sort Applications

Bubble sort is used if:
- complexity does not matter
- short and simple code is preferred