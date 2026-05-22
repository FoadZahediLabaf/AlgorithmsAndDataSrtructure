/*
 * Project: Merge Sort
 * Description: Sorts an integer array using the merge sort algorithm.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_sort(int array[], int size);
void merge_sort_with_order(int array[], int size, int ascending);
void merge_sort_recursive(int array[], int temp[], int left, int right, int ascending);
void merge(int array[], int temp[], int left, int middle, int right, int ascending);
void print_array(const int array[], int size);
int parse_integer(const char *text, int *value);
void print_usage(const char *program_name);
int is_ascending_mode(const char *mode);
int is_descending_mode(const char *mode);

int main(int argc, char *argv[]) {
    int *array;
    int size;
    int ascending;

    if (argc < 3 || (!is_ascending_mode(argv[1]) && !is_descending_mode(argv[1]))) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    ascending = is_ascending_mode(argv[1]);
    size = argc - 2;
    array = malloc((size_t)size * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        if (!parse_integer(argv[i + 2], &array[i])) {
            fprintf(stderr, "Error: '%s' is not a valid integer.\n", argv[i + 2]);
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("Original array:\n");
    print_array(array, size);

    merge_sort_with_order(array, size, ascending);

    printf("Sorted array (%s):\n", ascending ? "ascending" : "descending");
    print_array(array, size);

    free(array);

    return EXIT_SUCCESS;
}

void merge_sort(int array[], int size) {
    merge_sort_with_order(array, size, 1);
}

void merge_sort_with_order(int array[], int size, int ascending) {
    if (array == NULL || size <= 1) {
        return;
    }

    int *temp = malloc((size_t)size * sizeof(int));

    if (temp == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    merge_sort_recursive(array, temp, 0, size - 1, ascending);

    free(temp);
}

void merge_sort_recursive(int array[], int temp[], int left, int right, int ascending) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    merge_sort_recursive(array, temp, left, middle, ascending);
    merge_sort_recursive(array, temp, middle + 1, right, ascending);
    merge(array, temp, left, middle, right, ascending);
}

void merge(int array[], int temp[], int left, int middle, int right, int ascending) {
    int left_index = left;
    int right_index = middle + 1;
    int temp_index = left;

    while (left_index <= middle && right_index <= right) {
        int should_take_left;

        if (ascending) {
            should_take_left = array[left_index] <= array[right_index];
        } else {
            should_take_left = array[left_index] >= array[right_index];
        }

        if (should_take_left) {
            temp[temp_index++] = array[left_index++];
        } else {
            temp[temp_index++] = array[right_index++];
        }
    }

    while (left_index <= middle) {
        temp[temp_index++] = array[left_index++];
    }

    while (right_index <= right) {
        temp[temp_index++] = array[right_index++];
    }

    for (int i = left; i <= right; i++) {
        array[i] = temp[i];
    }
}

void print_array(const int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);

        if (i < size - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

int parse_integer(const char *text, int *value) {
    char *end_ptr;
    long number = strtol(text, &end_ptr, 10);

    if (*text == '\0' || *end_ptr != '\0') {
        return 0;
    }

    *value = (int)number;
    return 1;
}

void print_usage(const char *program_name) {
    fprintf(stderr, "Usage: %s <-a|-d> <integer1> <integer2> ...\n", program_name);
    fprintf(stderr, "  -a  Sort in ascending order\n");
    fprintf(stderr, "  -d  Sort in descending order\n");
    fprintf(stderr, "Example ascending:  %s -a 9 3 7 1 0 4\n", program_name);
    fprintf(stderr, "Example descending: %s -d 9 3 7 1 0 4\n", program_name);
}

int is_ascending_mode(const char *mode) {
    return strcmp(mode, "-a") == 0;
}

int is_descending_mode(const char *mode) {
    return strcmp(mode, "-d") == 0;
}