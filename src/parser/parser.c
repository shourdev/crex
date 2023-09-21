#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
Token *tokens2;
Token curtoken;
int tokenindex = -1;
AST *root;
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
void parse(Token *tokens)
{
    tokens2 = tokens;
    getnexttoken();
    AST *tree = expr();
    ast_print(tree);
}