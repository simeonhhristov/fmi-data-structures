# Merge Sort

## Complexity

- Time complexity - `O(n*log n)`
- Space Complexity - `O(n)`
- Stability - `Yes`
## Idea Behind The Algorithm 

![Image1.](https://cdn.programiz.com/cdn/farfuture/PRTu8e23Uz212XPrrzN_uqXkVZVY_E0Ta8GZp61-zvw/mtime:1586425911/sites/tutorial2program/files/merge-sort-example_0.png)

1. **Create copies of the subarrays** `L ← A[p..q]` **and** `M ← A[q+1..r]`**.**<br> 
2. **Create three pointers** `i`, `j` **and** `k`**.**
  - `i` **maintains current index of** `L` **, starting at 1**
  - `j` **maintains current index of** `M` **, starting at 1**
  - `k` **maintains the current index of** `A[p..q]` **, starting at** `p`**.**
  
3. **Until we reach the end of either** `L` **or** `M`**, pick the larger among the elements from** `L` **and** `M` **and place them in the correct position at** `A[p..q]`**.**
4. **When we run out of elements in either** `L` **or** `M`**, pick up the remaining elements and put in** `A[p..q]`**.**

## Merge Sort Applications
- Inversion count problem
- External sorting
- Ecommerce applications





