#include <stdio.h>
#include <string.h>

void removeTextAfterAsterisk(char *inputString) {
    char *asterisk = strchr(inputString, '*');
    if (asterisk != NULL) {
        *asterisk = '\0';
    }
}

int main() {
    char input[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    removeTextAfterAsterisk(input);

    printf("Result: %s\n", input);

    return 0;
}
