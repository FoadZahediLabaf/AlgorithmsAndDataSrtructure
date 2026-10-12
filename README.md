# Algorithms and Data Structures in C

A collection of 13 standalone C programs covering algorithms, data structures, recursive problem solving, and file-based data processing.

The projects explore pointers, dynamic memory allocation, linked structures, trees, sorting, backtracking, and structured input/output through executable examples.

## Overview

Each project focuses on a specific problem and includes its own source code and documentation.

The collection ranges from classic algorithms, such as merge sort and binary search trees, to applications involving student records, library borrowing data, and grid exploration.

Programs are organized by topic and can be compiled independently.

## Projects

### Recursion and Backtracking

| Project | Description |
|---|---|
| [Maze Solver](recursion-and-backtracking/maze-solver) | Finds an escape path, counts possible escape paths, and identifies the shortest one using recursive backtracking. |
| [Knight's Tour](recursion-and-backtracking/knight-tour) | Searches for a tour on an 8×8 chessboard using backtracking and Warnsdorff's heuristic. |
| [Magic Square](recursion-and-backtracking/magic-square) | Searches for a normal magic square whose rows, columns, and main diagonals have the same sum. |
| [Prefix Expression Evaluator](recursion-and-backtracking/polish-expression) | Recursively evaluates arithmetic expressions written in prefix Polish notation. |

### Sorting

| Project | Description |
|---|---|
| [Merge Sort](sorting/merge-sort) | Sorts command-line integers in ascending or descending order using divide and conquer. |
| [Linked List Sort](sorting/linked-list-sort) | Loads student records and writes them ordered by surname or grade. |

### Trees

| Project | Description |
|---|---|
| [Binary Search Tree](trees/binary-search-tree) | Provides interactive insertion, search, deletion, traversal, and tree summaries. |
| [Binary Tree Traversal](trees/binary-tree-traversal) | Builds a binary tree interactively and reports traversals, node count, and height. |

### Linked Lists

| Project | Description |
|---|---|
| [Overlapping Linked Lists](linked-lists/overlapping-linked-lists) | Connects the same student records through two linked orders: one by name and another by exam mark. |

### Grid Algorithms

| Project | Description |
|---|---|
| [Region Marker](grid-algorithms/region-marker) | Uses recursive flood fill to identify and label enclosed background regions in a grid, considering horizontal and vertical connections. |

### Strings and Files

| Project | Description |
|---|---|
| [Acronym Generator](strings-and-files/acronym-generator) | Generates character combinations from input words while alternating letters and digits. |

### Records Processing

| Project | Description |
|---|---|
| [Library Borrowing Records](records-processing/library-borrowing-records) | Processes user, catalogue, and borrowing files to generate summaries by user and by book. |
| [Blood Donation Records](records-processing/blood-donation-records) | Combines donor and donation records to calculate donation counts and total donated volume. |

## Concepts Covered

- Recursive decomposition and backtracking.
- Divide-and-conquer sorting.
- Binary trees and binary search trees.
- Linked lists and multiple links within shared records.
- Grid traversal and flood fill.
- Expression parsing.
- Structs, pointers, and dynamic memory.
- String handling and command-line arguments.
- Text-file parsing and report generation.

## Repository Structure

```text
AlgorithmsAndDataSrtructure/
├── recursion-and-backtracking/
│   ├── maze-solver/
│   ├── knight-tour/
│   ├── magic-square/
│   └── polish-expression/
├── sorting/
│   ├── merge-sort/
│   └── linked-list-sort/
├── trees/
│   ├── binary-search-tree/
│   └── binary-tree-traversal/
├── linked-lists/
│   └── overlapping-linked-lists/
├── grid-algorithms/
│   └── region-marker/
├── strings-and-files/
│   └── acronym-generator/
├── records-processing/
│   ├── library-borrowing-records/
│   └── blood-donation-records/
├── README.md
└── LICENSE
```

## Getting Started

### Requirements

- A C compiler, such as GCC or Clang.
- A terminal.

Each program is compiled separately from its project directory.

### Clone the Repository

```bash
git clone https://github.com/FoadZahediLabaf/AlgorithmsAndDataSrtructure.git
cd AlgorithmsAndDataSrtructure
```

### Example: Merge Sort

```bash
cd sorting/merge-sort

gcc -std=c11 -Wall -Wextra merge_sort.c -o merge_sort.out

./merge_sort.out -a 9 3 7 1 0 4
./merge_sort.out -d 9 3 7 1 0 4
```

The `-a` option selects ascending order, while `-d` selects descending order.

### Example: Prefix Expression Evaluation

From the repository root:

```bash
cd recursion-and-backtracking/polish-expression

gcc -std=c11 -Wall -Wextra polish_expression.c -o polish_expression.out

./polish_expression.out "* + 5 6 7"
```

The expression corresponds to `(5 + 6) × 7`.

Pass the complete expression as a quoted command-line argument.

### Example: Maze Solver

From the repository root:

```bash
cd recursion-and-backtracking/maze-solver

gcc -std=c11 -Wall -Wextra maze_solver.c -o maze_solver.out

./maze_solver.out input.txt
```

The program reads the supplied maze and prints its path analysis.

## Input and Output

Programs use different interaction styles:

- **Command-line arguments:** merge sort, magic square, and prefix expressions.
- **Interactive commands or prompts:** linked-list programs and tree programs.
- **Input files:** maze solving, region marking, acronym generation, and records processing.

Run file-based examples from their project directories so that relative input paths resolve correctly.

Several folders include sample inputs and expected-output files. Their local README documents the file format, commands, and output behavior.

Compiled executables ending in `.out` are excluded by the repository's `.gitignore`.

## Project Documentation

Each project has a dedicated README describing:

- The problem being solved.
- The algorithm or data structure used.
- Input formats and supported commands.
- Compilation and execution.
- Example behavior and relevant assumptions.

The programs are educational implementations. Backtracking problems can become expensive as the search space grows, and individual exercises have their own input constraints.

## Exercise Sources

Some projects are based on exercises from:

**Advanced Programming and Problem-Solving Strategies in C — Part II:
Algorithms and Data Structures, Second Edition.**

The corresponding project README identifies the exercise source and explains the relationship between the original problem and this implementation.

## Author

**Foad Zahedi Labaf**

## License and Copyright

© 2026 Foad Zahedi Labaf.

Licensed under the [MIT License](LICENSE).

Third-party materials remain subject to their original licenses and terms.
