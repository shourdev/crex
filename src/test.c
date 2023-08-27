#include <stdio.h>
#include <stdarg.h>
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

void printvars(const char *format, int numVars, ...) {
    va_list args;
    va_start(args, numVars);

    const char *placeholder = format;
    while (*placeholder) {
        if (*placeholder == '%' && *(placeholder + 1) == 't') {
            placeholder += 2; // Move past '%t'
            int varIndex = *placeholder - '0'; // Extract variable index

            struct Var *var = va_arg(args, struct Var*);
            switch (var->type) {
                case STRING:
                    printf("%s", var->value.stringvalue);
                    break;
                case INT:
                    printf("%d", var->value.intvalue);
                    break;
                case FLOAT:
                    printf("%f", var->value.floatvalue);
                    break;
                default:
                    printf("Unknown type");
                    break;
            }
        } else {
            putchar(*placeholder);
        }

        placeholder++;
    }

    va_end(args);
}

int main() {
    struct Var test = {.type = INT, .value.intvalue = 42};
    struct Var test2 = {.type = FLOAT, .value.floatvalue = 3.14};

    printvars("hi %t0",1,&test);

    return 0;
}
