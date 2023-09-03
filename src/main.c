#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool hasvarcode = false;
FILE *write;
typedef enum
{
    FUNC_KEYWORD,
    INT,
    STRING,
    FLOAT,
    PLUS_OP,
    TOKEN_EOF,
    INT_KEY,
    EQUAL,
    IDENTFIER,
    STRING_KEY,
    MUL_OP
} type;
typedef struct
{
    type type;
    char *value;
} Token;

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

void lexer(char *string, Token **tokens, int *num_tokens)
{
    int i = 0;
    int token_index = 0;
    int line = 1;
    int isiden = 0; /* this variable is
   Used for error handling, every time a token is matched this is evaluated to 1,
   and if none is matched it will be 0 giving an error.
   Also this is going to be changed to 0 every time the loop runs
    */
    *tokens = NULL;

    while (1)
    {

        isiden = 0;

        *tokens = realloc(*tokens, (token_index + 3) * sizeof(Token));
        // * Operator
        if (string[i] == '*')
        {
            (*tokens)[token_index].type = MUL_OP;
            (*tokens)[token_index].value = NULL;
            token_index += 1;
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
                (*tokens)[token_index].type = INT;
                (*tokens)[token_index].value = result;
                token_index++;
            }
            else
            {
                (*tokens)[token_index].type = FLOAT;
                (*tokens)[token_index].value = result;
                token_index++;
            }
        }
        // + Operator
        else if (string[i] == '+')
        {
            (*tokens)[token_index].type = PLUS_OP;
            (*tokens)[token_index].value = NULL;
            token_index += 1;
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
                (*tokens)[token_index].type = STRING;
                (*tokens)[token_index].value = result;
                token_index++;
                i++;
            }
            else
            {
                printf("Error: No closing quote for string on line %d\n", line);
            }
        }

        // Int Keyword
        if (string[i] == 'i' && string[i + 1] == 'n' && string[i + 2] == 't')
        {
            isiden = 1;
            int iseq = 0;
            (*tokens)[token_index].type = INT_KEY;
            (*tokens)[token_index].value = NULL;
            token_index++;

            i = i + 3;
            char *result = NULL;
            int resultLength = 0;
            while (isspace(string[i]))
            {

                i++;
            }
            while (1)
            {
                if (string[i] == '=')
                {
                    iseq = 1;
                    break;
                }
                resultLength++;
                result = realloc(result, resultLength * sizeof(char));
                result[resultLength - 1] = string[i];
                i++;
            }
            result = realloc(result, (resultLength + 1) * sizeof(char));
            result[resultLength] = '\0';
            (*tokens)[token_index].type = IDENTFIER;
            (*tokens)[token_index].value = result;
            token_index++;
            i++;
            // Equal
            if (iseq == 1)
            {

                (*tokens)[token_index].type = EQUAL;
                (*tokens)[token_index].value = NULL;
                token_index++;
            }
        }

        // String Keyword
        if (string[i] == 's' && string[i + 1] == 't' && string[i + 2] == 'r' && string[i + 3] == 'i' && string[i + 4] == 'n' && string[i + 5] == 'g')
        {
            int iseq = 0;
            isiden = 1;
            (*tokens)[token_index].type = STRING_KEY;
            (*tokens)[token_index].value = NULL;
            token_index++;
            char *result = NULL;
            int resultLength = 0;
            i += 6;
            while (isspace(string[i]))
            {
                i++;
            }
            while (1)
            {

                if (string[i] == '=')
                {
                    iseq = 1;
                    break;
                }
                resultLength++;
                result = realloc(result, resultLength * sizeof(char));
                result[resultLength - 1] = string[i];
                i++;
            }
            result = realloc(result, (resultLength + 1) * sizeof(char));
            result[resultLength] = '\0';
            (*tokens)[token_index].type = IDENTFIER;
            (*tokens)[token_index].value = result;
            token_index++;
            i++;
            // Equal
            if (iseq == 1)
            {

                (*tokens)[token_index].type = EQUAL;
                (*tokens)[token_index].value = NULL;
                token_index++;
            }
        }
        // Error Handling and spaces and lines and comments
        else
        {
            if (string[i] == '\n')
            {

                line++;
            }
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
                while (string[i] != '$')
                {

                    i++;
                }
                i++;
            }

            if (string[i] == '\0')
            {

                *tokens = realloc(*tokens, (token_index + 1) * sizeof(Token));
                (*tokens)[token_index].type = TOKEN_EOF;
                (*tokens)[token_index].value = NULL;
                *num_tokens = token_index + 1;
                return;
            }
            else
            {
                if (isiden == 0)
                {
                    printf("Error at line %d for %c\n", line, string[i]);
                    i++;
                }
            }
        }
    }
}

int main()
{

    FILE *FL;
    FL = fopen("main.crf", "r");

    char *file_content = read_file("main.crf");

    Token *tokens = NULL;
    int num_tokens = 0;

    lexer(file_content, &tokens, &num_tokens);
    for (int i = 0; i < num_tokens; i++)
    {
        switch (tokens[i].type)
        {
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
            printf("Token: STRING, Value: %s\n", tokens[i].value);
            break;
        case FLOAT:
            printf("Token: FLOAT, Value: %s\n", tokens[i].value);
            break;
        case INT_KEY:
            printf("Token: INT_kEY \n");
            break;
        case EQUAL:
            printf("Token: EQUAL \n");
            break;
        case IDENTFIER:
            printf("Token: IDENTIFIER, Value: %s \n", tokens[i].value);
            break;
        case STRING_KEY:
            printf("Token: STRING_KEY \n");
            break;
        case MUL_OP:
            printf("Token: MULTIPLY \n");
            break;
        }
    }
}
