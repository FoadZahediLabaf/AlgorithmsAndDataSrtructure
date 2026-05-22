# C-algorithms-and-data-structures
# C Algorithms and Data Structures

This repository contains a collection of C programming projects focused on algorithms, data structures, recursion, file processing, and problem solving.

The projects were developed as academic and personal programming exercises to practice writing clean, structured, and understandable C code. Each project focuses on a specific topic such as backtracking, sorting, binary trees, linked lists, grid algorithms, string processing, or records management.

## Repository Goals

The main goals of this repository are to:

- practice core programming concepts in C
- improve problem-solving skills through algorithmic exercises
- work with dynamic memory allocation and pointers
- organize C projects in a clean and readable structure
- document each project with clear explanations, input/output formats, and compile/run instructions

## Topics Covered

- Recursion and backtracking
- Sorting algorithms
- Binary trees and binary search trees
- Linked lists
- Grid-based algorithms
- String and file processing
- Records processing with structs
- Dynamic memory allocation
- File input/output in C

## Repository Structure

```text
C-algorithms-and-data-structures/
├── README.md
├── recursion-and-backtracking/
│   ├── maze-solver/
│   ├── knight-tour/
│   ├── magic-square/
│   └── polish-expression/
│
├── sorting/
│   ├── merge-sort/
│   └── linked-list-sort/
│
├── trees/
│   ├── binary-search-tree/
│   └── binary-tree-traversal/
│
├── linked-lists/
│   └── overlapping-linked-lists/
│
├── grid-algorithms/
│   └── region-marker/
│
├── strings-and-files/
│   └── acronym-generator/
│
└── records-processing/
    ├── library-borrowing-records/
    └── blood-donation-records/
```

## Projects

### Recursion and Backtracking

| Project | Description | Main Concepts |
|---|---|---|
| Maze Solver | Solves a maze using recursive backtracking and finds one path, all paths, and the shortest path. | Recursion, backtracking, dynamic memory, file input |
| Knight Tour | Solves the Knight's Tour problem on a chessboard using recursive backtracking. | Backtracking, recursion, board traversal |
| Magic Square | Generates or searches for magic squares. | Recursion, backtracking, matrix handling |
| Polish Expression | Evaluates or processes expressions written in Polish notation. | Recursion, expression parsing |

### Sorting

| Project | Description | Main Concepts |
|---|---|---|
| Merge Sort | Implements merge sort for integer arrays. | Divide and conquer, recursion, sorting |
| Linked List Sort | Sorts data stored in a linked list. | Linked lists, sorting, pointers |

### Trees

| Project | Description | Main Concepts |
|---|---|---|
| Binary Search Tree | Implements insertion, search, deletion, and traversal operations for a BST. | Trees, recursion, dynamic memory |
| Binary Tree Traversal | Builds a binary tree from input and prints preorder, inorder, and postorder traversals. | Trees, traversal, recursion |

### Linked Lists

| Project | Description | Main Concepts |
|---|---|---|
| Overlapping Linked Lists | Works with linked lists and detects or handles overlapping nodes/lists. | Linked lists, pointers, memory management |

### Grid Algorithms

| Project | Description | Main Concepts |
|---|---|---|
| Region Marker | Labels connected regions in a grid using flood fill. | Recursion, flood fill, matrices |

### Strings and Files

| Project | Description | Main Concepts |
|---|---|---|
| Acronym Generator | Generates acronyms from words by selecting characters according to a rule. | Strings, recursion, file I/O |

### Records Processing

| Project | Description | Main Concepts |
|---|---|---|
| Library Borrowing Records | Processes users, catalogue, and borrowing files to generate user/book borrowing summaries. | Structs, file I/O, dynamic memory |
| Blood Donation Records | Processes donor and donation records to calculate donation counts and total donated blood. | Structs, file I/O, arrays, strings |

## How to Compile Projects

Most projects can be compiled using `gcc` from inside their project folder.

Example:

```bash
gcc project_file.c -o project_name
```

Then run:

```bash
./project_name
```

Some projects require input files. In those cases, check the project-specific `README.md` inside the folder.

Example:

```bash
./library_borrowing_records users.txt catalogue.txt borrows.txt
```

## Documentation

Each larger project contains its own `README.md` explaining:

- what the program does
- the input format
- the output format
- how the program works
- how to compile and run it
- the main C concepts practiced

## Notes

Some exercises are based on academic programming problems or textbook-style exercises. When a project is based on a specific exercise source, the project README gives credit for the exercise idea and file format. The implementations and organization in this repository were written independently.

Generated executable files and temporary build outputs are not included in the repository.

## Author

**Foad Zahedi Labaf**

Computer Engineering graduate and Master's student in Computer Science and Engineering at Politecnico di Milano.

## License

This repository is licensed under the MIT License.