

# Blood Donation Records

## Overview

This project is a C program that processes blood donation records for a simple blood bank system. The data is divided into two input files: one file contains donation operations, and the other file contains the real identity of the registered donors.

The program reads both files and prints a summary for each donor, including:

- the number of donations made by the donor
- the total amount of blood donated in cubic centimeters (cc)

The goal of the project is to practice file processing, structs, arrays, string comparison, and dynamic memory allocation in C.

## Source of the Exercise

The programming exercise is based on the **Blood Donations** problem from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and file format are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

The program receives two input files:

1. A voluntary file containing donor identity information
2. A donation file containing donation operations

The donation file may contain the same donor ID more than once, because a donor can donate blood multiple times. The program must compute the statistics for each donor in the voluntary file.

For every donor, the program reports:

- donor ID
- donor name and surname
- number of donations
- total amount of donated blood

## Input Files

### `voluntary.txt`

This file stores the real identity of all people registered in the blood bank system.

Format:

```text
id title surname name
```

Example:

```text
BS-00 Writer Bram Stoker
JH-YY Agent Jonathan Harker
VT-XX Cont Vlad Tepes
VH-ZZ Doctor Van Helsing
```

Each line contains:

- donor ID
- title
- surname
- name

### `donation.txt`

This file stores the blood donation operations.

Format:

```text
id quantity
```

Example:

```text
JH-YY 300
VH-ZZ 400
JH-YY 200
BS-00 500
JH-YY 600
VH-ZZ 400
```

Each line contains:

- donor ID
- donated blood quantity in cc

The same donor ID can appear more than once.

## Output

The program prints a summary for each donor.

Example output:

```text
BS-00 Bram Stoker: 1 donation - 500 cc
JH-YY Jonathan Harker: 3 donations - 1100 cc
VT-XX Vlad Tepes: 0 donations - 0 cc
VH-ZZ Van Helsing: 2 donations - 800 cc
```

The order of the output follows the order of the donors in `voluntary.txt`.

## How the Program Works

The program first reads the voluntary file and stores all donors in an array of `Donor` structs. Each donor starts with zero donations and zero total donated blood.

Then the program reads the donation file. For each donation record, it searches for the matching donor ID in the donor array. When a match is found, the program increases that donor's donation count and adds the donation quantity to the total amount.

Finally, the program prints the summary for all donors.

## Concepts Practiced

- Structs
- Dynamic memory allocation
- File input
- Arrays of records
- String comparison with `strcmp`
- Counting and accumulation
- Memory cleanup with `free`

## Project Files

```text
blood-donation-records/
├── blood_donation_records.c
├── voluntary.txt
├── donation.txt
├── expected_output.txt
└── README.md
```

## How to Compile

```bash
gcc blood_donation_records.c -o blood_donation_records
```

## How to Run

```bash
./blood_donation_records voluntary.txt donation.txt
```

## Example Output Message

```text
Blood donation summary:
BS-00 Bram Stoker: 1 donation - 500 cc
JH-YY Jonathan Harker: 3 donations - 1100 cc
VT-XX Vlad Tepes: 0 donations - 0 cc
VH-ZZ Van Helsing: 2 donations - 800 cc

Done. Processed 4 donor records.
```