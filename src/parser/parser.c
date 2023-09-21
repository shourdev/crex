#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
Token *tokens2;
Token curtoken;
int tokenindex = -1;
AST *root;
AST *expr();
AST *term();
AST *factor();
void ast_root_add(AST *root, AST *node)
{
    root->data.AST_ROOT.code = realloc(root->data.AST_ROOT.code, (root->data.AST_ROOT.len + 1) * sizeof(AST));
    root->data.AST_ROOT.code[root->data.AST_ROOT.len++] = *node;
}
void getnexttoken()
{
    tokenindex++;
    curtoken = tokens2[tokenindex];
}
AST *factor()
{
    if (curtoken.type == INT || curtoken.type == FLOAT)
    {

        AST *numnode = AST_NEW(AST_NUM, curtoken.value);
        getnexttoken();
        return numnode;
    }

    if (curtoken.type == OPEN_PAREN)
    {
        getnexttoken();
        AST *expr2 = expr();
        if (curtoken.type == CLOSE_PAREN)
        {
            getnexttoken();
            return expr2;
        }
        else
        {
            printf("Expected ) after expression ");
            ast_print(expr2);
            printf(" on line %d\n", curtoken.line);
            exit(1);
        }
    }
}
AST *term()
{
    AST *left = factor();

    while (curtoken.type == MUL_OP || curtoken.type == DIV)
    {
        char *op;
        if (curtoken.type == MUL_OP)
        {
            op = "*";
        }
        if (curtoken.type == DIV)
        {
            op = "/";
        }

        getnexttoken();

        AST *right = factor();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
AST *expr()
{
    AST *left = term();

    AST *opnode;
    while (curtoken.type == PLUS_OP || curtoken.type == MINUS)
    {
        char *op;
        if (curtoken.type == PLUS_OP)
        {
            op = "+";
        }
        if (curtoken.type == MINUS)
        {
            op = "-";
        }
        getnexttoken();
        AST *right = term();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
void parsestatement()
{
    if (curtoken.type == INT || curtoken.type == FLOAT || curtoken.type == OPEN_PAREN)
    {
        AST *tree = expr();
        ast_root_add(root, tree);
    }
}
void parse(Token *tokens)
{
    tokens2 = tokens;
    getnexttoken();
    root = AST_NEW(AST_ROOT,
                   AST_NEW(EMPTY, 'f'), );

    while (curtoken.type != TOKEN_EOF)
    {
        parsestatement();
    }

    ast_print(root);
}