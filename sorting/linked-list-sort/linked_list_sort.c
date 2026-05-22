/*
 * Project: Linked List Sort
 * Description: Reads student records into a linked list and writes them sorted by surname or grade.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SURNAME_LENGTH 21
#define MAX_COMMAND_LENGTH 32
#define MAX_FILENAME_LENGTH 256

typedef struct Student {
    char surname[MAX_SURNAME_LENGTH];
    double grade;
    struct Student *next;
} Student;

Student *read_students_from_file(const char *filename);
Student *create_student(const char *surname, double grade);
Student *insert_by_surname(Student *sorted_head, Student *student);
Student *insert_by_grade(Student *sorted_head, Student *student);
Student *sort_by_surname(Student *head);
Student *sort_by_grade(Student *head);
void write_students_to_file(const char *filename, const Student *head);
void free_students(Student *head);
void print_help(void);
int is_valid_grade(double grade);

int main(void) {
    Student *head = NULL;
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

            free_students(head);
            head = read_students_from_file(filename);
        } else if (strcmp(command, "writeN") == 0) {
            if (scanf("%255s", filename) != 1) {
                fprintf(stderr, "Error: missing output filename.\n");
                break;
            }

            head = sort_by_surname(head);
            write_students_to_file(filename, head);
            printf("Done. Students sorted by surname saved to '%s'.\n", filename);
        } else if (strcmp(command, "writeM") == 0) {
            if (scanf("%255s", filename) != 1) {
                fprintf(stderr, "Error: missing output filename.\n");
                break;
            }

            head = sort_by_grade(head);
            write_students_to_file(filename, head);
            printf("Done. Students sorted by grade saved to '%s'.\n", filename);
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else if (strcmp(command, "stop") == 0) {
            break;
        } else {
            printf("Invalid command. Type 'help' to see the available commands.\n");
        }
    }

    free_students(head);
    printf("Done. Memory released successfully.\n");

    return EXIT_SUCCESS;
}

Student *read_students_from_file(const char *filename) {
    FILE *input_file = fopen(filename, "r");
    Student *head = NULL;
    Student *tail = NULL;
    char surname[MAX_SURNAME_LENGTH];
    double grade;
    int loaded_count = 0;

    if (input_file == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'.\n", filename);
        return NULL;
    }

    while (fscanf(input_file, "%20s %lf", surname, &grade) == 2) {
        Student *student;

        if (!is_valid_grade(grade)) {
            fprintf(stderr, "Warning: discarded invalid grade for student '%s'.\n", surname);
            continue;
        }

        student = create_student(surname, grade);

        if (head == NULL) {
            head = student;
            tail = student;
        } else {
            tail->next = student;
            tail = student;
        }

        loaded_count++;
    }

    fclose(input_file);

    printf("Loaded %d valid student record%s from '%s'.\n",
           loaded_count,
           loaded_count == 1 ? "" : "s",
           filename);

    return head;
}

Student *create_student(const char *surname, double grade) {
    Student *student = malloc(sizeof(Student));

    if (student == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(student->surname, surname, MAX_SURNAME_LENGTH - 1);
    student->surname[MAX_SURNAME_LENGTH - 1] = '\0';
    student->grade = grade;
    student->next = NULL;

    return student;
}

Student *insert_by_surname(Student *sorted_head, Student *student) {
    Student *current;

    if (sorted_head == NULL || strcmp(student->surname, sorted_head->surname) < 0) {
        student->next = sorted_head;
        return student;
    }

    current = sorted_head;

    while (current->next != NULL && strcmp(current->next->surname, student->surname) <= 0) {
        current = current->next;
    }

    student->next = current->next;
    current->next = student;

    return sorted_head;
}

Student *insert_by_grade(Student *sorted_head, Student *student) {
    Student *current;

    if (sorted_head == NULL || student->grade < sorted_head->grade) {
        student->next = sorted_head;
        return student;
    }

    current = sorted_head;

    while (current->next != NULL && current->next->grade <= student->grade) {
        current = current->next;
    }

    student->next = current->next;
    current->next = student;

    return sorted_head;
}

Student *sort_by_surname(Student *head) {
    Student *sorted_head = NULL;
    Student *current = head;

    while (current != NULL) {
        Student *next = current->next;
        current->next = NULL;
        sorted_head = insert_by_surname(sorted_head, current);
        current = next;
    }

    return sorted_head;
}

Student *sort_by_grade(Student *head) {
    Student *sorted_head = NULL;
    Student *current = head;

    while (current != NULL) {
        Student *next = current->next;
        current->next = NULL;
        sorted_head = insert_by_grade(sorted_head, current);
        current = next;
    }

    return sorted_head;
}

void write_students_to_file(const char *filename, const Student *head) {
    FILE *output_file = fopen(filename, "w");

    if (output_file == NULL) {
        fprintf(stderr, "Error: could not open output file '%s'.\n", filename);
        return;
    }

    while (head != NULL) {
        fprintf(output_file, "%s %.2f\n", head->surname, head->grade);
        head = head->next;
    }

    fclose(output_file);
}

void free_students(Student *head) {
    while (head != NULL) {
        Student *next = head->next;
        free(head);
        head = next;
    }
}

void print_help(void) {
    printf("Available commands:\n");
    printf("  read <filename>    Load student records from a file\n");
    printf("  writeN <filename>  Write students ordered by surname\n");
    printf("  writeM <filename>  Write students ordered by grade\n");
    printf("  help               Show this help message\n");
    printf("  stop               Exit the program\n");
}

int is_valid_grade(double grade) {
    return grade >= 0.0 && grade <= 30.0;
}