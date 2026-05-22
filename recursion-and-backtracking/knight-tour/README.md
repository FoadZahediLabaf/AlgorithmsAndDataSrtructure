# Knight's Tour

## Overview

This project is a C program that solves the Knight's Tour problem on an 8x8 chessboard.

The Knight's Tour is a classic backtracking problem where a knight must visit every square of the chessboard exactly once. The program asks the user for a starting position, then tries to find a valid tour from that position.

To make the search faster, the program uses **Warnsdorff's heuristic**. This heuristic chooses the next move with the fewest possible onward moves, which greatly reduces unnecessary backtracking.

## Problem Description

The program receives the starting position of the knight from the user.

The position is entered as:

```text
row column
```

Both values must be between `0` and `7`.

Example:

```text
6 7
```

The program then searches for a valid knight's tour and prints the board with the move number written in each cell.

## Knight Movement

A knight moves in an L-shape:

- two squares vertically and one square horizontally
- or two squares horizontally and one square vertically

From each position, there are at most 8 possible knight moves.

## Tour Type

The program reports whether the found tour is:

- **open tour**: the final square does not connect back to the starting square
- **closed tour**: the final square can jump back to the starting square with one knight move

The program finds one valid tour and then checks whether that tour is open or closed.

## How the Program Works

The board is represented as an 8x8 matrix of integers.

At the beginning, all cells are initialized to `0`, meaning they have not been visited yet. The starting cell is marked as move `1`.

The recursive solver then tries to visit all remaining cells. At each step, it:

1. collects all valid knight moves from the current position
2. counts how many onward moves each option has
3. sorts the move options using Warnsdorff's heuristic
4. recursively tries the best move first
5. backtracks if a move does not lead to a complete tour

When all 64 cells have been visited, the program prints the completed tour.

## Example

Input:

```text
Enter the knight's starting position (row column, 0-7): 6 7
```

Example output:

```text
Knight's tour found.
Tour type: open tour

 64  13  30  33  44  15  28  19
 31  34  63  14  29  18  41  16
 12  61  32  45  58  43  20  27
 35  50  59  62  25  40  17  42
 60  11  54  39  46  57  26  21
 49  36  51  56  53  24   3   6
 10  55  38  47   8   5  22   1
 37  48   9  52  23   2   7   4

Done. Knight's tour processing completed.
```

The number `1` shows the starting square. The number `64` shows the final square.

## Concepts Practiced

- Recursion
- Backtracking
- Warnsdorff's heuristic
- Chessboard traversal
- Matrix handling
- Move validation
- Sorting candidate moves
- Open and closed tour checking

## Project Files

```text
knight-tour/
├── knight_tour.c
└── README.md
```

## How to Compile

```bash
gcc knight_tour.c -o knight_tour
```

## How to Run

```bash
./knight_tour
```

Then enter a starting position:

```text
6 7
```

## Notes

The program uses zero-based indexing for board positions.

Valid rows and columns are:

```text
0 1 2 3 4 5 6 7
```


