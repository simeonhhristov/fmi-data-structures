# Radix Sort

## Complexity

- Time complexity - `O(n + k)`
- Space Complexity - `O(d*(n + b))`
- Stability - `Yes`
-`b` is the counting base .
-`d` is the number of digits in the largest element.



## Idea Behind The Algorithm 

Radix sort is a sorting algorithm that sorts the elements by first grouping the individual digits of the same **place value**. Then, sort the elements according to their increasing/decreasing order.

Since radix sort is a non-comparative algorithm, it has advantages over comparative sorting algorithms.
For the radix sort that uses **counting sort** as an intermediate stable sort, the time complexity is `O(d(n+k))`.

Detailed information about the algorithm:</br>
https://www.programiz.com/dsa/radix-sort


## Radix Sort Applications
Radix sort is implemented in

- DC3 algorithm (Kärkkäinen-Sanders-Burkhardt) while making a suffix array.
- Places where there are numbers in large ranges.




