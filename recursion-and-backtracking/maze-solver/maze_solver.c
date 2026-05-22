/*
 * Project: Maze Solver
 * Description: Solves a maze using recursive backtracking and finds one path, all paths, and the shortest path.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>

#define START '@'
#define EXIT '#'
#define WALL '*'
#define OPEN ' '
#define PATH '$'
#define NO_PATH -1

static const int ROW_MOVES[] = { -1, 0, 0, 1 };
static const int COL_MOVES[] = { 0, 1, -1, 0 };
static const int MOVE_COUNT = 4;

typedef struct {
    char **cells;
    int rows;
    int cols;
    int start_row;
    int start_col;
} Maze;

Maze read_maze(const char *filename);
char **allocate_cells(int rows, int cols);
char **copy_cells(char **source, int rows, int cols);
void free_cells(char **cells, int rows);
void print_maze(char **cells, int rows, int cols);
int find_one_path(char **maze, int rows, int cols, int row, int col);
int count_all_paths(char **maze, int rows, int cols, int row, int col);
int find_shortest_path(char **maze,
                       char **best_path,
                       int rows,
                       int cols,
                       int row,
                       int col,
                       int current_steps,
                       int best_steps);
int is_inside_maze(int row, int col, int rows, int cols);
int is_walkable(char cell);
void restore_start_symbol(char **maze, int start_row, int start_col);

int main(int argc, char *argv[]) {
    Maze maze;
    char **maze_for_one_path;
    char **maze_for_all_paths;
    char **maze_for_shortest_path;
    char **best_path;
    int path_count;
    int shortest_steps;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        fprintf(stderr, "Example: %s in.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    maze = read_maze(argv[1]);

    printf("Original maze:\n");
    print_maze(maze.cells, maze.rows, maze.cols);

    maze_for_one_path = copy_cells(maze.cells, maze.rows, maze.cols);
    maze_for_all_paths = copy_cells(maze.cells, maze.rows, maze.cols);
    maze_for_shortest_path = copy_cells(maze.cells, maze.rows, maze.cols);
    best_path = copy_cells(maze.cells, maze.rows, maze.cols);

    if (maze_for_one_path == NULL || maze_for_all_paths == NULL ||
        maze_for_shortest_path == NULL || best_path == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free_cells(maze.cells, maze.rows);
        free_cells(maze_for_one_path, maze.rows);
        free_cells(maze_for_all_paths, maze.rows);
        free_cells(maze_for_shortest_path, maze.rows);
        free_cells(best_path, maze.rows);
        return EXIT_FAILURE;
    }

    printf("One path:\n");
    if (find_one_path(maze_for_one_path, maze.rows, maze.cols, maze.start_row, maze.start_col)) {
        restore_start_symbol(maze_for_one_path, maze.start_row, maze.start_col);
        print_maze(maze_for_one_path, maze.rows, maze.cols);
    } else {
        printf("No path found.\n\n");
    }

    path_count = count_all_paths(maze_for_all_paths, maze.rows, maze.cols, maze.start_row, maze.start_col);
    printf("Number of paths found: %d\n\n", path_count);

    shortest_steps = find_shortest_path(maze_for_shortest_path,
                                        best_path,
                                        maze.rows,
                                        maze.cols,
                                        maze.start_row,
                                        maze.start_col,
                                        0,
                                        NO_PATH);

    if (shortest_steps == NO_PATH) {
        printf("Shortest path: no path found.\n");
    } else {
        restore_start_symbol(best_path, maze.start_row, maze.start_col);
        printf("Shortest path (%d steps):\n", shortest_steps);
        print_maze(best_path, maze.rows, maze.cols);
    }

    free_cells(maze.cells, maze.rows);
    free_cells(maze_for_one_path, maze.rows);
    free_cells(maze_for_all_paths, maze.rows);
    free_cells(maze_for_shortest_path, maze.rows);
    free_cells(best_path, maze.rows);

    printf("Done. Maze processing completed.\n");

    return EXIT_SUCCESS;
}

Maze read_maze(const char *filename) {
    FILE *input_file = fopen(filename, "r");
    Maze maze;
    int start_count = 0;
    int exit_count = 0;

    if (input_file == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d %d", &maze.rows, &maze.cols) != 2) {
        fprintf(stderr, "Error: input file must start with the maze rows and columns.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    if (maze.rows <= 0 || maze.cols <= 0) {
        fprintf(stderr, "Error: maze dimensions must be positive.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    fgetc(input_file); /* Consume the newline after the dimensions. */

    maze.cells = allocate_cells(maze.rows, maze.cols);
    maze.start_row = -1;
    maze.start_col = -1;

    for (int row = 0; row < maze.rows; row++) {
        for (int col = 0; col < maze.cols; col++) {
            int ch = fgetc(input_file);

            while (ch == '\n' || ch == '\r') {
                ch = fgetc(input_file);
            }

            if (ch == EOF) {
                fprintf(stderr, "Error: maze file ended before all cells were read.\n");
                free_cells(maze.cells, maze.rows);
                fclose(input_file);
                exit(EXIT_FAILURE);
            }

            if (ch != START && ch != EXIT && ch != WALL && ch != OPEN) {
                fprintf(stderr, "Error: invalid maze character '%c'.\n", ch);
                free_cells(maze.cells, maze.rows);
                fclose(input_file);
                exit(EXIT_FAILURE);
            }

            maze.cells[row][col] = (char)ch;

            if (ch == START) {
                maze.start_row = row;
                maze.start_col = col;
                start_count++;
            } else if (ch == EXIT) {
                exit_count++;
            }
        }
    }

    fclose(input_file);

    if (start_count != 1) {
        fprintf(stderr, "Error: maze must contain exactly one start character '%c'.\n", START);
        free_cells(maze.cells, maze.rows);
        exit(EXIT_FAILURE);
    }

    if (exit_count < 1) {
        fprintf(stderr, "Error: maze must contain at least one exit character '%c'.\n", EXIT);
        free_cells(maze.cells, maze.rows);
        exit(EXIT_FAILURE);
    }

    return maze;
}

char **allocate_cells(int rows, int cols) {
    char **cells = malloc(rows * sizeof(char *));

    if (cells == NULL) {
        return NULL;
    }

    for (int row = 0; row < rows; row++) {
        cells[row] = malloc(cols * sizeof(char));

        if (cells[row] == NULL) {
            for (int i = 0; i < row; i++) {
                free(cells[i]);
            }
            free(cells);
            return NULL;
        }
    }

    return cells;
}

char **copy_cells(char **source, int rows, int cols) {
    char **copy = allocate_cells(rows, cols);

    if (copy == NULL) {
        return NULL;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            copy[row][col] = source[row][col];
        }
    }

    return copy;
}

void free_cells(char **cells, int rows) {
    if (cells == NULL) {
        return;
    }

    for (int row = 0; row < rows; row++) {
        free(cells[row]);
    }

    free(cells);
}

void print_maze(char **cells, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            putchar(cells[row][col]);
        }
        putchar('\n');
    }
    putchar('\n');
}

int find_one_path(char **maze, int rows, int cols, int row, int col) {
    if (!is_inside_maze(row, col, rows, cols) || !is_walkable(maze[row][col])) {
        return 0;
    }

    if (maze[row][col] == EXIT) {
        return 1;
    }

    char original_cell = maze[row][col];
    maze[row][col] = PATH;

    for (int i = 0; i < MOVE_COUNT; i++) {
        if (find_one_path(maze, rows, cols, row + ROW_MOVES[i], col + COL_MOVES[i])) {
            return 1;
        }
    }

    maze[row][col] = original_cell;
    return 0;
}

int count_all_paths(char **maze, int rows, int cols, int row, int col) {
    int count = 0;

    if (!is_inside_maze(row, col, rows, cols) || !is_walkable(maze[row][col])) {
        return 0;
    }

    if (maze[row][col] == EXIT) {
        return 1;
    }

    char original_cell = maze[row][col];
    maze[row][col] = PATH;

    for (int i = 0; i < MOVE_COUNT; i++) {
        count += count_all_paths(maze, rows, cols, row + ROW_MOVES[i], col + COL_MOVES[i]);
    }

    maze[row][col] = original_cell;
    return count;
}

int find_shortest_path(char **maze,
                       char **best_path,
                       int rows,
                       int cols,
                       int row,
                       int col,
                       int current_steps,
                       int best_steps) {
    if (!is_inside_maze(row, col, rows, cols) || !is_walkable(maze[row][col])) {
        return best_steps;
    }

    if (best_steps != NO_PATH && current_steps >= best_steps) {
        return best_steps;
    }

    if (maze[row][col] == EXIT) {
        if (best_steps == NO_PATH || current_steps < best_steps) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    best_path[r][c] = maze[r][c];
                }
            }
            return current_steps;
        }
        return best_steps;
    }

    char original_cell = maze[row][col];
    maze[row][col] = PATH;

    for (int i = 0; i < MOVE_COUNT; i++) {
        best_steps = find_shortest_path(maze,
                                        best_path,
                                        rows,
                                        cols,
                                        row + ROW_MOVES[i],
                                        col + COL_MOVES[i],
                                        current_steps + 1,
                                        best_steps);
    }

    maze[row][col] = original_cell;
    return best_steps;
}

int is_inside_maze(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

int is_walkable(char cell) {
    return cell == START || cell == OPEN || cell == EXIT;
}

void restore_start_symbol(char **maze, int start_row, int start_col) {
    maze[start_row][start_col] = START;
}