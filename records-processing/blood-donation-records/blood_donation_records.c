/*
 * Project: Blood Donation Records
 * Description: Reads donor records and donation events, then summarizes the number and total amount of donations per donor.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LENGTH 6
#define MAX_NAME_LENGTH 21
#define MAX_LINE_LENGTH 256

typedef struct {
    char code[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    int donation_count;
    int total_amount_cc;
} Donor;

Donor *read_donors(const char *filename, int *donor_count);
void read_donations(const char *filename, Donor donors[], int donor_count);
int find_donor_by_code(const Donor donors[], int donor_count, const char *code);
void print_results(const Donor donors[], int donor_count);
FILE *open_file_or_exit(const char *filename, const char *mode);

int main(int argc, char *argv[]) {
    Donor *donors;
    int donor_count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <donors_file> <donations_file>\n", argv[0]);
        fprintf(stderr, "Example: %s donors.txt donations.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    donors = read_donors(argv[1], &donor_count);
    read_donations(argv[2], donors, donor_count);
    print_results(donors, donor_count);

    printf("\nDone. Processed %d donor record%s.\n",
           donor_count,
           donor_count == 1 ? "" : "s");

    free(donors);

    return EXIT_SUCCESS;
}

Donor *read_donors(const char *filename, int *donor_count) {
    FILE *input_file = open_file_or_exit(filename, "r");
    Donor *donors;
    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), input_file) != NULL) {
        char code[MAX_ID_LENGTH];
        char ignored_field[MAX_NAME_LENGTH];
        char surname[MAX_NAME_LENGTH];
        char name[MAX_NAME_LENGTH];

        if (sscanf(line, "%5s %20s %20s %20s", code, ignored_field, surname, name) == 4) {
            count++;
        }
    }

    if (count == 0) {
        fprintf(stderr, "Error: donor file '%s' does not contain valid donor records.\n", filename);
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    donors = calloc((size_t)count, sizeof(Donor));

    if (donors == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    rewind(input_file);

    int index = 0;
    while (index < count && fgets(line, sizeof(line), input_file) != NULL) {
        char ignored_field[MAX_NAME_LENGTH];

        if (sscanf(line,
                   "%5s %20s %20s %20s",
                   donors[index].code,
                   ignored_field,
                   donors[index].surname,
                   donors[index].name) == 4) {
            donors[index].donation_count = 0;
            donors[index].total_amount_cc = 0;
            index++;
        }
    }

    fclose(input_file);

    *donor_count = count;
    return donors;
}

void read_donations(const char *filename, Donor donors[], int donor_count) {
    FILE *input_file = open_file_or_exit(filename, "r");
    char code[MAX_ID_LENGTH];
    int amount_cc;

    while (fscanf(input_file, "%5s %d", code, &amount_cc) == 2) {
        int donor_index = find_donor_by_code(donors, donor_count, code);

        if (donor_index >= 0 && amount_cc > 0) {
            donors[donor_index].donation_count++;
            donors[donor_index].total_amount_cc += amount_cc;
        }
    }

    fclose(input_file);
}

int find_donor_by_code(const Donor donors[], int donor_count, const char *code) {
    for (int i = 0; i < donor_count; i++) {
        if (strcmp(code, donors[i].code) == 0) {
            return i;
        }
    }

    return -1;
}

void print_results(const Donor donors[], int donor_count) {
    printf("Blood donation summary:\n");

    for (int i = 0; i < donor_count; i++) {
        printf("%s %s %s: %d donation%s - %d cc\n",
               donors[i].code,
               donors[i].name,
               donors[i].surname,
               donors[i].donation_count,
               donors[i].donation_count == 1 ? "" : "s",
               donors[i].total_amount_cc);
    }
}

FILE *open_file_or_exit(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        fprintf(stderr, "Error: could not open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    return file;
}