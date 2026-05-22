/*
 * Project: Prefix Polish Notation Evaluator
 * Description: Recursively evaluates arithmetic expressions written in prefix notation.
 * Author: Foad Zahedi Labaf
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-7

double evaluate_expression(const char expression[], int *position, int *is_valid);
void skip_spaces(const char expression[], int *position);
int is_operator(char character);
void print_usage(const char *program_name);

int main(int argc, char *argv[]) {
    int position = 0;
    int is_valid = 1;
    double result;

    if (argc != 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    result = evaluate_expression(argv[1], &position, &is_valid);
    skip_spaces(argv[1], &position);

    if (!is_valid || argv[1][position] != '\0') {
        fprintf(stderr, "Error: invalid prefix expression.\n");
        return EXIT_FAILURE;
    }

    printf("Expression: %s\n", argv[1]);
    printf("Result: %.2f\n", result);
    printf("Done. Prefix expression evaluated successfully.\n");

    return EXIT_SUCCESS;
}

double evaluate_expression(const char expression[], int *position, int *is_valid) {
    char *end_pointer;
    char current_character;
    double left_operand;
    double right_operand;
    double value;

    skip_spaces(expression, position);
    current_character = expression[*position];

    if (current_character == '\0') {
        *is_valid = 0;
        return 0.0;
    }

    if (is_operator(current_character) &&
        (expression[*position + 1] == '\0' || isspace((unsigned char)expression[*position + 1]))) {
        (*position)++;

        left_operand = evaluate_expression(expression, position, is_valid);
        right_operand = evaluate_expression(expression, position, is_valid);

        if (!*is_valid) {
            return 0.0;
        }

        switch (current_character) {
            case '+':
                return left_operand + right_operand;
            case '-':
                return left_operand - right_operand;
            case '*':
                return left_operand * right_operand;
            case '/':
                if (right_operand > -EPSILON && right_operand < EPSILON) {
                    fprintf(stderr, "Error: division by zero.\n");
                    *is_valid = 0;
                    return 0.0;
                }
                return left_operand / right_operand;
            default:
                *is_valid = 0;
                return 0.0;
        }
    }

    value = strtod(&expression[*position], &end_pointer);

    if (end_pointer == &expression[*position]) {
        *is_valid = 0;
        return 0.0;
    }

    *position = (int)(end_pointer - expression);
    return value;
}

void skip_spaces(const char expression[], int *position) {
    while (isspace((unsigned char)expression[*position])) {
        (*position)++;
    }
}

int is_operator(char character) {
    return character == '+' || character == '-' || character == '*' || character == '/';
}

void print_usage(const char *program_name) {
    fprintf(stderr, "Usage: %s \"<prefix_expression>\"\n", program_name);
    fprintf(stderr, "Example: %s \"+ 3.5 5.2\"\n", program_name);
    fprintf(stderr, "Example: %s \"* + 5 6 7\"\n", program_name);
}