/*
 * Project: Acronym Generator
 * Description: Generates acronyms by choosing one character from each word, alternating between letters and digits.
 * Author: Foad Zahedi Labaf
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

typedef enum {
    EXPECT_LETTER,
    EXPECT_DIGIT
} CharacterType;

typedef struct {
    char *text;
    int length;
} Word;

Word *read_words_from_file(const char *filename, int *word_count);
void generate_acronyms(const Word words[], int word_count, const char *output_filename);
void generate_acronyms_recursive(const Word words[],
                                 FILE *output_file,
                                 char acronym[],
                                 int index,
                                 int word_count,
                                 CharacterType expected_type);
void write_acronym(FILE *output_file, const char acronym[], int length);
char *duplicate_string(const char *source);
int character_matches_type(char character, CharacterType expected_type);
CharacterType opposite_type(CharacterType type);
void free_words(Word words[], int word_count);

int main(int argc, char *argv[]) {
    int word_count;
    Word *words;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    words = read_words_from_file(argv[1], &word_count);
    generate_acronyms(words, word_count, argv[2]);
    printf("Done. Acronyms saved to '%s'.\n", argv[2]);

    free_words(words, word_count);

    return EXIT_SUCCESS;
}

Word *read_words_from_file(const char *filename, int *word_count) {
    FILE *input_file = fopen(filename, "r");
    Word *words;
    char buffer[MAX_WORD_LENGTH + 1];

    if (input_file == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(input_file, "%d", word_count) != 1 || *word_count <= 0) {
        fprintf(stderr, "Error: input file must start with a positive number of words.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    words = calloc((size_t)*word_count, sizeof(Word));

    if (words == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *word_count; i++) {
        if (fscanf(input_file, "%100s", buffer) != 1) {
            fprintf(stderr, "Error: expected %d words, but the file contains fewer.\n", *word_count);
            free_words(words, i);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }

        words[i].text = duplicate_string(buffer);
        words[i].length = (int)strlen(buffer);

        if (words[i].text == NULL) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free_words(words, i);
            fclose(input_file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(input_file);
    return words;
}

void generate_acronyms(const Word words[], int word_count, const char *output_filename) {
    FILE *output_file = fopen(output_filename, "w");
    char *acronym = malloc(((size_t)word_count + 1) * sizeof(char));

    if (output_file == NULL) {
        fprintf(stderr, "Error: could not open output file '%s'.\n", output_filename);
        free(acronym);
        exit(EXIT_FAILURE);
    }

    if (acronym == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    generate_acronyms_recursive(words, output_file, acronym, 0, word_count, EXPECT_LETTER);
    generate_acronyms_recursive(words, output_file, acronym, 0, word_count, EXPECT_DIGIT);

    free(acronym);
    fclose(output_file);
}

void generate_acronyms_recursive(const Word words[],
                                 FILE *output_file,
                                 char acronym[],
                                 int index,
                                 int word_count,
                                 CharacterType expected_type) {
    if (index == word_count) {
        acronym[index] = '\0';
        write_acronym(output_file, acronym, word_count);
        return;
    }

    for (int i = 0; i < words[index].length; i++) {
        char current = words[index].text[i];

        if (character_matches_type(current, expected_type)) {
            acronym[index] = current;
            generate_acronyms_recursive(words,
                                        output_file,
                                        acronym,
                                        index + 1,
                                        word_count,
                                        opposite_type(expected_type));
        }
    }
}

void write_acronym(FILE *output_file, const char acronym[], int length) {
    for (int i = 0; i < length; i++) {
        fputc(toupper((unsigned char)acronym[i]), output_file);
    }

    fputc('\n', output_file);
}

char *duplicate_string(const char *source) {
    size_t length = strlen(source) + 1;
    char *copy = malloc(length * sizeof(char));

    if (copy != NULL) {
        memcpy(copy, source, length);
    }

    return copy;
}

int character_matches_type(char character, CharacterType expected_type) {
    unsigned char value = (unsigned char)character;

    if (expected_type == EXPECT_LETTER) {
        return isalpha(value) != 0;
    }

    return isdigit(value) != 0;
}

CharacterType opposite_type(CharacterType type) {
    return type == EXPECT_LETTER ? EXPECT_DIGIT : EXPECT_LETTER;
}

void free_words(Word words[], int word_count) {
    if (words == NULL) {
        return;
    }

    for (int i = 0; i < word_count; i++) {
        free(words[i].text);
    }

    free(words);
}
