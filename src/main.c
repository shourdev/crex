

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool hasvarcode = false;
FILE *write;
typedef enum{
    FUNC_KEYWORD,
    INT,
    STRING,
    FLOAT,
    PLUS_OP,
    TOKEN_EOF
} type;
typedef struct{
    type type;
    char* value;
} Token;

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Dynamically allocate memory for the string
    char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
    if (buffer == NULL) {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t result = fread(buffer, 1, file_size, file);
    if (result != file_size) {
        printf("Error reading the file.\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0'; // Add null terminator at the end

    fclose(file);
    return buffer;
}

void lexer(char* string, Token** tokens, int* num_tokens) {
    int i = 0;
    int token_index = 0;
    int line = 1;
    *tokens = NULL;

    while (1) {
        while (isspace(string[i])) {
            if (string[i] == '\n') {
                line++;
            }
            i++;
        }

        if (string[i] == '\0') {
            // Handle end-of-file
            *tokens = realloc(*tokens, (token_index + 1) * sizeof(Token));
            (*tokens)[token_index].type = TOKEN_EOF;
            (*tokens)[token_index].value = NULL;
            *num_tokens = token_index + 1;
            return;
        }

        *tokens = realloc(*tokens, (token_index + 1) * sizeof(Token));

        if (string[i] == 'f' && string[i + 1] == 'u' && string[i + 2] == 'n' && string[i + 3] == 'c') {
            (*tokens)[token_index].type = FUNC_KEYWORD;
            (*tokens)[token_index].value = NULL;
            token_index += 1;
            i += 4;
        } else if (string[i] == '+') {
            (*tokens)[token_index].type = PLUS_OP;
            (*tokens)[token_index].value = NULL;
            token_index += 1;
            i += 1;
        } else if (isdigit(string[i])) {
            char *result = NULL;
            int resultLength = 0;

            while (isdigit(string[i]) && string[i] != '\n' && string[i] != '\0')
            {
                resultLength++;
                result = realloc(result, resultLength * sizeof(char));
                result[resultLength - 1] = string[i];
                i++;
            }

            result = realloc(result, (resultLength + 1) * sizeof(char));
            result[resultLength] = '\0';

            (*tokens)[token_index].type = INT;
            (*tokens)[token_index].value = result;
            token_index++;
        } 
 
       
    }
}


int main() {

FILE *FL;
FL = fopen("main.crf","r");

    char* file_content = read_file("main.crf");

 Token* tokens = NULL;
  int num_tokens = 0;

  lexer(file_content, &tokens, &num_tokens);
    for (int i = 0; i < num_tokens; i++) {
        switch (tokens[i].type) {
            case FUNC_KEYWORD:
                printf("Token: FUNCTION\n");
                break;
            case PLUS_OP:
                printf("Token: PLUS\n");
                break;
            case INT:
                printf("Token: INT_LITERAL, Value: %s\n", tokens[i].value);
                free(tokens[i].value);
                break;
            case TOKEN_EOF:
                printf("Token: EOF\n");
                break;
            case STRING:
                printf("Token: STRING, Value: %s\n",tokens[i].value);        }
    }

}