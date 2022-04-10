# Insertion Sort
Best among the slow algorithms.
## Complexity

- Time complexity - `O(n^2)`
- Space Complexity - `O(1)`
- Stability - `Yes`

## Idea Behind The Algorithm 
Suppose we need to sort the following array.

![Image1.](https://cdn.programiz.com/cdn/farfuture/K-kSm72ww4_afH0mQJDuR3Y-fPZYgBYo_Pclx7WlYUo/mtime:1582112622/sites/tutorial2program/files/Frame%204_0.png)

1. **The first element in the array is assumed to be sorted. Take the second element and store it separately in** `key`.

Compare key with the first element. If the first element is greater than key, then key is placed in front of the first element. 


![Image2.](https://cdn.programiz.com/cdn/farfuture/l-X2VCkF2rp4i0X8mZX6BGJL_FQW9EL8PkKhBswQfpc/mtime:1582112622/sites/tutorial2program/files/Insertion-sort-0_1.png)
2. **Now, the first two elements are sorted.**

Take the third element and compare it with the elements on the left of it. Placed it just behind the element smaller than it. If there is no element smaller than it, then place it at the beginning of the array.

![Image3.](https://cdn.programiz.com/cdn/farfuture/MqcrLAaQHEhcuJTmF_m712GG_wMemTY9AID0J9w4T6E/mtime:1582112622/sites/tutorial2program/files/Insertion-sort-1_1.png)

3. **Similarly, place every unsorted element at its correct position.**

![Image4.](https://cdn.programiz.com/cdn/farfuture/hWFdFWWU0lZD2xWGz0CoMDESnjYa9Wg1HwpH99jTTH0/mtime:1582112622/sites/tutorial2program/files/Insertion-sort-2_2.png)


![Image5.](https://cdn.programiz.com/cdn/farfuture/TxAcrgHKfahw_BPEIKwCWB9BY2GNiI91yzWeetMfG9Q/mtime:1582112622/sites/tutorial2program/files/Insertion-sort-3_2.png)


## Insertion Sort Applications
Insertion sort is used when:

- The array is has a small number of elements
- There are only a few elements left to be sorted




