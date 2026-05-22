

# Acronym Generator

## Overview

This project is a C program that generates acronyms from a list of words.

The program reads words from an input file and creates all possible acronyms by choosing one character from each word. The generated acronyms must alternate between letters and digits.

For example, one acronym can start with a letter, then use a digit from the next word, then a letter again, and so on. The program also tries the opposite pattern, starting with a digit first.

The generated acronyms are written to an output file.

## Problem Description

The input file starts with the number of words. After that, it contains the words used to generate the acronyms.

The program chooses exactly one valid character from each word. A valid acronym must follow one of these alternating patterns:

```text
letter digit letter digit ...
```

or:

```text
digit letter digit letter ...
```

Letters are converted to uppercase in the output. Digits remain unchanged.

## Input Format

The input file must start with a positive integer representing the number of words.

Format:

```text
number_of_words
word1
word2
word3
...
```

Example `input.txt`:

```text
3
ab1
c2d
3ef
```

Each word can contain letters, digits, or a mix of both.

## Output Format

The output file contains one generated acronym per line.

For the example above, possible generated acronyms include:

```text
A2E
A2F
B2E
B2F
1C3
1D3
```

The exact number of output lines depends on how many valid letters or digits exist in each word.

## How the Program Works

The program first reads the number of words from the input file. Then it stores each word dynamically in an array of `Word` structs.

After reading the input, the program uses recursion to generate all valid acronyms.

At each recursive step, the program:

1. looks at the current word
2. checks all characters in that word
3. selects only characters that match the expected type
4. moves to the next word and switches the expected type

The expected character type alternates between:

- letter
- digit

The program runs the recursive generation twice:

1. starting with a letter
2. starting with a digit

This allows it to generate both possible alternating acronym patterns.

## Concepts Practiced

- Recursion
- File input and output
- Dynamic memory allocation
- Arrays of structs
- String handling
- Character classification with `isalpha` and `isdigit`
- Uppercase conversion with `toupper`
- Command-line arguments
- Memory cleanup with `free`

## Project Files

```text
acronym-generator/
├── acronym_generator.c
├── input.txt
├── expected_output.txt
└── README.md
```

## How to Compile

```bash
gcc acronym_generator.c -o acronym_generator
```

## How to Run

```bash
./acronym_generator input.txt output.txt
```

After running the program, it generates:

```text
output.txt
```

The generated output can be compared with:

```text
expected_output.txt
```

## Example

Input file:

```text
3
ab1
c2d
3ef
```

Command:

```bash
./acronym_generator input.txt output.txt
```

Example output:

```text
A2E
A2F
B2E
B2F
1C3
1D3
```

## Notes

The program requires both an input filename and an output filename as command-line arguments. If they are missing, it prints a usage message.

The input file must contain exactly the number of words specified in the first line.