

# Binary Tree Traversal

## Overview

This project is a C program that builds a binary tree from user input and prints its main recursive traversals.

The program asks the user to enter the root value, then recursively asks for the left and right child of each node. If a node does not have a child, the user enters `NULL`.

After the tree is built, the program prints:

- preorder traversal
- inorder traversal
- postorder traversal
- number of nodes
- tree height

The program also releases all dynamically allocated memory before exiting.

## Problem Description

The program creates a binary tree interactively.

For each node, the user can enter:

- an integer value, which creates a child node
- `NULL`, which means that child does not exist

This allows the user to build any binary tree shape, not only a Binary Search Tree.

## Binary Tree Traversals

The program supports three common recursive traversals.

### Preorder Traversal

Preorder visits nodes in this order:

```text
root left right
```

### Inorder Traversal

Inorder visits nodes in this order:

```text
left root right
```

### Postorder Traversal

Postorder visits nodes in this order:

```text
left right root
```

## Example Usage

Example input sequence:

```text
Enter root value: 50
Enter left child of 50, or NULL: 30
Enter left child of 30, or NULL: 20
Enter left child of 20, or NULL: NULL
Enter right child of 20, or NULL: NULL
Enter right child of 30, or NULL: 40
Enter left child of 40, or NULL: NULL
Enter right child of 40, or NULL: NULL
Enter right child of 50, or NULL: 70
Enter left child of 70, or NULL: 60
Enter left child of 60, or NULL: NULL
Enter right child of 60, or NULL: NULL
Enter right child of 70, or NULL: 80
Enter left child of 80, or NULL: NULL
Enter right child of 80, or NULL: NULL
```

The tree created from this input is:

```text
        50
       /  \
     30    70
    /  \  /  \
  20   40 60  80
```

Example output:

```text
Preorder traversal: 50 30 20 40 70 60 80
Inorder traversal: 20 30 40 50 60 70 80
Postorder traversal: 20 40 30 60 80 70 50
Number of nodes: 7
Tree height: 2
Done. Tree memory released successfully.
```

## How the Program Works

The program uses recursion to build the tree.

When a node value is entered, the program creates a new node using dynamic memory allocation. Then it asks for the left child and right child of that node.

If the user enters `NULL`, the corresponding child pointer is set to `NULL`.

After the tree is built, recursive functions are used to:

1. print preorder traversal
2. print inorder traversal
3. print postorder traversal
4. count the number of nodes
5. calculate the tree height
6. free all allocated nodes

## Concepts Practiced

- Binary trees
- Recursion
- Tree traversal
- Dynamic memory allocation
- Structs and pointers
- Input validation
- Counting nodes
- Calculating tree height
- Memory cleanup with `free`

## Project Files

```text
binary-tree-traversal/
├── binary_tree_traversal.c
└── README.md
```

## How to Compile

```bash
gcc binary_tree_traversal.c -o binary_tree_traversal
```

## How to Run

```bash
./binary_tree_traversal
```

Then enter integer values or `NULL` when prompted.

## Notes

This is a general binary tree traversal project. It does not enforce the Binary Search Tree ordering rule.

The program uses zero children, one child, or two children depending on the values entered by the user.