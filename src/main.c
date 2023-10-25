/*
Copyright (c) 2023 Shourjjo Majumder
https://github.com/shourdev/crex

This is the main file of the crex compiler.
This is the driver file.
This calls the function to tokenize,parse,semantically analyse and generate code.
*/
#include "./lexer/lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./parser/parser.h"
#include "./ast/ast.h"
#include "./code-gen/gen.h"
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

    int num_tokens = 0;
    Token *tokens = lexer(file_content, &num_tokens);

    AST *tree = parse(tokens);
    caller(tree);
    free(tokens);
}
