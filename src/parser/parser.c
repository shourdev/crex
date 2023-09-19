#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
Token *tokens2;
Token curtoken;
int tokenindex = -1;
void getnexttoken()
{
    tokenindex++;
    curtoken = tokens2[tokenindex];
}
void parseexpr()
{
    char *test = curtoken.value;

    int x;
    sscanf(test, "%d", &x);
    getnexttoken();
    if (curtoken.type == PLUS_OP)
    {
        getnexttoken();
        char *test2 = curtoken.value;
        int y;
        sscanf(test2, "%d", &y);
        AST *tree = AST_NEW(AST_ROOT,
                            AST_NEW(AST_ADD,
                                    AST_NEW(AST_INT, x),
                                    AST_NEW(AST_INT, y), ), );
        ast_print(tree);
    }
}
void parsestatement()
{
    if (curtoken.type == INT)
    {
        parseexpr();
    }
    else
    {
        printf("Error \n");
        exit(1);
    }
}
void parse(Token *tokens)
{
    tokens2 = tokens;
    getnexttoken();
    while (curtoken.type != TOKEN_EOF)
    {

        parsestatement();
    }
}