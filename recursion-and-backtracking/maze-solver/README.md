

# Maze Solver

## Overview

This project is a C program that solves a maze using recursive backtracking.

The maze is read from a text file. The program prints:

- one possible escape path
- the number of all escape paths
- the shortest escape path

The solution paths are printed directly in the terminal.

## Source of the Exercise

The programming exercise is based on the **Maze** problem from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and file format are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

The input file contains a labyrinth represented as a matrix.

The first line contains the number of rows and columns:

```text
rows columns
```

The following lines contain the maze itself.

Maze symbols:

```text
@  starting position
#  exit point
*  wall
   empty corridor
```

The program assumes that the maze contains exactly one starting position.

## Input Format

Example `input.txt`:

```text
12 10
**********
*        *
*   **@* *
* * ** * *
* ****** *
*   **   *
* *    ***
* ** * ***
* *  * * *
* * ** * *
*   **   *
******#***
```

## Output

The program prints:

1. the original maze
2. one possible escape path
3. the number of all escape paths
4. the shortest escape path

Cells that belong to a path are marked with:

```text
$
```

The starting position remains:

```text
@
```

The exit remains:

```text
#
```

Example terminal output structure:

```text
Original maze:
...

One path:
...

Number of paths found: 9

Shortest path (15 steps):
...

Done. Maze processing completed.
```

## How the Program Works

The program uses recursive backtracking.

For each position, it checks whether the current cell is inside the maze and whether it is walkable. A cell is walkable if it is an empty corridor, the starting position, or the exit.

The recursive search tries four possible moves:

- up
- right
- left
- down

For one escape path, the program stops when it reaches the first valid exit path.

For all escape paths, the program explores every possible valid route from the start to the exit and counts them.

For the shortest escape path, the program keeps track of the best path found so far and updates it whenever a shorter path is found.

## Concepts Practiced

- Recursion
- Backtracking
- Maze traversal
- Matrix handling
- Dynamic memory allocation
- File input
- Path counting
- Shortest path search
- Memory cleanup

## Project Files

```text
maze-solver/
├── maze_solver.c
├── input.txt
└── README.md
```

## How to Compile

```bash
gcc maze_solver.c -o maze_solver
```

## How to Run

```bash
./maze_solver input.txt
```

## Notes

The input file must preserve spaces inside the maze because spaces represent open corridors. Avoid replacing spaces with tabs or dots.