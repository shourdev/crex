#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a character is part of a word
bool isWordChar(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_';
}

// Function to replace the word starting with '%' with "%s"
void replaceWordsWithPercent(char *str) {
    char *readPtr = str;
    char *writePtr = str;

    while (*readPtr) {
        if (*readPtr == '%' && isWordChar(*(readPtr + 1))) {
            // Skip the word starting with '%'
            while (*readPtr && isWordChar(*readPtr)) {
                readPtr++;
            }
            strcpy(writePtr, "%s");
            writePtr += 2;
        } else {
            *writePtr++ = *readPtr++;
        }
    }
    *writePtr = '\0';
}

int main() {
    char str[] = "test %hi lol %bye";
    printf("Before: %s\n", str);

    // Create a writable array to store the modified string
    char modifiedStr[100]; // Adjust the size accordingly

    // Copy the original string to the writable array
    strcpy(modifiedStr, str);

    // Replace words starting with '%' in the writable array
    replaceWordsWithPercent(modifiedStr);

    printf("After:  %s\n", modifiedStr);
    return 0;
}
