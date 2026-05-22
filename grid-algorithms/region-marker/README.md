

# Region Marker

## Overview

This project is a C program that reads a map from a text file, finds all closed background regions, and marks each region with a different integer value.

The map is represented as a matrix containing only two characters:

- `*` represents a fence or wall
- `.` represents background area

The program uses a recursive flood-fill approach to explore connected background cells. Only vertical and horizontal moves are considered, so diagonal cells are not treated as connected.

## Source of the Exercise

The programming exercise is based on the **Map Regions** problem from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and file format are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

The input file stores a map whose size is unknown, but limited to 20 rows and 20 columns. The map contains only `*` and `.` characters.

The program must:

1. Read the input map from a file
2. Find each connected background region
3. Mark each region with a different integer value
4. Save the marked map to an output file

Input and output file names are passed as command-line arguments.

## Input Format

The input file contains the map directly, without dimensions.

Example `input.txt`:

```text
***************
*...*.........*
*...*........**
*...*.......*.*
*...*...****..*
*....*.*......*
*.....*.......*
*.....*.......*
*.....*****...*
*....*.....*..*
*****.......*.*
*............**
*.............*
***************
```

## Output Format

The output file contains the same map, but every `.` region is replaced with a region number.

Example `expected-output.txt`:

```text
***************
*111*222222222*
*111*22222222**
*111*2222222*3*
*111*222****33*
*1111*2*333333*
*11111*3333333*
*11111*3333333*
*11111*****333*
*1111*44444*33*
*****4444444*3*
*444444444444**
*4444444444444*
***************
```

In this example, the program finds 4 connected regions.

## How the Program Works

The program first reads the map into a fixed-size 2D array. Each `*` is stored as a wall, and each `.` is stored as an unvisited background cell.

Then it scans the matrix from top to bottom and left to right. When it finds an unvisited background cell, it starts a recursive flood-fill from that position and marks all connected cells with the same region ID.

The flood-fill explores four directions only:

- up
- down
- left
- right

After all cells have been processed, the marked map is written to the output file.

## Concepts Practiced

- Recursion
- Flood-fill algorithm
- Matrix/grid traversal
- File input and output
- Boundary checking
- Command-line arguments
- Connected components in a grid

## Project Files

```text
region-marker/
├── region_marker.c
├── input.txt
├── expected-output.txt
└── README.md
```

## How to Compile

```bash
gcc region_marker.c -o region_marker
```

## How to Run

```bash
./region_marker input.txt output.txt
```

After running the program, it generates:

```text
output.txt
```

The generated output can be compared with:

```text
expected-output.txt
```

## Example Output Message

```text
Original map:
...

Marked regions:
...

Done. Marked map saved to 'output.txt'.
```