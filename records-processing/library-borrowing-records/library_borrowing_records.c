/*
 * Project: Library Borrowing Records
 * Description: Reads users, catalogue, and borrow records, then generates users_borrows.txt and book_borrows.txt.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LENGTH 101
#define USERS_BORROWS_FILE "users_borrows.txt"
#define BOOK_BORROWS_FILE "book_borrows.txt"

typedef struct Book {
    char *writer;
    char *title;
    char *position;
    char *id;
    int copies;
} Book;

typedef struct User {
    char *name;
    char *phone;
    char *role;
    char *id;
} User;

typedef struct Borrow {
    char *user_id;
    char *book_id;
    char *date;
} Borrow;

User *read_users(const char *filename, int *user_count);
Book *read_books(const char *filename, int *book_count);
Borrow *read_borrows(const char *filename, int *borrow_count);
void write_users_borrows(const char *filename,
                         const User users[],
                         int user_count,
                         const Borrow borrows[],
                         int borrow_count);
void write_book_borrows(const char *filename,
                        const Book books[],
                        int book_count,
                        const Borrow borrows[],
                        int borrow_count);
int count_user_borrows(const Borrow borrows[], int borrow_count, const char *user_id);
int count_book_borrows(const Borrow borrows[], int borrow_count, const char *book_id);
char *duplicate_string(const char *text);
FILE *open_file_or_exit(const char *filename, const char *mode);
void free_users(User users[], int user_count);
void free_books(Book books[], int book_count);
void free_borrows(Borrow borrows[], int borrow_count);

int main(int argc, char *argv[]) {
    User *users;
    Book *books;
    Borrow *borrows;
    int user_count;
    int book_count;
    int borrow_count;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <users_file> <catalogue_file> <borrows_file>\n", argv[0]);
        fprintf(stderr, "Example: %s users.txt catalogue.txt borrows.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    users = read_users(argv[1], &user_count);
    books = read_books(argv[2], &book_count);
    borrows = read_borrows(argv[3], &borrow_count);

    write_users_borrows(USERS_BORROWS_FILE, users, user_count, borrows, borrow_count);
    write_book_borrows(BOOK_BORROWS_FILE, books, book_count, borrows, borrow_count);

    printf("Done. Processed %d users, %d books, and %d borrow records.\n",
           user_count,
           book_count,
           borrow_count);
    printf("User borrow file saved to '%s'.\n", USERS_BORROWS_FILE);
    printf("Book borrow file saved to '%s'.\n", BOOK_BORROWS_FILE);

    free_borrows(borrows, borrow_count);
    free_books(books, book_count);
    free_users(users, user_count);

    return EXIT_SUCCESS;
}

User *read_users(const char *filename, int *user_count) {
    FILE *input_file = open_file_or_exit(filename, "r");
    User *users;
    char name[MAX_FIELD_LENGTH];
    char phone[MAX_FIELD_LENGTH];
    char role[MAX_FIELD_LENGTH];
    char id[MAX_FIELD_LENGTH];
    int count = 0;

    while (fscanf(input_file, "%s %s %s %s", name, phone, role, id) == 4) {
        count++;
    }

    users = calloc((size_t)count, sizeof(User));

    if (users == NULL && count > 0) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    rewind(input_file);

    for (int i = 0; i < count; i++) {
        fscanf(input_file, "%s %s %s %s", name, phone, role, id);

        users[i].name = duplicate_string(name);
        users[i].phone = duplicate_string(phone);
        users[i].role = duplicate_string(role);
        users[i].id = duplicate_string(id);

        if (users[i].name == NULL || users[i].phone == NULL ||
            users[i].role == NULL || users[i].id == NULL) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free_users(users, i + 1);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(input_file);
    *user_count = count;
    return users;
}

Book *read_books(const char *filename, int *book_count) {
    FILE *input_file = open_file_or_exit(filename, "r");
    Book *books;
    char writer[MAX_FIELD_LENGTH];
    char title[MAX_FIELD_LENGTH];
    char position[MAX_FIELD_LENGTH];
    char id[MAX_FIELD_LENGTH];
    int copies;
    int count = 0;

    while (fscanf(input_file, "%s %s %s %s %d", writer, title, position, id, &copies) == 5) {
        count++;
    }

    books = calloc((size_t)count, sizeof(Book));

    if (books == NULL && count > 0) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    rewind(input_file);

    for (int i = 0; i < count; i++) {
        fscanf(input_file, "%s %s %s %s %d", writer, title, position, id, &copies);

        books[i].writer = duplicate_string(writer);
        books[i].title = duplicate_string(title);
        books[i].position = duplicate_string(position);
        books[i].id = duplicate_string(id);
        books[i].copies = copies;

        if (books[i].writer == NULL || books[i].title == NULL ||
            books[i].position == NULL || books[i].id == NULL) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free_books(books, i + 1);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(input_file);
    *book_count = count;
    return books;
}

Borrow *read_borrows(const char *filename, int *borrow_count) {
    FILE *input_file = open_file_or_exit(filename, "r");
    Borrow *borrows;
    char user_id[MAX_FIELD_LENGTH];
    char book_id[MAX_FIELD_LENGTH];
    char date[MAX_FIELD_LENGTH];
    int count = 0;

    while (fscanf(input_file, "%s %s %s", user_id, book_id, date) == 3) {
        count++;
    }

    borrows = calloc((size_t)count, sizeof(Borrow));

    if (borrows == NULL && count > 0) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    rewind(input_file);

    for (int i = 0; i < count; i++) {
        fscanf(input_file, "%s %s %s", user_id, book_id, date);

        borrows[i].user_id = duplicate_string(user_id);
        borrows[i].book_id = duplicate_string(book_id);
        borrows[i].date = duplicate_string(date);

        if (borrows[i].user_id == NULL || borrows[i].book_id == NULL || borrows[i].date == NULL) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free_borrows(borrows, i + 1);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(input_file);
    *borrow_count = count;
    return borrows;
}

void write_users_borrows(const char *filename,
                         const User users[],
                         int user_count,
                         const Borrow borrows[],
                         int borrow_count) {
    FILE *output_file = open_file_or_exit(filename, "w");

    for (int i = 0; i < user_count; i++) {
        int total = count_user_borrows(borrows, borrow_count, users[i].id);

        fprintf(output_file,
                "%s %s %s %s %d\n",
                users[i].name,
                users[i].phone,
                users[i].role,
                users[i].id,
                total);

        for (int j = 0; j < borrow_count; j++) {
            if (strcmp(borrows[j].user_id, users[i].id) == 0) {
                fprintf(output_file, "%s %s\n", borrows[j].book_id, borrows[j].date);
            }
        }
    }

    fclose(output_file);
}

void write_book_borrows(const char *filename,
                        const Book books[],
                        int book_count,
                        const Borrow borrows[],
                        int borrow_count) {
    FILE *output_file = open_file_or_exit(filename, "w");

    for (int i = 0; i < book_count; i++) {
        int total = count_book_borrows(borrows, borrow_count, books[i].id);

        fprintf(output_file,
                "%s %s %s %s %d %d\n",
                books[i].writer,
                books[i].title,
                books[i].position,
                books[i].id,
                books[i].copies,
                total);

        for (int j = 0; j < borrow_count; j++) {
            if (strcmp(borrows[j].book_id, books[i].id) == 0) {
                fprintf(output_file, "%s %s\n", borrows[j].user_id, borrows[j].date);
            }
        }
    }

    fclose(output_file);
}

int count_user_borrows(const Borrow borrows[], int borrow_count, const char *user_id) {
    int count = 0;

    for (int i = 0; i < borrow_count; i++) {
        if (strcmp(borrows[i].user_id, user_id) == 0) {
            count++;
        }
    }

    return count;
}

int count_book_borrows(const Borrow borrows[], int borrow_count, const char *book_id) {
    int count = 0;

    for (int i = 0; i < borrow_count; i++) {
        if (strcmp(borrows[i].book_id, book_id) == 0) {
            count++;
        }
    }

    return count;
}

char *duplicate_string(const char *text) {
    size_t length = strlen(text) + 1;
    char *copy = malloc(length);

    if (copy != NULL) {
        memcpy(copy, text, length);
    }

    return copy;
}

FILE *open_file_or_exit(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        fprintf(stderr, "Error: could not open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

void free_users(User users[], int user_count) {
    if (users == NULL) {
        return;
    }

    for (int i = 0; i < user_count; i++) {
        free(users[i].name);
        free(users[i].phone);
        free(users[i].role);
        free(users[i].id);
    }

    free(users);
}

void free_books(Book books[], int book_count) {
    if (books == NULL) {
        return;
    }

    for (int i = 0; i < book_count; i++) {
        free(books[i].writer);
        free(books[i].title);
        free(books[i].position);
        free(books[i].id);
    }

    free(books);
}

void free_borrows(Borrow borrows[], int borrow_count) {
    if (borrows == NULL) {
        return;
    }

    for (int i = 0; i < borrow_count; i++) {
        free(borrows[i].user_id);
        free(borrows[i].book_id);
        free(borrows[i].date);
    }

    free(borrows);
}