#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
Token *tokens2;
Token curtoken;
int tokenindex = -1;
AST *root;

AST* and();
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
AST *num()
{
    if (curtoken.type == INT || curtoken.type == FLOAT)
    {

        AST *numnode = AST_NEW(AST_NUM, curtoken.value);
        getnexttoken();
        return numnode;
    }
    if (curtoken.type == STRING)
    {

        AST *stringnode = AST_NEW(StringNode, curtoken.value);
        getnexttoken();

        return stringnode;
    }
    if (curtoken.type == MINUS)
    {
        getnexttoken();
        AST *factor2 = factor();
        char *op = "-";
        AST *factor3 = AST_NEW(UnaryNode, op, factor2);

        return factor3;
    }
    if (curtoken.type == OPEN_PAREN)
    {
        getnexttoken();
        AST *expr2 = and();
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
    else
    {
        printf("Error: Invalid synax, expected literal or identifier after operator %d on line %d\n ", tokens2[tokenindex - 1].type, tokens2[tokenindex - 1].line);
        exit(1);
    }
}
AST *factor()
{
    AST *left = num();

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

        AST *right = num();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
AST* term(){
     AST *left = factor();

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
        AST *right = factor();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
AST *rel()
{
    AST *left = term();
    while (curtoken.type == GREATER || curtoken.type == SMALLER || curtoken.type == EQUALSTO)
    {
        char *op;
        if (curtoken.type == GREATER)
        {
            op = ">";
        }
        if (curtoken.type == SMALLER)
        {
            op = "<";
        }
        if (curtoken.type == EQUALSTO)
        {
            op = "==";
        }
        getnexttoken();
        AST *right = term();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
AST * and ()
{
    AST *left = rel();
    while (curtoken.type == AND)
    {
        char *op = "&&";
        getnexttoken();
        AST *right = rel();
        left = AST_NEW(BinOpNode, left, op, right);
       
    }
    return left;
}


void parsestatement()
{
    if (curtoken.type == INT || curtoken.type == FLOAT || curtoken.type == OPEN_PAREN || curtoken.type == MINUS || curtoken.type == STRING)
    {
        AST *tree = and();
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