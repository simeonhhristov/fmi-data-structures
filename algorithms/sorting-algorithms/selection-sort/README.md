# Selection Sort

## Complexity

- Time complexity - `O(n^2)`
- Space Complexity - `O(1)`
- Stability - `No`

## Idea Behind The Algorithm 

1. **Set the first element as** `minimum`.

![Image1.](https://cdn.programiz.com/cdn/farfuture/w1ZKsO2Obaw1WV03_lamX22SVyapwhbiKoLkT5Raiiw/mtime:1582112622/sites/tutorial2program/files/Selection-sort-0-initial-array.png)

2. **Compare** `minimum` **with the second element. If the second element is smaller than** `minimum`**, assign the second element as** `minimum`.

![Image2.](https://cdn.programiz.com/cdn/farfuture/9jjqXX0fGtJE2ul2Mga20fvf_GkNlFAFsDMwrrwFzbQ/mtime:1582112622/sites/tutorial2program/files/Selection-sort-0-comparision.png)

3. **After each iteration,** `minimum` **is placed in the front of the unsorted list.**

![Image3.](https://cdn.programiz.com/cdn/farfuture/6o-qergdHNq6D7eBxBi87yIuCLc7MJy2BHR4QHeNxxQ/mtime:1582112622/sites/tutorial2program/files/Selection-sort-0-swapping.png)

4. **For each iteration, indexing starts from the first unsorted element. Step 1 to 3 are repeated until all the elements are placed at their correct positions.**

## Selection Sort Applications
Selection sort is used when

- A small list is to be sorted
- Cost of swapping does not matter
- Checking of all the elements is compulsory
- Cost of writing to a memory matters like in flash memory (number of writes/swaps is `O(n)` as compared to `O(n^2)` of bubble sort)
