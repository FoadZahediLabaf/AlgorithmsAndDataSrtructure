

# Magic Square Solver

## Overview

This project is a C program that finds one normal magic square of size `n x n` using recursive backtracking.

A normal magic square is a square matrix filled with the distinct integers from `1` to `n²`, where every row, every column, and both main diagonals have the same sum. This sum is called the magic constant or magic sum.

The program receives the size of the square from the command line and prints one valid magic square if a solution is found.

## Source of the Exercise

The programming exercise is based on the **Magic Square** problem from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and mathematical definition are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

Given a positive integer `n`, the program tries to generate a normal magic square of size `n x n`.

The square must contain all numbers from:

```text
1 to n²
```

Each number must appear exactly once.

Every row, column, and diagonal must have the same sum.

The magic constant is calculated as:

```text
n * (n² + 1) / 2
```

For example, for `n = 3`, the magic constant is:

```text
3 * (9 + 1) / 2 = 15
```

A possible 3x3 magic square is:

```text
  2   7   6
  9   5   1
  4   3   8
```

## Program Behavior

The program takes the square size as a command-line argument.

Example:

```bash
./magic_square 3
```

Special cases:

- `n = 1` has a valid magic square: `1`
- `n = 2` has no normal magic square
- larger sizes may take much longer because the program uses recursive backtracking

The program currently accepts sizes from `1` to `10`, but backtracking becomes very slow for larger values of `n`.

## How the Program Works

The program creates an empty `n x n` matrix and tries to fill it position by position.

It uses the numbers from `1` to `n²`, making sure that each number is used only once.

At each recursive step, the program:

1. places an unused number in the current cell
2. checks whether the current partial square is still promising
3. continues recursively if the partial square is valid
4. backtracks if the current choice cannot lead to a solution

The pruning function checks row sums, column sums, and diagonal sums while the square is being filled. This helps reject invalid partial solutions earlier.

When all cells are filled, the program verifies that the final matrix is a valid magic square.

## Concepts Practiced

- Recursion
- Backtracking
- Matrix handling
- Dynamic memory allocation
- Arrays
- Search-space pruning
- Command-line arguments
- Input validation
- Memory cleanup with `free`

## Project Files

```text
magic-square/
├── magic_square.c
└── README.md
```

## How to Compile

```bash
gcc magic_square.c -o magic_square
```

## How to Run

Run for a 3x3 magic square:

```bash
./magic_square 3
```

Example output:

```text
Magic square of size 3 found.
Magic constant: 15

  2   7   6
  9   5   1
  4   3   8
```

Run for size 2:

```bash
./magic_square 2
```

Expected output:

```text
No normal 2x2 magic square exists.
```

If the size is missing:

```bash
./magic_square
```

The program prints:

```text
Usage: ./magic_square <size>
Example: ./magic_square 3
```

## Notes

This implementation is designed as a recursive backtracking exercise. It is clear and educational, but it is not optimized for generating large magic squares.

For practical use, specialized construction methods are faster for many magic-square sizes. This project intentionally focuses on recursion and backtracking.