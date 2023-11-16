#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Prototypes
int compareStrings(const void *a, const void *b);
int countWords(FILE *file);
void countLetters(char **word_array, int n_total_words, int *count_letters);

int main() {
    FILE *file;
    char word[MAX_WORD_LENGTH];
    char **word_array = NULL;
    int word_count = 0;
    int count_letters[26] = {0}; // Array to store counts for each letter

    // Open the file
    file = fopen("lusiadas.txt", "r");
    if (file == NULL) {
        printf("Error opening the file");
        return 1;
    }

    // Count the total number of words in the file
    word_count = countWords(file);

    // Allocate the array with the exact number of words
    word_array = (char **)malloc(word_count * sizeof(char *));
    if (word_array == NULL) {
        printf("Error allocating memory");
        fclose(file);
        return 1;
    }

    // Read words from the file and populate the array
    for (int i = 0; i < word_count; i++) {
        if (fscanf(file, "%s", word) == 1) {
            // Convert the word to lowercase
            for (int j = 0; word[j]; j++) {
                word[j] = tolower(word[j]);
            }

            // Allocate memory for the word
            word_array[i] = (char *)malloc(strlen(word) + 1);
            if (word_array[i] == NULL) {
                printf("Error allocating memory");
                fclose(file);
                return 1;
            }

            // Copy the word to the allocated memory
            strcpy(word_array[i], word);
        }
    }

    // Close the file
    fclose(file);

    // Count the number of words that start with each letter
    countLetters(word_array, word_count, count_letters);

    // Print the number of words that start with each letter
    for (char c = 'a'; c <= 'z'; c++) {
        printf("Words starting with '%c': %d\n", c, count_letters[c - 'a']);
    }

    // Print the total number of words
    printf("Total number of words: %d\n", word_count);

    // Free allocated memory
    for (int i = 0; i < word_count; i++) {
        free(word_array[i]);
    }
    free(word_array);

    return 0;
}

// Function to compare strings for qsort
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to count words in the file
int countWords(FILE *file) {
    int word_count = 0;
    char word[MAX_WORD_LENGTH];

    while (fscanf(file, "%s", word) == 1) {
        word_count++;
    }

    // Return to the beginning of the file for the second pass
    fseek(file, 0, SEEK_SET);

    return word_count;
}

// Function to count words that start with each letter
void countLetters(char **word_array, int n_total_words, int *count_letters) {
    for (int i = 0; i < n_total_words; i++) {
        char first_letter = word_array[i][0];
        if (isalpha(first_letter)) {
            count_letters[tolower(first_letter) - 'a']++;
        }
    }
}
