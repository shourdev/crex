#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    TOKEN_FUNC,
    TOKEN_FUNC_NAME,
    TOKEN_FUNC_BRACK,
    TOKEN_FUNC_START,
    TOKEN_FUNC_END,
    TOKEN_STD_LIB_COUT,
    TOKEN_FUNC_CALL,
    TOKEN_END,
    TOKEN_UNKNOWN,
    TOKEN_PAREN
} TokenType;

typedef struct {
    TokenType type;
    char *funcName;
} Token;

Token getNextToken(FILE *input) {
    int c;
    Token token;

    // Skip whitespace
    do {
        c = fgetc(input);
    } while (isspace(c));

    // Check for end of file
    if (c == EOF) {
        token.type = TOKEN_END;
        token.funcName = NULL; // Set funcName to NULL for TOKEN_END
        return token;
    }

    // Check for operators
    char buf[10];
    int i = 0;
    if (c == 'f') {
        // Check for "func" keyword
        buf[i++] = c;
        while ((c = fgetc(input)) != EOF && isalpha(c) && i < sizeof(buf) - 1) {
            buf[i++] = c;
        }
        buf[i] = '\0';
        if (strcmp(buf, "func") == 0) {
            token.type = TOKEN_FUNC;
            token.funcName = NULL; // Set funcName to NULL for TOKEN_FUNC
            return token;
        }
    } 
      if (c == 'o') {
        // Check for "func" keyword
        buf[i++] = c;
        while ((c = fgetc(input)) != EOF && isalpha(c) && i < sizeof(buf) - 1) {
            buf[i++] = c;
        }
        buf[i] = '\0';
        if (strcmp(buf, "over") == 0) {
            token.type = TOKEN_FUNC_END;
            token.funcName = NULL; // Set funcName to NULL for TOKEN_FUNC
            return token;
        }
    }
    else if (c == 'c') {
        // Check for "cout" keyword
        buf[i++] = c;
        while ((c = fgetc(input)) != EOF && isalpha(c) && i < sizeof(buf) - 1) {
            buf[i++] = c;
        }
        buf[i] = '\0';
        if (strcmp(buf, "cout") == 0) {
            token.type = TOKEN_STD_LIB_COUT;
            token.funcName = NULL; // Set funcName to NULL for TOKEN_STD_LIB_COUT
            return token;
        }
    } else if (isalpha(c) || c == '_') {
        // Identifier (function name or other names)
        buf[i++] = c;
        while ((c = fgetc(input)) != EOF && (isalnum(c) || c == '_') && i < sizeof(buf) - 1) {
            buf[i++] = c;
        }
        buf[i] = '\0';
        token.type = TOKEN_FUNC_NAME;
        token.funcName = strdup(buf); // Allocate memory for funcName and copy the string
        return token;
    } 
     else if (c == '(' || c == ')') {
        token.type = TOKEN_FUNC_BRACK;
        token.funcName = NULL; // Set funcName to NULL for TOKEN_FUNC_BRACK
    }
      else if (c == ':') {
        token.type = TOKEN_FUNC_CALL;
        token.funcName = NULL; // Set funcName to NULL for TOKEN_FUNC_START
    }
     else if (c == '-') {
        token.type = TOKEN_FUNC_START;
        token.funcName = NULL; // Set funcName to NULL for TOKEN_FUNC_START
    }
    else if (c == '\"') {
    token.type = TOKEN_PAREN;
    token.funcName = NULL; // Set funcName to NULL for TOKEN_FUNC_START
}
    else {
        token.type = TOKEN_UNKNOWN;
        token.funcName = NULL; // Set funcName to NULL for TOKEN_UNKNOWN
    }

    return token;
}

int main() {
    // Example usage
    FILE *input = fopen("test.crf", "r"); // Replace "input.txt" with your input file

    Token token;
    do {
        token = getNextToken(input);
        switch (token.type) {
            case TOKEN_FUNC:
                printf("func\n");
                break;
            case TOKEN_END:
                printf("end\n");
                break;
            case TOKEN_FUNC_BRACK:
                printf("func brack\n");
                break;
            case TOKEN_FUNC_CALL:
                printf("func call /\n");
                break;
            case TOKEN_FUNC_END:
                printf("func end\n");
                break;
            case TOKEN_FUNC_NAME:
                printf("name: %s\n", token.funcName); // Print the function name
                free(token.funcName); // Free the dynamically allocated funcName
                break;
            case TOKEN_FUNC_START:
                printf("func start\n");
                break;
            case TOKEN_STD_LIB_COUT:
                printf("cout\n");
                break;
            case TOKEN_UNKNOWN:
                printf("idk\n");
                break;
        }
    } while (token.type != TOKEN_END);

    fclose(input);
    return 0;
}
