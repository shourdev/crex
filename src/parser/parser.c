#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
#include <stdbool.h>
// tokens2 is an array of tokens, and curtoken stores the current token in the tokens2 index
Token *tokens2;
Token curtoken;
int tokenindex = -1;
AST *root;
// All the functions for parsing expression
AST * or ();
AST * and ();
AST *term();
AST *factor();
AST *rel();
AST *primary();
AST *unary();
// Root is kinda like a main function, in my language you need no main function so the root holds ast for those
void ast_root_add(AST *root, AST *node)
{
    root->data.AST_ROOT.code = realloc(root->data.AST_ROOT.code, (root->data.AST_ROOT.len + 1) * sizeof(AST));
    root->data.AST_ROOT.code[root->data.AST_ROOT.len++] = *node;
}
Token peek()
{
    return tokens2[tokenindex];
}
Token previous()
{
    return tokens2[tokenindex - 1];
}
bool isatend()
{
    return peek().type == TOKEN_EOF;
}
Token getnexttoken()
{
    if (!isatend())
    {
        tokenindex++;
    }
    return previous();
}

bool check(enum tokentype type)
{
    if (isatend())
    {
        return false;
    }
    return peek().type == type;
}
bool match(enum tokentype type)
{
    if (check(type))
    {
        getnexttoken();
        return true;
    }
    return false;
}
void error(Token token, char *message)
{
    if (token.type == TOKEN_EOF)
    {
        printf("%d at end %s", token.line, message);
        exit(1);
    }
    else
    {
        printf("%d at %d %s", token.line, token.type, message);
        exit(1);
    }
}
Token consume(enum tokentype type, char *message)
{
    if (check(type))
    {
        return getnexttoken();
    }
    error(peek(), message);
}
bool instanceofvar(AST *expr)
{
    AST ast = *expr;
    if (ast.tag == VarAcess)
    {
        return true;
    }
    return false;
}
// Parses int,float, () etc
AST *primary()
{
    if (match(INT) || match(FLOAT))
    {

        AST *numnode = AST_NEW(AST_NUM, previous().value);
        return numnode;
    }
    if (match(STRING))
    {

        AST *stringnode = AST_NEW(StringNode, previous().value);

        return stringnode;
    }
    if (match(IDENTFIER))
    {
        AST *varnode = AST_NEW(VarAcess, previous().value);
        return varnode;
    }

    if (match(OPEN_PAREN))
    {

        AST *expr2 = and();

        consume(CLOSE_PAREN, "Expect ')' after expression.");

        return expr2;
    }
}
// Parses unary
AST *unary()
{
    if (match(MINUS) || match(BANG))
    {
        char *op;
        if (previous().type == MINUS)
        {
            op = "-";
        }
        if (previous().type == BANG)
        {
            op = "!";
        }

        AST *right = unary();
        AST *expr = AST_NEW(UnaryNode, op, right);
        return expr;
    }
    return primary();
}
// Parses multiplication and div
AST *factor()
{
    AST *left = unary();

    while (match(MUL_OP) || match(DIV))
    {
        char *op;
        if (previous().type == MUL_OP)
        {
            op = "*";
        }
        if (previous().type == DIV)
        {
            op = "/";
        }

        AST *right = unary();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
// Parses addition and subtraction
AST *term()
{
    AST *left = factor();

    AST *opnode;
    while (match(PLUS_OP) || match(MINUS))
    {
        char *op;
        if (previous().type == PLUS_OP)
        {
            op = "+";
        }
        if (previous().type == MINUS)
        {
            op = "-";
        }

        AST *right = factor();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
// Relation operators like < == etc
AST *rel()
{
    AST *left = term();
    while (match(GREATER) || match(SMALLER) || match(EQUALSTO))
    {
        char *op;
        if (previous().type == GREATER)
        {
            op = ">";
        }
        if (previous().type == SMALLER)
        {
            op = "<";
        }
        if (previous().type == EQUALSTO)
        {
            op = "==";
        }

        AST *right = term();

        left = AST_NEW(BinOpNode, left, op, right);
    }

    return left;
}
// &&
AST * and ()
{
    AST *left = rel();
    while (match(AND))
    {
        char *op = "&&";

        AST *right = rel();
        left = AST_NEW(BinOpNode, left, op, right);
    }
    return left;
}
// ||
AST * or ()
{
    AST *left = and();
    while (match(OR))
    {
        char *op = "||";

        AST *right = and();
        left = AST_NEW(BinOpNode, left, op, right);
    }
    return left;
}
AST *assignment()
{
    AST *expr = or ();
    if (match(EQUAL))
    {
        char *op = "=";
        AST *value = assignment();
        if (instanceofvar(expr))
        {
            AST exp = *expr;
            char *name = exp.data.VarAcess.name;
            return AST_NEW(VarAssign, name, value);
        }
        printf("Invalid assignment target.\n");
        exit(1);
    }
    return expr;
}
AST *expr()
{

    return assignment();
}
AST *exprstate()
{
    AST *exp = expr();

    consume(QUESTION, "Expected '?' after expression.");
    return exp;
}
AST *printstatement()
{
    AST *expr2 = expr();

    consume(QUESTION, "Expected '?' after value.");

    AST *node = AST_NEW(PrintNode, expr2);

    return node;
}

AST *statement()
{
    if (match(PRINT_KEY))
    {

        return printstatement();
    }

    return exprstate();
}
AST *varDeclare()
{
    char *name = peek().value;
    getnexttoken();
    AST *init;
    if (match(EQUAL))
    {
        init = expr();
    }
    consume(QUESTION, "Expect '?' after variable declaration");
    return AST_NEW(VarDecl, name, init);
}
AST *declaration()
{
    if (match(INT_KEY) || match(STRING_KEY) || match(FLOAT_KEY))
    {
        return varDeclare();
    }
    return statement();
}
void parsestatement()
{
    while (!isatend())
    {
        AST *tree = declaration();
        ast_root_add(root, tree);
    }
}
void parse(Token *tokens)
{
    tokens2 = tokens;
    getnexttoken();
    root = AST_NEW(AST_ROOT,
                   AST_NEW(EMPTY, 'f'), );
    AST *tree;

    parsestatement();
    ast_print(root);
}