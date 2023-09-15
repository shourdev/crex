/*
This is the code for the crex lexer.
*/
#include <stdio.h>
#include "./lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

Token *lexer(char *string, int *num_tokens)
{
    Token *tokens = NULL;
    int haserrored = 0;
    int i = 0;
    int token_index = 0;
    int line = 1;
    int isiden = 0; /* this variable is
   Used for error handling, every time a token is matched this is evaluated to 1,
   and if none is matched it will be 0 giving an error.
   Also this is going to be changed to 0 every time the loop runs
    */

    while (1)
    {

        isiden = 0;

        tokens = realloc(tokens, sizeof(Token) * (token_index + 3));
        // * Operator
        if (string[i] == '*')
        {
            tokens[token_index].type = MUL_OP;
            tokens[token_index].value = NULL;
            tokens[token_index].line = line;
            token_index++;
            i++;
            isiden = 1;
        }

        // Int and float
        else if (isdigit(string[i]))
        {
            isiden = 1;
            char *result = NULL;
            int resultLength = 0;
            int isdec = 0;

            while (string[i] != '\n')
            {
                if (string[i] == '.')
                {
                    while (!isdigit(string[i]))
                    {
                        resultLength++;
                        result = realloc(result, resultLength * sizeof(char));
                        result[resultLength - 1] = string[i];
                        i++;
                        isdec = 1;
                    }
                }
                if (!isdigit(string[i]))
                {

                    break;
                }

                resultLength++;
                result = realloc(result, resultLength * sizeof(char));
                result[resultLength - 1] = string[i];
                i++;
            }

            result = realloc(result, (resultLength + 1) * sizeof(char));
            result[resultLength] = '\0';

            if (isdec == 0)
            {
                tokens[token_index].type = INT;

                tokens[token_index].value = result;
                tokens[token_index].line = line;
                token_index++;
            }
            else
            {
                tokens[token_index].type = FLOAT;
                tokens[token_index].value = result;
                tokens[token_index].line = line;
                token_index++;
            }
            free(result);
        }
        // + Operator
        else if (string[i] == '+')
        {
            tokens[token_index].type = PLUS_OP;
            tokens[token_index].value = NULL;
            tokens[token_index].line = line;
            token_index++;
            i += 1;
            isiden = 1;
        }
        // Strings
        else if (string[i] == '"')
        {
            isiden = 1;
            i++;
            int stringstart = i;
            while (string[i] != '"' && string[i] != '\0')
            {

                i++;
            }
            if (string[i] == '"')
            {
                int strlength = i - stringstart;
                char *result = (char *)malloc(strlength + 1);
                strncpy(result, string + stringstart, strlength);
                result[strlength] = '\0';
                tokens[token_index].type = STRING;
                tokens[token_index].value = result;
                tokens[token_index].line = line;
                token_index++;
                i++;
                free(result);
            }
            else
            {
                printf("Lexical Error: Unterminated string at line %d\n", line);
                haserrored = 1;
            }
        }
        // Identifiers
        if (isalpha(string[i]))
        {
            int visited = 0;
            char *result = NULL;
            int resultLength = 0;
            while (isalnum(string[i]) || isalpha(string[i]) || string[i] == '_')
            {
                resultLength++;
                result = realloc(result, resultLength * sizeof(char));
                result[resultLength - 1] = string[i];
                i++;
            }
            result = realloc(result, (resultLength + 1) * sizeof(char));
            result[resultLength] = '\0';
            if (strcmp(result, "int") == 0)
            {
                isiden = 1;

                tokens[token_index].type = INT_KEY;
                tokens[token_index].value = NULL;
                tokens[token_index].line = line;
                token_index++;
                visited = 1;
            }
            if (strcmp(result, "string") == 0)
            {
                visited = 1;
                isiden = 1;
                tokens[token_index].type = STRING_KEY;
                tokens[token_index].value = NULL;
                tokens[token_index].line = line;
                token_index++;
            }
            if(strcmp(result,"float")==0){
                visited = 1;
                isiden = 1;
                tokens[token_index].type = FLOAT_KEY;
                tokens[token_index].value = NULL;
                tokens[token_index].line = line;
                token_index++;
            }
            if (strcmp(result, "over") == 0)
            {
                visited = 1;
                isiden = 1;
                tokens[token_index].type = OVER_KEY;
                tokens[token_index].value = NULL;
                tokens[token_index].line = line;
                token_index++;
            }
            else
            {
                if (visited == 0)
                {
                    isiden = 1;
                    tokens[token_index].type = IDENTFIER;
                    tokens[token_index].value = result;
                    tokens[token_index].line = line;
                    token_index++;
                }
            }
            free(result);
        }

        // Equal
        if (string[i] == '=')
        {
            isiden = 1;
            tokens[token_index].type = EQUAL;
            tokens[token_index].value = NULL;
            tokens[token_index].line = line;
            token_index++;
            i++;
        }
        // Opening paren
        if (string[i] == '(')
        {
            isiden = 1;
            tokens[token_index].type = OPEN_PAREN;
            tokens[token_index].value = NULL;
            tokens[token_index].line = line;
            token_index++;
            i++;
        }
        // Closing paren
        if (string[i] == ')')
        {
            isiden = 1;
            tokens[token_index].type = CLOSE_PAREN;
            tokens[token_index].value = NULL;
            tokens[token_index].line = line;
            token_index++;
            i++;
        }
        // Comma
        if (string[i] == ',')
        {
            isiden = 1;
            tokens[token_index].type = COMMA;
            tokens[token_index].value = NULL;
            tokens[token_index].line = line;
            token_index++;
            i++;
        }
        // Error Handling and spaces and lines and comments
        else
        { // Lines
            if (string[i] == '\n')
            {

                line++;
            }
            // Space
            if (isspace(string[i]))
            {

                i++;
                continue;
            }
            // Comments
            if (string[i] == '$')
            {
                i++;
                isiden = 1;
                while (1)
                {
                    if (string[i] == '$')
                    {
                        break;
                    }
                    if (string[i] == '\0')
                    {
                        printf("Lexical Error: Line %d unterminated comment\n", line);
                        haserrored = 1;
                    }
                    i++;
                }
                i++;
            }
            // EOF
            if (string[i] == '\0')
            {

                tokens[token_index].type = TOKEN_EOF;
                tokens[token_index].value = NULL;
                tokens[token_index].line = line;

                break;
            }
            // Error
            else
            {
                if (isiden == 0)
                {
                    printf("Lexical Error: line %d for %c\n", line, string[i]);
                    haserrored = 1;
                    i++;
                }
            }
        }
    }
    if (haserrored == 1)
    {
        exit(1);
    }
    else
    {
        *num_tokens = token_index + 1;
        return tokens;
    }
}