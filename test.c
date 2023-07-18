#include <stdio.h>

int main() {
    char* myString = "Hello";

    // Loop through the characters in the string and convert to ASCII in one go
    int i;
    for (i = 0; myString[i] != '\0'; i++) {
        int asciiValue = (int)myString[i];
        printf("Character: %c, ASCII value: %d\n", myString[i], asciiValue);
    }

    return 0;
}
