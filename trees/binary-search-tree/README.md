

# Binary Search Tree

## Overview

This project is a C implementation of a Binary Search Tree (BST).

A Binary Search Tree is a tree-based data structure where each node stores one key. For every node:

- keys smaller than the node key are stored in the left subtree
- keys greater than the node key are stored in the right subtree

This property makes searching, insertion, deletion, and ordered traversal efficient when the tree is reasonably balanced.


## Problem Description

The program provides an interactive menu for working with a Binary Search Tree.

The user can:

- insert one or more integer keys
- search for a key
- delete a key
- print the tree using preorder traversal
- print the tree using inorder traversal
- print the tree using postorder traversal
- print a summary of the tree
- exit the program and free the allocated memory

Duplicate keys are ignored, because this implementation stores each key only once.

## Binary Search Tree Operations

### Insert

A new key is inserted according to the BST rule:

- if the key is smaller than the current node, move left
- if the key is greater than the current node, move right
- if the key already exists, ignore it

### Search

The search operation compares the target key with the current node. Depending on the comparison, it recursively continues in the left or right subtree.

### Delete

The delete operation handles three cases:

1. the node has no children
2. the node has one child
3. the node has two children

When deleting a node with two children, the program replaces the node key with the minimum key from the right subtree.

### Traversals

The program supports three recursive tree traversals:

- preorder: root, left, right
- inorder: left, root, right
- postorder: left, right, root

For a Binary Search Tree, inorder traversal prints the keys in sorted ascending order.

## Example Usage

After running the program, the menu is shown:

```text
Binary Search Tree Menu
1. Insert one or more keys
2. Search key
3. Delete key
4. Print preorder traversal
5. Print inorder traversal
6. Print postorder traversal
7. Print tree summary
0. Exit
Choice:
```

Example input sequence:

```text
1
50 30 70 20 40 60 80
5
7
2
40
3
30
5
0
```

Example output highlights:

```text
Inorder traversal: 20 30 40 50 60 70 80

Number of nodes: 7
Tree height: 2
Minimum key: 20
Maximum key: 80

Key found.

Deleted successfully.

Inorder traversal: 20 40 50 60 70 80

Done. Tree memory released successfully.
```

## Concepts Practiced

- Binary Search Tree operations
- Recursion
- Dynamic memory allocation
- Pointers
- Structs
- Tree traversal
- Searching
- Deletion in a tree
- Input parsing
- Memory cleanup with `free`

## Project Files

```text
binary-search-tree/
├── binary_search_tree.c
└── README.md
```

## How to Compile

```bash
gcc binary_search_tree.c -o binary_search_tree
```

## How to Run

```bash
./binary_search_tree
```

## Notes

This project is a Binary Search Tree implementation, not a simple binary search over a sorted array. Unlike array-based binary search, the data structure grows dynamically as keys are inserted.

The program uses recursion for insertion, search, deletion, traversals, counting nodes, calculating height, and freeing memory.