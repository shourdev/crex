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
AST *expr();
// All the functions for parsing statements
AST *block();
AST *declaration();
AST *varDeclare();
AST *statement();
AST *ifstatement();
AST *printstatement();
AST *exprstate();
AST *whilestatement();
bool isatend();
// Root is kinda like a main function, in my language you need no main function so the root holds ast for those
void ast_root_add(AST *root, AST *node)
{
    root->data.AST_ROOT.code = realloc(root->data.AST_ROOT.code, (root->data.AST_ROOT.len + 1) * sizeof(AST));
    root->data.AST_ROOT.code[root->data.AST_ROOT.len++] = *node;
}
// For blocks
void ast_block_add(AST *root, AST *node)
{
    root->data.AST_BLOCK.code = realloc(root->data.AST_BLOCK.code, (root->data.AST_BLOCK.len + 1) * sizeof(AST));
    root->data.AST_BLOCK.code[root->data.AST_BLOCK.len++] = *node;
}
// For args
void ast_arg_add(AST *root, AST *node)
{
    root->data.AST_ARG.args = realloc(root->data.AST_ARG.args, (root->data.AST_ARG.len + 1) * sizeof(AST));
    root->data.AST_ARG.args[root->data.AST_ARG.len++] = *node;
}
// Token related functions
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
bool instanceoflist(AST *expr)
{
    AST ast = *expr;
    if (ast.tag == Listac)
    {
        return true;
    }
    return false;
}

/*
This section parses all the expressions
*/

// Parses int,float, () etc
AST *primary()
{
    if (match(INT))
    {

        AST *numnode = AST_NEW(AST_NUM, previous().value);
        return numnode;
    }
    if (match(FLOAT))
    {

        AST *numnode = AST_NEW(AST_FLOAT, previous().value);
        return numnode;
    }
    if (match(TRUE_kEY) || match(FALSE_kEY))
    {
        char *val;
        if (previous().type == TRUE_kEY)
        {
            val = "true";
        }
        if (previous().type == FALSE_kEY)
        {
            val = "false";
        }
        AST *boolnode = AST_NEW(BOOL, val);
        return boolnode;
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
AST *finishcall(AST *callee)
{
    int arg = 0;
    AST *arguments = AST_NEW(AST_ARG,
                             AST_NEW(EMPTY, 'f'), );
    if (!check(CLOSE_PAREN))
    {
        do
        {
            if (arg > 250)
            {
                error(peek(), "Too many arguments");
            }
            ast_arg_add(arguments, expr());
            arg++;
        } while (match(COMMA));
    }
    consume(CLOSE_PAREN, "Expect ')' after arguments.");
    return AST_NEW(Call, callee, arguments);
}
AST *call()
{
    AST *expr2 = primary();
    while (true)
    {
        if (match(OPEN_PAREN))
        {
            expr2 = finishcall(expr2);
        }
        else
        {
            break;
        }
    }
    return expr2;
}
AST *list()
{
    AST *expr2 = call();
    while (true)
    {
        if (match(LEFT_SQUARE))
        {
            AST *index = expr();
            consume(RIGHT_SQUARE, "Expected ']' after index expression.");
            expr2 = AST_NEW(Listac, expr2, index);
        }
        else
        {
            break;
        }
    }
    return expr2;
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
    return list();
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
// =
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
        if (instanceoflist(expr))
        {
            return AST_NEW(ListAssign, expr, value);
        }
        printf("Error");
        exit(1);
    }
    return expr;
}
AST *expr()
{

    return assignment();
}
/*
This section parses all the statements
*/
AST *exprstate()
{
    AST *exp = expr();

    consume(SEMI, "Expected ';' after expression.");
    return exp;
}
AST *printstatement()
{
    AST *expr2 = expr();

    consume(SEMI, "Expected ';' after value.");

    AST *node = AST_NEW(PrintNode, expr2);

    return node;
}
AST *whilestatement()
{
    consume(OPEN_PAREN, "Expect '(' after 'while'");
    AST *condition = expr();
    consume(CLOSE_PAREN, "Expect ')' after condition");
    AST *body = block();
    return AST_NEW(WHILE_LOOP, condition, body);
}
AST *ifstatement()
{
    consume(OPEN_PAREN, "Expect '(' after 'if'");
    AST *condition = expr();
    consume(CLOSE_PAREN, "Expect ')' after condition");
    AST *then = block();
    AST *elsebranch = AST_NEW(EMPTY, 2);
    if (match(ELSE))
    {
        elsebranch = block();
    }
    return AST_NEW(IF_STATEMENT, condition, then, elsebranch);
}
AST *statement()
{
    if (match(PRINT_KEY))
    {

        return printstatement();
    }
    if (match(IF))
    {
        return ifstatement();
    }
    if (match(WHILE_KEY))
    {
        return whilestatement();
    }
    return exprstate();
}
AST *functionargs()
{
    char *type;
    if (match(STRING_KEY))
    {
        type = "string";
    }
    if (match(INT_KEY))
    {
        type = "int";
    }
    if (match(FLOAT_KEY))
    {
        type = "float";
    }
    if (match(BOOL_KEY))
    {
        type = "bool";
    }
    char *name = peek().value;
    getnexttoken();
    return AST_NEW(FunctionARG, name, type);
}
AST *functionparse(char *name, char *type3, bool islist)
{
    type type2;
    if (islist == true)
    {
        type2.islist = true;
    }
    else
    {
        type2.islist = false;
    }
    type2.isstruct = false;
    type2.type = type3;
    AST *parameters = AST_NEW(AST_ARG,
                              AST_NEW(EMPTY, 2), );

    if (!check(CLOSE_PAREN))
    {
        do
        {
            ast_arg_add(parameters, functionargs());
        } while (match(COMMA));
    }
    consume(CLOSE_PAREN, "Expected closing paren");
    if (match(SEMI))
    {
        AST *body = AST_NEW(EMPTY, 3);
        return AST_NEW(Function, name, parameters, body, type2);
    }
    AST *body = block();
    return AST_NEW(Function, name, parameters, body, type2);
}

AST *varDeclare()
{
    char *type;
    if (previous().type == INT_KEY)
    {
        type = "int";
    }
    if (previous().type == FLOAT_KEY)
    {
        type = "float";
    }
    if (previous().type == STRING_KEY)
    {
        type = "string";
    }
    if (previous().type == BOOL_KEY)
    {
        type = "bool";
    }
    // Lists
    if (peek().type == LEFT_SQUARE)
    {
        AST *arguments = AST_NEW(AST_ARG,
                                 AST_NEW(EMPTY, 'f'), );
        getnexttoken();
        consume(RIGHT_SQUARE, "Expected ']' after '['");
        char *name = peek().value;
        getnexttoken();
        if (match(EQUAL))
        {
            consume(LEFT_SQUARE, "Expected '[' after '='");

            if (!check(RIGHT_SQUARE))
            {
                do
                {

                    ast_arg_add(arguments, expr());

                } while (match(COMMA));
            }
            consume(RIGHT_SQUARE, "Expected ']' after expressions.");
        }
        if (match(OPEN_PAREN))
        {
            return functionparse(name, type, true);
        }
        consume(SEMI, "Expected ';'");
        return AST_NEW(AST_LIST, arguments, type, name);
    }
    char *name = peek().value;
    getnexttoken();
    AST *init = AST_NEW(EMPTY, 3);
    if (match(EQUAL))
    {
        init = expr();
    }
    // Functions
    if (match(OPEN_PAREN))
    {
        return functionparse(name, type, false);
    }
    consume(SEMI, "Expect ';' after variable declaration");
    return AST_NEW(VarDecl, name, type, init);
}
AST *declaration()
{
    if (match(INT_KEY) || match(STRING_KEY) || match(FLOAT_KEY) || match(BOOL_KEY))
    {
        return varDeclare();
    }
    return statement();
}
AST *block()
{
    AST *root = AST_NEW(AST_BLOCK,
                        AST_NEW(EMPTY, 'f'), );
    while (!check(HASH) && !isatend())
    {
        AST *code = declaration();
        ast_block_add(root, code);
    }
    consume(HASH, "Expected '#' after block.");
    return root;
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