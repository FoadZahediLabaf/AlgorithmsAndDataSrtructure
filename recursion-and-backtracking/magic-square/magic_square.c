/*
 * Project: Magic Square Solver
 * Description: Finds one n x n magic square using recursive backtracking.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>

int solve_magic_square(int **square, int *used_numbers, int size, int target_sum, int position);
int is_promising(int **square, int size, int target_sum, int row, int col);
int is_magic_square(int **square, int size, int target_sum);
int **allocate_square(int size);
void free_square(int **square, int size);
void initialize_square(int **square, int size);
void print_square(int **square, int size);
int parse_size(const char *input, int *size);

int main(int argc, char *argv[]) {
    int size;
    int target_sum;
    int **square;
    int *used_numbers;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        fprintf(stderr, "Example: %s 3\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_size(argv[1], &size) || size < 1) {
        fprintf(stderr, "Error: size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (size == 2) {
        printf("No normal 2x2 magic square exists.\n");
        return EXIT_SUCCESS;
    }

    target_sum = size * (size * size + 1) / 2;

    square = allocate_square(size);
    used_numbers = calloc((size * size) + 1, sizeof(int));

    if (square == NULL || used_numbers == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free_square(square, size);
        free(used_numbers);
        return EXIT_FAILURE;
    }

    initialize_square(square, size);

    if (solve_magic_square(square, used_numbers, size, target_sum, 0)) {
        printf("Magic square of size %d found.\n", size);
        printf("Magic constant: %d\n\n", target_sum);
        print_square(square, size);
    } else {
        printf("No magic square found for size %d.\n", size);
    }

    free_square(square, size);
    free(used_numbers);

    return EXIT_SUCCESS;
}

int solve_magic_square(int **square, int *used_numbers, int size, int target_sum, int position) {
    if (position == size * size) {
        return is_magic_square(square, size, target_sum);
    }

    int row = position / size;
    int col = position % size;

    for (int value = 1; value <= size * size; value++) {
        if (!used_numbers[value]) {
            square[row][col] = value;
            used_numbers[value] = 1;

            if (is_promising(square, size, target_sum, row, col) &&
                solve_magic_square(square, used_numbers, size, target_sum, position + 1)) {
                return 1;
            }

            used_numbers[value] = 0;
            square[row][col] = 0;
        }
    }

    return 0;
}

int is_promising(int **square, int size, int target_sum, int row, int col) {
    int row_sum = 0;
    int col_sum = 0;
    int main_diagonal_sum = 0;
    int anti_diagonal_sum = 0;

    for (int i = 0; i < size; i++) {
        row_sum += square[row][i];
        col_sum += square[i][col];
        main_diagonal_sum += square[i][i];
        anti_diagonal_sum += square[i][size - 1 - i];
    }

    if (col < size - 1 && row_sum >= target_sum) {
        return 0;
    }

    if (col == size - 1 && row_sum != target_sum) {
        return 0;
    }

    if (row < size - 1 && col_sum >= target_sum) {
        return 0;
    }

    if (row == size - 1 && col_sum != target_sum) {
        return 0;
    }

    if (row == col) {
        if (row < size - 1 && main_diagonal_sum >= target_sum) {
            return 0;
        }

        if (row == size - 1 && main_diagonal_sum != target_sum) {
            return 0;
        }
    }

    if (row + col == size - 1) {
        if (row < size - 1 && anti_diagonal_sum >= target_sum) {
            return 0;
        }

        if (row == size - 1 && anti_diagonal_sum != target_sum) {
            return 0;
        }
    }

    return 1;
}

int is_magic_square(int **square, int size, int target_sum) {
    int main_diagonal_sum = 0;
    int anti_diagonal_sum = 0;

    for (int i = 0; i < size; i++) {
        int row_sum = 0;
        int col_sum = 0;

        for (int j = 0; j < size; j++) {
            row_sum += square[i][j];
            col_sum += square[j][i];
        }

        if (row_sum != target_sum || col_sum != target_sum) {
            return 0;
        }

        main_diagonal_sum += square[i][i];
        anti_diagonal_sum += square[i][size - 1 - i];
    }

    return main_diagonal_sum == target_sum && anti_diagonal_sum == target_sum;
}

int **allocate_square(int size) {
    int **square = malloc(size * sizeof(int *));

    if (square == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        square[i] = malloc(size * sizeof(int));

        if (square[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
    }

    return square;
}

void free_square(int **square, int size) {
    if (square == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        free(square[i]);
    }

    free(square);
}

void initialize_square(int **square, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            square[row][col] = 0;
        }
    }
}

void print_square(int **square, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("%3d ", square[row][col]);
        }
        printf("\n");
    }
}

int parse_size(const char *input, int *size) {
    char *end_ptr;
    long value = strtol(input, &end_ptr, 10);

    if (*input == '\0' || *end_ptr != '\0') {
        return 0;
    }

    if (value < 1 || value > 10) {
        return 0;
    }

    *size = (int)value;
    return 1;
}
