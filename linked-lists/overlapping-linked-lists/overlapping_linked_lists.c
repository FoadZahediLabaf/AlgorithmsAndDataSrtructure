/*
 * Project: Overlapped Lists
 * Description: Stores student exam records in two overlapped linked lists ordered by name and by mark.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 21
#define MAX_COMMAND_LENGTH 32
#define MAX_FILENAME_LENGTH 256

typedef struct Student {
    char name[MAX_NAME_LENGTH];
    double mark;
    struct Student *next_by_name;
    struct Student *next_by_mark;
} Student;

Student *insert_by_name(Student *head, Student *new_student);
Student *insert_by_mark(Student *head, Student *new_student);
Student *create_student(const char *name, double mark);
void read_students(const char *filename, Student **name_head, Student **mark_head);
void write_by_name(const char *filename, const Student *head);
void write_by_mark(const char *filename, const Student *head);
void free_students(Student *head);
void print_help(void);
int is_valid_mark(double mark);

int main(void) {
    Student *name_head = NULL;
    Student *mark_head = NULL;
    char command[MAX_COMMAND_LENGTH];
    char filename[MAX_FILENAME_LENGTH];

    print_help();

    while (1) {
        printf("\nCommand: ");

        if (scanf("%31s", command) != 1) {
            break;
        }

        if (strcmp(command, "read") == 0) {
            if (scanf("%255s", filename) != 1) {
                fprintf(stderr, "Error: missing input filename.\n");
                break;
            }

            read_students(filename, &name_head, &mark_head);
            printf("Done. Students loaded from '%s'.\n", filename);
        } else if (strcmp(command, "writeN") == 0) {
            if (scanf("%255s", filename) != 1) {
                fprintf(stderr, "Error: missing output filename.\n");
                break;
            }

            write_by_name(filename, name_head);
            printf("Done. Students ordered by name saved to '%s'.\n", filename);
        } else if (strcmp(command, "writeM") == 0) {
            if (scanf("%255s", filename) != 1) {
                fprintf(stderr, "Error: missing output filename.\n");
                break;
            }

            write_by_mark(filename, mark_head);
            printf("Done. Students ordered by mark saved to '%s'.\n", filename);
        } else if (strcmp(command, "stop") == 0) {
            break;
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else {
            printf("Invalid command. Type 'help' to see the available commands.\n");
        }
    }

    free_students(name_head);
    printf("Done. Memory released successfully.\n");

    return EXIT_SUCCESS;
}

Student *insert_by_name(Student *head, Student *new_student) {
    Student *current;

    if (head == NULL || strcmp(new_student->name, head->name) < 0) {
        new_student->next_by_name = head;
        return new_student;
    }

    current = head;

    while (current->next_by_name != NULL &&
           strcmp(current->next_by_name->name, new_student->name) <= 0) {
        current = current->next_by_name;
    }

    new_student->next_by_name = current->next_by_name;
    current->next_by_name = new_student;

    return head;
}

Student *insert_by_mark(Student *head, Student *new_student) {
    Student *current;

    if (head == NULL || new_student->mark < head->mark) {
        new_student->next_by_mark = head;
        return new_student;
    }

    current = head;

    while (current->next_by_mark != NULL && current->next_by_mark->mark <= new_student->mark) {
        current = current->next_by_mark;
    }

    new_student->next_by_mark = current->next_by_mark;
    current->next_by_mark = new_student;

    return head;
}

Student *create_student(const char *name, double mark) {
    Student *student = malloc(sizeof(Student));

    if (student == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(student->name, name, MAX_NAME_LENGTH - 1);
    student->name[MAX_NAME_LENGTH - 1] = '\0';
    student->mark = mark;
    student->next_by_name = NULL;
    student->next_by_mark = NULL;

    return student;
}

void read_students(const char *filename, Student **name_head, Student **mark_head) {
    FILE *input_file = fopen(filename, "r");
    char name[MAX_NAME_LENGTH];
    double mark;
    int loaded_count = 0;

    if (input_file == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'.\n", filename);
        return;
    }

    free_students(*name_head);
    *name_head = NULL;
    *mark_head = NULL;

    while (fscanf(input_file, "%20s %lf", name, &mark) == 2) {
        Student *student;

        if (!is_valid_mark(mark)) {
            fprintf(stderr, "Warning: discarded invalid mark for student '%s'.\n", name);
            continue;
        }

        student = create_student(name, mark);
        *name_head = insert_by_name(*name_head, student);
        *mark_head = insert_by_mark(*mark_head, student);
        loaded_count++;
    }

    fclose(input_file);

    printf("Loaded %d valid student record%s.\n",
           loaded_count,
           loaded_count == 1 ? "" : "s");
}

void write_by_name(const char *filename, const Student *head) {
    FILE *output_file = fopen(filename, "w");

    if (output_file == NULL) {
        fprintf(stderr, "Error: could not open output file '%s'.\n", filename);
        return;
    }

    while (head != NULL) {
        fprintf(output_file, "%s %.2f\n", head->name, head->mark);
        head = head->next_by_name;
    }

    fclose(output_file);
}

void write_by_mark(const char *filename, const Student *head) {
    FILE *output_file = fopen(filename, "w");

    if (output_file == NULL) {
        fprintf(stderr, "Error: could not open output file '%s'.\n", filename);
        return;
    }

    while (head != NULL) {
        fprintf(output_file, "%s %.2f\n", head->name, head->mark);
        head = head->next_by_mark;
    }

    fclose(output_file);
}

void free_students(Student *head) {
    Student *current = head;

    while (current != NULL) {
        Student *next = current->next_by_name;
        free(current);
        current = next;
    }
}

void print_help(void) {
    printf("Available commands:\n");
    printf("  read <filename>    Load student records from a file\n");
    printf("  writeN <filename>  Write students ordered by name\n");
    printf("  writeM <filename>  Write students ordered by mark\n");
    printf("  help               Show this help message\n");
    printf("  stop               Exit the program\n");
}

int is_valid_mark(double mark) {
    return mark >= 0.0 && mark <= 30.0;
}
