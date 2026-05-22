# Merge Sort

## Overview

This project is a C implementation of the merge sort algorithm.

Merge sort is a divide-and-conquer sorting algorithm. It splits an array into smaller parts, sorts those parts recursively, and then merges them back together in sorted order.

This version supports both sorting directions:

- ascending order with `-a`
- descending order with `-d`

The numbers to sort are passed directly through the command line.

## Problem Description

The program receives a sorting mode and a list of integers from the terminal.

The first argument must be one of these options:

```text
-a  ascending order
-d  descending order
```

All following arguments must be valid integers.

If the sorting mode is missing, invalid, or no integers are provided, the program prints a usage message.

## How the Algorithm Works

Merge sort follows three main steps:

1. Divide the array into two halves
2. Recursively sort each half
3. Merge the two sorted halves into one sorted array

The recursion stops when a subarray has one element, because a single element is already sorted.

During the merge step, the comparison changes depending on the selected mode:

- in ascending mode, the smaller value is placed first
- in descending mode, the larger value is placed first

## Examples

### Ascending order

Command:

```bash
./merge_sort -a 1 5 3 8 6 8 5 8 5 6 12 0
```

Output:

```text
Original array:
1 5 3 8 6 8 5 8 5 6 12 0
Sorted array (ascending):
0 1 3 5 5 5 6 6 8 8 8 12
```

### Descending order

Command:

```bash
./merge_sort -d 1 5 3 8 6 8 5 8 5 6 12 0
```

Output:

```text
Original array:
1 5 3 8 6 8 5 8 5 6 12 0
Sorted array (descending):
12 8 8 8 6 6 5 5 5 3 1 0
```

## Concepts Practiced

- Divide and conquer
- Recursion
- Sorting algorithms
- Dynamic memory allocation
- Arrays
- Command-line arguments
- Input validation
- Ascending and descending sorting
- Memory cleanup

## Project Files

```text
merge-sort/
├── merge_sort.c
└── README.md
```

## How to Compile

```bash
gcc merge_sort.c -o merge_sort
```

## How to Run

Run in ascending order:

```bash
./merge_sort -a 9 3 7 1 0 4
```

Expected output:

```text
Original array:
9 3 7 1 0 4
Sorted array (ascending):
0 1 3 4 7 9
```

Run in descending order:

```bash
./merge_sort -d 9 3 7 1 0 4
```

Expected output:

```text
Original array:
9 3 7 1 0 4
Sorted array (descending):
9 7 4 3 1 0
```

Run with missing arguments:

```bash
./merge_sort
```

Expected usage message:

```text
Usage: ./merge_sort <-a|-d> <integer1> <integer2> ...
  -a  Sort in ascending order
  -d  Sort in descending order
Example ascending:  ./merge_sort -a 9 3 7 1 0 4
Example descending: ./merge_sort -d 9 3 7 1 0 4
```

## Notes

The implementation uses one temporary array during the merge phase. This avoids repeatedly allocating memory inside each recursive call and keeps the sorting process cleaner.