#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum types {
    STRING,
    INT,
    FLOAT
};

struct Var {
    enum types type;
    union {
        int intvalue;
        float floatvalue;
        char* stringvalue;
    } value;
};
void getStringInput(struct Var *var) {
    char inputChar;
    int maxLength = 0;
    int length = 0;

    // Calculate input length
    while ((inputChar = getchar()) != '\n' && inputChar != EOF) {
        length++;
        if (length > maxLength) {
            maxLength = length;
        }
    }

    // Allocate memory for the string
    var->value.stringvalue = malloc((maxLength + 1) * sizeof(char));
    if (var->value.stringvalue == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Reset input and read characters again into allocated memory
    fseek(stdin, 0, SEEK_SET);
    for (int i = 0; i < maxLength; i++) {
        inputChar = getchar();
        if (inputChar == '\n' || inputChar == EOF) {
            break;
        }
        var->value.stringvalue[i] = inputChar;
    }
    var->value.stringvalue[maxLength] = '\0'; // Null-terminate the string
    var->type = STRING;
}

int main() {

  struct Var *var1 = malloc(sizeof(struct Var)); // Allocate memory for the struct

    if (var1 == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    var1->type = STRING;

    // Read input from the user
    char *input = NULL;
    size_t input_size = 0;
    printf("Enter a string: ");
    getline(&input, &input_size, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove the newline character

    // Allocate memory and copy the input
    var1->value.stringvalue = malloc(strlen(input) + 1);


    strcpy(var1->value.stringvalue, input);

    // Print the stored string
    printf("Stored string: %s\n", var1->value.stringvalue);

    // Clean up
    free(input);
    free(var1->value.stringvalue);
    free(var1);

    return 0; // Exit successfully
}
