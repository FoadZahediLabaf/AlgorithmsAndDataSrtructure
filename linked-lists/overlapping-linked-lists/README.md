

# Overlapping Linked Lists

## Overview

This project is a C program that stores student exam records using two overlapped linked lists.

Each student record contains:

- a last name
- an exam mark

The same student node belongs to two different linked lists at the same time:

- one linked list ordered by student name
- one linked list ordered by exam mark

This allows the program to write the records ordered by name and then ordered by mark, or vice versa, without rebuilding or reordering the data between the two commands.

## Source of the Exercise

The programming exercise is based on the **List Sorting** and **Overlapped Lists** problems from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and file format are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

The input file stores information about students who passed an exam. Each row contains the student's last name and final mark.

The program supports the following commands:

```text
read fileName
writeN fileName
writeM fileName
stop
```

Command meanings:

- `read fileName`: reads student records from a file
- `writeN fileName`: writes the current records ordered by name
- `writeM fileName`: writes the current records ordered by mark
- `stop`: terminates the program

The main point of the overlapped-list version is that `writeN` followed by `writeM`, or `writeM` followed by `writeN`, can be executed without reordering the same data again.

## Input Format

The input file contains one student per line.

Format:

```text
name mark
```

Example `students.txt`:

```text
Rossi 24
Bianchi 28.5
Verdi 19
Neri 30
Gallo 22.5
```

The name is a string of at most 20 characters. The mark is a real value in the range `[0, 30]`.

## Output Format

### Output ordered by name

Command:

```text
writeN students_by_name.txt
```

Example output:

```text
Bianchi 28.50
Gallo 22.50
Neri 30.00
Rossi 24.00
Verdi 19.00
```

### Output ordered by mark

Command:

```text
writeM students_by_mark.txt
```

Example output:

```text
Verdi 19.00
Gallo 22.50
Rossi 24.00
Bianchi 28.50
Neri 30.00
```

## How the Program Works

The program creates one `Student` struct for each valid input record.

Each node contains two next pointers:

- `next_by_name`
- `next_by_mark`

When a student is read, the same node is inserted into both linked lists:

1. the name-ordered list
2. the mark-ordered list

Because both lists share the same nodes, the program can write the data in either order without sorting again.

## Concepts Practiced

- Linked lists
- Overlapped linked structures
- Multiple next pointers in one struct
- Dynamic memory allocation
- File input and output
- String comparison with `strcmp`
- Command-based program execution
- Memory cleanup with `free`

## Project Files

```text
overlapping-linked-lists/
├── overlapping_linked_lists.c
├── students.txt
├── expected_by_name.txt
├── expected_by_mark.txt
└── README.md
```

## How to Compile

```bash
gcc overlapping_linked_lists.c -o overlapping_linked_lists
```

## How to Run

```bash
./overlapping_linked_lists
```

Example command sequence:

```text
read students.txt
writeN students_by_name.txt
writeM students_by_mark.txt
stop
```

After running the program, it generates output files such as:

```text
students_by_name.txt
students_by_mark.txt
```

The generated files can be compared with:

```text
expected_by_name.txt
expected_by_mark.txt
```