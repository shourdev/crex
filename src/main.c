/*
This is the main file of the crex compiler.
It contains all CLI related code.
Copyright (c) 2023 Shourjjo Majumder
https://github.com/shourdev/crex
*/
#include "lexer.c"
#include "include.h"
FILE *write;
char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL)
    {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }

    size_t result = fread(buffer, 1, file_size, file);
    if (result != file_size)
    {
        printf("Error reading the file.\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}

int main()

{

    FILE *FL;
    FL = fopen("main.crf", "r");

    char *file_content = read_file("main.crf");
Token* tokens;
int num_tokens = 0;
lexer(file_content,&tokens,&num_tokens);
for (int i=0;i<num_tokens;i++){
    switch (tokens[i].type)
    {
    case INT:
        printf("Token: INT LITERAL, Value: %s\n",tokens[i].value);
        
        break;
    case STRING:
        printf("Token: STRING LITERAL, Value: %s\n",tokens[i].value);
        break;
    case FLOAT:
        printf("Token: FLOAT_LITERAL, Value: %s\n",tokens[i].value);
        break;
    case PLUS_OP:
        printf("Token: PLUS_OPERATOR\n");
        break;
    case INT_KEY:
        printf("Token: INT_KEYWORD\n");
        break;
    case EQUAL:
        printf("Token: Equals\n");
        break;
    case IDENTFIER:
        printf("Token: Identifier, Value: %s\n",tokens[i].value);
        break;
    case STRING_KEY:
        printf("Token: STRING_KEYWORD\n");
        break;
    case MUL_OP:
        printf("Token: MULTIPLY_OPERATOR\n");
        break;
    case OPEN_PAREN:
        printf("Token: OPEN_PAREN\n");
        break;
    case CLOSE_PAREN:
        printf("Token: CLOSE_PAREN\n");
        break;
    case OVER_KEY:
        printf("Token: OVER_KEYWORD\n");
        break;
    case COMMA:
        printf("Token: Comma\n");
        break;
    case TOKEN_EOF:
        printf("Token: EOF \n");
        break;
    
    
   
    }
}
free(tokens);
}