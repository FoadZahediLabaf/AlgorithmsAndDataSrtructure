

# Library Borrowing Records

## Overview

This project is a C program that processes simple library borrowing data from text files. It reads three input files containing library users, the book catalogue, and borrowing operations. After processing the data, it generates two output files:

- `users_borrows.txt`: lists each user and the books borrowed by that user
- `book_borrows.txt`: lists each book and the users who borrowed a copy of that book

The goal of the project is to practice working with structured data in C, especially file handling, structs, dynamic memory allocation, arrays, strings, and output file generation.

## Source of the Exercise

The programming exercise is based on the **Library** problem from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and file format are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

The program receives three input files:

1. A users file containing the library users
2. A catalogue file containing the available books
3. A borrows file containing the borrowing operations

Using these files, the program produces two reports:

1. A report grouped by user, showing which books each user borrowed
2. A report grouped by book, showing which users borrowed each book

All fields are strings without spaces, except the number of available copies in the catalogue file, which is an integer.

## Input Files

### `users.txt`

This file stores the list of library users.

Format:

```text
name phone role user_id
```

Example:

```text
Potter 011001 Wizard HP
Granger 011002 Witch HG
Weasley 011003 Wizard RW
```

Each line contains:

- user name
- phone number
- role/title
- unique user identifier

### `catalogue.txt`

This file stores the list of available books.

Format:

```text
writer title position book_id copies
```

Example:

```text
J.K.Rowling ThePhilosopher'sStone R1S2B1 JKR1 3
J.K.Rowling TheChamberOfSecrets R1S2B2 JKR2 3
J.K.Rowling ThePrisonerOfAzkaban R1S2B3 JKR3 2
```

Each line contains:

- writer name
- book title
- book position in the library
- unique book identifier
- number of available copies

### `borrows.txt`

This file stores the borrowing operations.

Format:

```text
user_id book_id date
```

Example:

```text
HG JKR5 10/09/2009
HG JKR6 05/09/2009
RW JKR1 15/08/2009
```

Each line contains:

- identifier of the user who borrowed the book
- identifier of the borrowed book
- date of the operation in `dd/mm/yyyy` format

## Output Files

### `users_borrows.txt`

This file contains the same user information from `users.txt`, plus the number of books borrowed by each user. After each user line, the program writes the borrowed book identifiers and the borrowing dates.

Example:

```text
Potter 011001 Wizard HP 2
JKR4 01/09/2009
JKR5 20/09/2009
Granger 011002 Witch HG 3
JKR5 10/09/2009
JKR6 05/09/2009
JKR7 15/09/2009
Weasley 011003 Wizard RW 1
JKR1 15/08/2009
```

### `book_borrows.txt`

This file contains the same book information from `catalogue.txt`, plus the number of borrowed copies for each book. After each book line, the program writes the user identifiers and borrowing dates for users who borrowed that book.

Example:

```text
J.K.Rowling ThePhilosopher'sStone R1S2B1 JKR1 3 1
RW 15/08/2009
J.K.Rowling TheChamberOfSecrets R1S2B2 JKR2 3 0
J.K.Rowling ThePrisonerOfAzkaban R1S2B3 JKR3 2 0
J.K.Rowling TheGobletOfFire R1S2B4 JKR4 3 1
HP 01/09/2009
```

## How the Program Works

The program first reads all users into an array of `User` structs. Then it reads all books into an array of `Book` structs. After that, it reads all borrow operations into an array of `Borrow` structs.

To generate `users_borrows.txt`, the program checks each user against all borrow records and counts how many records match the user's identifier.

To generate `book_borrows.txt`, the program checks each book against all borrow records and counts how many records match the book's identifier.

This approach is simple and easy to understand. It is suitable for practicing dynamic memory allocation and file processing in C.

## Concepts Practiced

- Structs
- Dynamic memory allocation
- File input and output
- Arrays of records
- String handling
- Searching through arrays
- Output file generation
- Memory cleanup with `free`

## Project Files

```text
library-borrowing-records/
├── library_borrowing_records.c
├── users.txt
├── catalogue.txt
├── borrows.txt
├── expected_users_borrows.txt
├── expected_book_borrows.txt
└── README.md
```

## How to Compile

```bash
gcc library_borrowing_records.c -o library_borrowing_records
```

## How to Run

```bash
./library_borrowing_records users.txt catalogue.txt borrows.txt
```

After running the program, it generates:

```text
users_borrows.txt
book_borrows.txt
```

The generated files can be compared with:

```text
expected_users_borrows.txt
expected_book_borrows.txt
```

## Example Output Message

```text
Done. Processed 3 users, 7 books, and 6 borrow records.
User borrow file saved to 'users_borrows.txt'.
Book borrow file saved to 'book_borrows.txt'.
```