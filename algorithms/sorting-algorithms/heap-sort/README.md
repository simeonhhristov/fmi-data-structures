# Heap Sort

## Complexity

- Time complexity - `O(n*log n)`
- Space Complexity - `O(1)`
- Stability - `No`

## Idea Behind The Algorithm 

Visit the link below to see a full explanation about heap sort:
- https://www.programiz.com/dsa/heap-sort

## Heap Sort Applications



Systems concerned with security and embedded systems such as Linux Kernel use Heap Sort because of the `O(n log n)` upper bound on Heapsort's running time and constant `O(1)` upper bound on its auxiliary storage. </br>

Although Heap Sort has `O(n log n)` time complexity even for the worst case, it doesn't have more applications ( compared to other sorting algorithms like Quick Sort, Merge Sort ). However, its underlying data structure, heap, can be efficiently used if we want to extract the smallest (or largest) from the list of items without the overhead of keeping the remaining items in the sorted order. For e.g Priority Queues.
