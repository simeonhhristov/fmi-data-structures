# Counting Sort

## Complexity

- Time complexity - `O(n + k)`
- Space Complexity - `O(n + k)`
- Stability - `Yes`

## Idea Behind The Algorithm 

1. **Find out the maximum element (let it be** `max`**) from the given array.**

    
![Image1.](https://cdn.programiz.com/cdn/farfuture/_iojSNQFxCvNdbdPPmMVCJZxGFTS0TOZRIt1E4Wte0Y/mtime:1582112622/sites/tutorial2program/files/Counting-sort-0_0.png)

2. **Initialize an array of length `max + 1` with all elements 0. This array is used for storing the count of the elements in the array.**

![Image2.](https://cdn.programiz.com/cdn/farfuture/bRDNfPQG8lie6m7EFXVqPj8w6RzkRhM34XNaAoG2dCs/mtime:1582112622/sites/tutorial2program/files/Counting-sort-1.png)

3. **Store the count of each element at their respective index in `count` array**

For example: if the count of element 3 is 2 then, 2 is stored in the 3rd position of `count` array. If element "5" is not present in the array, then 0 is stored in 5th position. 

![Image3.](https://cdn.programiz.com/cdn/farfuture/CIyC1Lkj5JFln_hjy8U1acmUZ4JST__v4bQBvPcnOkk/mtime:1582112622/sites/tutorial2program/files/Counting-sort-2.png)

4. **Store cumulative sum of the elements of the count array. It helps in placing the elements into the correct index of the sorted array. **

![Image4.](https://cdn.programiz.com/cdn/farfuture/6A5S6vY-KsapHcyBjGgLNrp-58NRdyGDeVXspSzUbwM/mtime:1582112622/sites/tutorial2program/files/Counting-sort-3.png)

5. **Find the index of each element of the original array in the count array. This gives the cumulative count. Place the element at the index calculated as shown in figure below.**

![Image5.](https://cdn.programiz.com/cdn/farfuture/tcfjQdeYwL_jETOCPZxNjIXbysRrb7MaG6PwO2MzHnM/mtime:1582112622/sites/tutorial2program/files/Counting-sort-4_1.png)

6. **After placing each element at its correct position, decrease its count by one.**

## Counting Sort Applications

Counting sort is used when:

- There are smaller integers with multiple counts.
- Linear complexity is the need.

## Note
Counting sort doesn't work for arrays with negative integers. One approach to making it work with negatives is to keep them in a separate array and make them positive, use counting sort on them and reverse them, then add them back to the original array.