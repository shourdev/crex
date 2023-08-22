#include <stdio.h>
#include <stdlib.h>

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

int main() {
    struct Var *var1 = malloc(sizeof(struct Var)); // Allocate memory for the struct

    if (var1 == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    var1->type = STRING;
    var1->value.stringvalue = "";
    printf("%s\n", var1->value.stringvalue);
    var1->value.stringvalue = "helk";
        printf("%s\n", var1->value.stringvalue);
    free(var1); // Free allocated memory

    return 0;
}
