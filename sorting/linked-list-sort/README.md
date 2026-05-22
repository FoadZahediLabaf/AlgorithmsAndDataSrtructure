

# Linked List Sort

## Overview

This project is a C program that reads student records from a text file, stores them in a linked list, and writes the records sorted by either surname or grade.

Each student record contains:

- a surname
- a grade

The program is command-based. The user can load records from a file, write them ordered by surname, write them ordered by grade, or stop the program.

## Problem Description

The program manages a simple linked list of student exam records.

It supports these commands:

```text
read <filename>
writeN <filename>
writeM <filename>
help
stop
```

Command meanings:

- `read <filename>` loads student records from an input file
- `writeN <filename>` writes the records ordered alphabetically by surname
- `writeM <filename>` writes the records ordered by grade from lowest to highest
- `help` prints the available commands
- `stop` exits the program and releases memory

## Input Format

The input file contains one student per line.

Format:

```text
surname grade
```

Example `students.txt`:

```text
Rossi 24
Bianchi 28.5
Verdi 19
Neri 30
Gallo 22.5
Conti 26
Ferrari 18
```

The surname is a string of at most 20 characters. The grade must be a value between `0` and `30`.

Invalid grades are skipped and reported with a warning.

## Output Format

The program writes sorted student records to output files.

### Output ordered by surname

Command:

```text
writeN students_by_name.txt
```

Expected output:

```text
Bianchi 28.50
Conti 26.00
Ferrari 18.00
Gallo 22.50
Neri 30.00
Rossi 24.00
Verdi 19.00
```

### Output ordered by grade

Command:

```text
writeM students_by_grade.txt
```

Expected output:

```text
Ferrari 18.00
Verdi 19.00
Gallo 22.50
Rossi 24.00
Conti 26.00
Bianchi 28.50
Neri 30.00
```

## How the Program Works

The program first reads the input file and creates a linked list of `Student` nodes.

Each node contains:

- the student surname
- the student grade
- a pointer to the next node

When the user runs `writeN`, the linked list is sorted by surname using insertion into a new sorted list.

When the user runs `writeM`, the linked list is sorted by grade using the same linked-list insertion idea, but comparing grades instead of surnames.

After sorting, the program writes the current linked list order to the requested output file.

Before the program exits, it frees all dynamically allocated nodes.

## Concepts Practiced

- Linked lists
- Structs and pointers
- Dynamic memory allocation
- File input and output
- String comparison with `strcmp`
- Sorting linked lists
- Command-based program execution
- Input validation
- Memory cleanup with `free`

## Project Files

```text
linked-list-sort/
├── linked_list_sort.c
├── students.txt
├── expected_by_name.txt
├── expected_by_grade.txt
└── README.md
```

## How to Compile

```bash
gcc linked_list_sort.c -o linked_list_sort
```

## How to Run

```bash
./linked_list_sort
```

Example command sequence inside the program:

```text
read students.txt
writeN students_by_name.txt
writeM students_by_grade.txt
stop
```

The generated files can be compared with:

```text
expected_by_name.txt
expected_by_grade.txt
```

## Notes

This project uses one linked list and reorders it depending on the requested output command.

It is different from the overlapping linked lists project, where the same nodes are connected in two separate orders at the same time.