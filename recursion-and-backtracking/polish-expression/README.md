# Prefix Polish Notation Evaluator

## Overview

This project is a C program that evaluates arithmetic expressions written in prefix notation, also known as Polish notation.

In prefix notation, the operator is written before its operands. For example, the normal infix expression:

```text
(5 + 6) * 7
```

can be written in prefix notation as:

```text
* + 5 6 7
```

The program receives the expression as a single command-line string, evaluates it recursively, and prints the result.

## Source of the Exercise

The programming exercise is based on the **Prefix (Polish) Notation** problem from:

**Advanced Programming and Problem-Solving Strategies in C — Part II: Algorithms and Data Structures, Second Edition.**

Only the exercise idea and expression format are based on the book. The implementation in this repository was written and organized independently.

## Problem Description

The program parses a prefix expression passed as a single string and prints the result to standard output.

The supported binary operators are:

```text
+  addition
-  subtraction
*  multiplication
/  division
```

Each operator works on two operands. Operands can be integer or decimal values.

## Input Format

The expression must be passed as one quoted command-line argument.

Format:

```bash
./polish_expression "<prefix_expression>"
```

Example:

```bash
./polish_expression "+ 3.5 5.2"
```

This represents:

```text
3.5 + 5.2
```

## Output Format

The program prints the original expression and the evaluated result.

Example output:

```text
Expression: + 3.5 5.2
Result: 8.70
Done. Prefix expression evaluated successfully.
```

## Examples

### Simple expression

Command:

```bash
./polish_expression "+ 3.5 5.2"
```

Output:

```text
Expression: + 3.5 5.2
Result: 8.70
Done. Prefix expression evaluated successfully.
```

### Nested expression

Command:

```bash
./polish_expression "* + 5 6 7"
```

This represents:

```text
(5 + 6) * 7
```

Output:

```text
Expression: * + 5 6 7
Result: 77.00
Done. Prefix expression evaluated successfully.
```

### Expression with division

Command:

```bash
./polish_expression "* + 1.4 2.1 / - 4.4 0.4 2.0"
```

This represents:

```text
(1.4 + 2.1) * ((4.4 - 0.4) / 2.0)
```

Output:

```text
Expression: * + 1.4 2.1 / - 4.4 0.4 2.0
Result: 7.00
Done. Prefix expression evaluated successfully.
```

## How the Program Works

The program uses recursive parsing.

At each recursive step, it reads the next meaningful token in the expression:

1. If the character is an operator, the function recursively evaluates the left operand and the right operand.
2. If the character is a number, the function reads and returns that number.
3. The operator is then applied to the two recursive results.

Because every supported operator is binary, the prefix expression is unambiguous and does not need parentheses.

The program also checks for invalid expressions and division by zero.

## Concepts Practiced

- Recursion
- Prefix notation parsing
- Arithmetic expression evaluation
- Command-line arguments
- String scanning
- Floating-point values
- Character checking with `ctype.h`
- Error handling

## Project Files

```text
polish-expression/
├── polish_expression.c
└── README.md
```

## How to Compile

```bash
gcc polish_expression.c -o polish_expression
```

## How to Run

```bash
./polish_expression "+ 3.5 5.2"
```

or:

```bash
./polish_expression "* + 5 6 7"
```

## Notes

The expression should be wrapped in quotes so the shell passes it to the program as one single argument.

This implementation focuses on binary operators, decimal numbers, recursive evaluation, and basic expression validation.