/*
 * Project: Knight's Tour
 * Description: Solves the Knight's Tour problem on an 8x8 chessboard using recursive backtracking.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define TOTAL_SQUARES (BOARD_SIZE * BOARD_SIZE)
#define KNIGHT_MOVES 8

static const int ROW_MOVES[KNIGHT_MOVES] = { 2, 1, -1, -2, -2, -1, 1, 2 };
static const int COL_MOVES[KNIGHT_MOVES] = { 1, 2, 2, 1, -1, -2, -2, -1 };

typedef struct MoveOption {
    int row;
    int col;
    int onward_moves;
} MoveOption;

int solve_knight_tour(int board[BOARD_SIZE][BOARD_SIZE],
                      int row,
                      int col,
                      int start_row,
                      int start_col,
                      int move_number,
                      int *is_closed_tour);
int collect_ordered_moves(const int board[BOARD_SIZE][BOARD_SIZE],
                          int row,
                          int col,
                          MoveOption moves[KNIGHT_MOVES]);
int count_onward_moves(const int board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void sort_moves_by_onward_count(MoveOption moves[], int move_count);
int is_valid_position(int row, int col);
int is_closed_move(int row, int col, int start_row, int start_col);
void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]);
void print_board(const int board[BOARD_SIZE][BOARD_SIZE]);

int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE];
    int start_row;
    int start_col;
    int is_closed_tour = 0;

    initialize_board(board);

    printf("Enter the knight's starting position (row column, 0-7): ");

    if (scanf("%d %d", &start_row, &start_col) != 2) {
        fprintf(stderr, "Error: invalid input. Please enter two integers.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_position(start_row, start_col)) {
        fprintf(stderr, "Error: position must be inside the board, from 0 to 7.\n");
        return EXIT_FAILURE;
    }

    board[start_row][start_col] = 1;

    if (solve_knight_tour(board, start_row, start_col, start_row, start_col, 1, &is_closed_tour)) {
        printf("\nKnight's tour found.\n");
        printf("Tour type: %s\n\n", is_closed_tour ? "closed tour" : "open tour");
        print_board(board);
    } else {
        printf("\nNo knight's tour found from this starting position.\n");
    }

    printf("\nDone. Knight's tour processing completed.\n");

    return EXIT_SUCCESS;
}

int solve_knight_tour(int board[BOARD_SIZE][BOARD_SIZE],
                      int row,
                      int col,
                      int start_row,
                      int start_col,
                      int move_number,
                      int *is_closed_tour) {
    MoveOption moves[KNIGHT_MOVES];
    int move_count;

    if (move_number == TOTAL_SQUARES) {
        *is_closed_tour = is_closed_move(row, col, start_row, start_col);
        return 1;
    }

    move_count = collect_ordered_moves(board, row, col, moves);

    for (int i = 0; i < move_count; i++) {
        int next_row = moves[i].row;
        int next_col = moves[i].col;

        board[next_row][next_col] = move_number + 1;

        if (solve_knight_tour(board,
                              next_row,
                              next_col,
                              start_row,
                              start_col,
                              move_number + 1,
                              is_closed_tour)) {
            return 1;
        }

        board[next_row][next_col] = 0;
    }

    return 0;
}

int collect_ordered_moves(const int board[BOARD_SIZE][BOARD_SIZE],
                          int row,
                          int col,
                          MoveOption moves[KNIGHT_MOVES]) {
    int move_count = 0;

    for (int i = 0; i < KNIGHT_MOVES; i++) {
        int next_row = row + ROW_MOVES[i];
        int next_col = col + COL_MOVES[i];

        if (is_valid_position(next_row, next_col) && board[next_row][next_col] == 0) {
            moves[move_count].row = next_row;
            moves[move_count].col = next_col;
            moves[move_count].onward_moves = count_onward_moves(board, next_row, next_col);
            move_count++;
        }
    }

    sort_moves_by_onward_count(moves, move_count);

    return move_count;
}

int count_onward_moves(const int board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    int count = 0;

    for (int i = 0; i < KNIGHT_MOVES; i++) {
        int next_row = row + ROW_MOVES[i];
        int next_col = col + COL_MOVES[i];

        if (is_valid_position(next_row, next_col) && board[next_row][next_col] == 0) {
            count++;
        }
    }

    return count;
}

void sort_moves_by_onward_count(MoveOption moves[], int move_count) {
    for (int i = 0; i < move_count - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < move_count; j++) {
            if (moves[j].onward_moves < moves[min_index].onward_moves) {
                min_index = j;
            }
        }

        if (min_index != i) {
            MoveOption temporary = moves[i];
            moves[i] = moves[min_index];
            moves[min_index] = temporary;
        }
    }
}

int is_valid_position(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

int is_closed_move(int row, int col, int start_row, int start_col) {
    for (int i = 0; i < KNIGHT_MOVES; i++) {
        if (row + ROW_MOVES[i] == start_row && col + COL_MOVES[i] == start_col) {
            return 1;
        }
    }

    return 0;
}

void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = 0;
        }
    }
}

void print_board(const int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("%3d ", board[row][col]);
        }
        printf("\n");
    }
}