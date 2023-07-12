#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char* checkString(const char* input) {
    const char delimiter = '%';
    char* words = NULL;
    bool hasPercentage = false;

    // Check if the input contains '%'
    if (strchr(input, delimiter) != NULL) {
        hasPercentage = true;

        // Create a copy of the input string
        char* inputCopy = strdup(input);

        // Find the words after each '%'
        char* token = strtok(inputCopy, " ");
        while (token != NULL) {
            if (token[0] == delimiter && strlen(token) > 1) {
                if (words == NULL) {
                    words = strdup(token + 1); // Exclude the '%' character
                } else {
                    // Append the comma and the word to the existing words
                    size_t len = strlen(words);
                    words = realloc(words, len + strlen(token) + 2); // +2 for comma and null terminator
                    strcat(words, ",");
                    strcat(words, token + 1); // Exclude the '%' character
                }
            }

            token = strtok(NULL, " ");
        }

        // Free the memory allocated for the input copy
        free(inputCopy);
    }

    // Return the appropriate value
    if (hasPercentage && words != NULL) {
        return words;
    } else {
        return strdup("1");
    }
}

int main() {
    char input[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    // Remove the trailing newline character
    input[strcspn(input, "\n")] = '\0';

    const char* result = checkString(input);

    // Print the individual words
    printf("Result: %s\n", result);

    // Free the memory allocated for the result
    free((void*)result);

    return 0;
}
