/*
 * Project: Region Marker
 * Description: Finds and labels connected empty regions in a 2D map using flood fill.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20
#define WALL 0
#define EMPTY -1

void read_map(const char *filename, int map[MAX_SIZE][MAX_SIZE], int *rows, int *cols);
void find_regions(int map[MAX_SIZE][MAX_SIZE], int rows, int cols);
void flood_fill(int map[MAX_SIZE][MAX_SIZE], int rows, int cols, int row, int col, int region_id);
void write_map(const char *filename, int map[MAX_SIZE][MAX_SIZE], int rows, int cols);
void print_map(int map[MAX_SIZE][MAX_SIZE], int rows, int cols);
int is_inside_map(int row, int col, int rows, int cols);

int main(int argc, char *argv[]) {
    int map[MAX_SIZE][MAX_SIZE];
    int rows = 0;
    int cols = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    read_map(argv[1], map, &rows, &cols);

    printf("Original map:\n");
    print_map(map, rows, cols);

    find_regions(map, rows, cols);

    printf("\nMarked regions:\n");
    print_map(map, rows, cols);

    write_map(argv[2], map, rows, cols);

    return EXIT_SUCCESS;
}

void read_map(const char *filename, int map[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    FILE *input_file = fopen(filename, "r");
    char line[MAX_SIZE + 2];
    int current_row = 0;
    int expected_cols = -1;

    if (input_file == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), input_file) != NULL) {
        int current_col = 0;

        if (current_row >= MAX_SIZE) {
            fprintf(stderr, "Error: map has more than %d rows.\n", MAX_SIZE);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }

        while (line[current_col] == '*' || line[current_col] == '.') {
            if (current_col >= MAX_SIZE) {
                fprintf(stderr, "Error: map has more than %d columns.\n", MAX_SIZE);
                fclose(input_file);
                exit(EXIT_FAILURE);
            }

            map[current_row][current_col] = (line[current_col] == '*') ? WALL : EMPTY;
            current_col++;
        }

        if (current_col == 0) {
            continue;
        }

        if (expected_cols == -1) {
            expected_cols = current_col;
        } else if (current_col != expected_cols) {
            fprintf(stderr, "Error: all map rows must have the same length.\n");
            fclose(input_file);
            exit(EXIT_FAILURE);
        }

        current_row++;
    }

    fclose(input_file);

    if (current_row == 0 || expected_cols == -1) {
        fprintf(stderr, "Error: input map is empty or invalid.\n");
        exit(EXIT_FAILURE);
    }

    *rows = current_row;
    *cols = expected_cols;
}

void find_regions(int map[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int region_count = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (map[row][col] == EMPTY) {
                region_count++;
                flood_fill(map, rows, cols, row, col, region_count);
            }
        }
    }
}

void flood_fill(int map[MAX_SIZE][MAX_SIZE], int rows, int cols, int row, int col, int region_id) {
    static const int ROW_MOVES[] = { 1, 0, 0, -1 };
    static const int COL_MOVES[] = { 0, 1, -1, 0 };
    const int move_count = 4;

    if (!is_inside_map(row, col, rows, cols) || map[row][col] != EMPTY) {
        return;
    }

    map[row][col] = region_id;

    for (int i = 0; i < move_count; i++) {
        flood_fill(map, rows, cols, row + ROW_MOVES[i], col + COL_MOVES[i], region_id);
    }
}

void write_map(const char *filename, int map[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    FILE *output_file = fopen(filename, "w");

    if (output_file == NULL) {
        fprintf(stderr, "Error: could not open output file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (map[row][col] == WALL) {
                fprintf(output_file, "*");
            } else {
                fprintf(output_file, "%d", map[row][col]);
            }
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);
}

void print_map(int map[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (map[row][col] == WALL) {
                printf(" * ");
            } else if (map[row][col] == EMPTY) {
                printf(" . ");
            } else {
                printf("%2d ", map[row][col]);
            }
        }
        printf("\n");
    }
}

int is_inside_map(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
