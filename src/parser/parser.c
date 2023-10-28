/*
This is code for the crex parser. This is a recursive descent parser.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "../ast/ast.h"
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

AST *functionparse(char *name, type type);
AST* struct_decl();
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
    if (match(NULL_KEY))
    {
        AST *nullnode = AST_NEW(NULL_NODE);
        return nullnode;
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

        AST *expr2 = expr();

        consume(CLOSE_PAREN, "Expect ')' after expression.");

        return expr2;
    }
    if (match(LEFT_SQUARE))
    {
        AST *arguments = AST_NEW(AST_ARG,
                                 AST_NEW(EMPTY, 'f'), );
        if (!check(RIGHT_SQUARE))
        {
            do
            {
                ast_arg_add(arguments, expr());
            } while (match(COMMA));
        }
        consume(RIGHT_SQUARE, "Expected ']'");
        return AST_NEW(Square, arguments);
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
AST *dot()
{
    AST *left = list();
    while (true)
    {
        if (match(DOT))
        {
            AST *right = list();
            left = AST_NEW(STRUCT_ACC, left, right);
        }
        else
        {
            break;
        }
    }
    return left;
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
    return dot();
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
    while (match(GREATER) || match(SMALLER) || match(EQUALSTO) || match(NOTEQUAL))
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
        if (previous().type == NOTEQUAL)
        {
            op = "!=";
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

        AST *value = assignment();

        return AST_NEW(Assign, expr, value);
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

    return AST_NEW(ExprStatement, exp);
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
AST *returnstatement()
{
    if (peek().type == SEMI)
    {
        getnexttoken();
        AST *expr2 = AST_NEW(EMPTY, 2);
        return AST_NEW(Return_Node, expr2);
    }
    AST *expr2 = expr();
    consume(SEMI, "Expected ';' after expression");
    return AST_NEW(Return_Node, expr2);
}
AST *breakstatement()
{
    consume(SEMI, "Expected ';' after break statement");
    return AST_NEW(Break_Node);
}
AST *parsestruct(char* name)
{
    AST *root = AST_NEW(AST_BLOCK,
                        AST_NEW(EMPTY, 'f'), );
    while (!check(HASH) && !isatend())
    {
        if (match(INT_KEY) || match(STRING_KEY) || match(FLOAT_KEY) || match(BOOL_KEY) || match(VOID_KEY))
        {
            ast_block_add(root, varDeclare());
        }
        if (match(STRUCT_KEY))
        {
            ast_block_add(root, struct_decl());
        }
    }
    consume(HASH, "Expected '#' after block.");
    return AST_NEW(AST_STRUCT,name,root);
}
AST *struct_decl()
{
    type type;
    type.isstruct = true;
    type.islist = false;
    AST *expr2 = AST_NEW(EMPTY, 2);
    consume(IDENTFIER, "Expected identifier after struct keyword");
    type.type = previous().value;
    if (match(LEFT_SQUARE))
    {
        type.islist = true;
        consume(RIGHT_SQUARE, "Expected ']'");
        char *name;
        name = peek().value;
        getnexttoken();
        if (match(EQUAL))
        {
            expr2 = expr();
        }
        if (match(OPEN_PAREN))
        {
            return functionparse(name, type);
        }
        consume(SEMI, "expected ;");
        return AST_NEW(AST_LIST, expr2, type, name);
    }
    if (peek().type == IDENTFIER)
    {
        char *name = peek().value;
        getnexttoken();

        if (match(EQUAL))
        {

            expr2 = expr();
        }
        if (match(OPEN_PAREN))
        {
            return functionparse(name, type);
        }
        consume(SEMI, "Expect ';' after variable declaration");
        return AST_NEW(VarDecl, name, type, expr2);
    }
    else
    {
        return parsestruct(previous().value);
    }
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
    if (match(RETURN))
    {
        return returnstatement();
    }
    if (match(BREAK))
    {
        return breakstatement();
    }
    if (match(STRUCT_KEY))
    {
        return struct_decl();
    }
    return exprstate();
}
AST *functionargs()
{
    char *name;
    type type;
    type.islist = false;
    type.isstruct = false;
    if (match(STRING_KEY))
    {
        type.type = "string";
    }
    if (match(INT_KEY))
    {
        type.type = "int";
    }
    if (match(FLOAT_KEY))
    {
        type.type = "float";
    }
    if (match(BOOL_KEY))
    {
        type.type = "bool";
    }
    if (match(VOID_KEY))
    {
        type.type = "void";
    }
    if (match(STRUCT_KEY))
    {
        type.isstruct = true;
        consume(IDENTFIER, "Expected identifier after struct keyword");
        type.type = previous().value;
    }
    if (match(LEFT_SQUARE))
    {
        type.islist = true;
        consume(RIGHT_SQUARE, "Expected ']'");
        name = peek().value;
        getnexttoken();
        AST *arguments = AST_NEW(EMPTY, 2);
        return AST_NEW(AST_LIST, arguments, type, name);
    }
    name = peek().value;
    getnexttoken();
    AST *arguments = AST_NEW(EMPTY, 2);
    return AST_NEW(VarDecl, name, type, arguments);
}
AST *functionparse(char *name, type type)
{

    AST *parameters = AST_NEW(AST_ARG,
                              AST_NEW(EMPTY, 2), );

    if (!check(CLOSE_PAREN))
    {
        do
        {
            ast_arg_add(parameters, functionargs());
        } while (match(COMMA));
    }
    consume(CLOSE_PAREN, "Expected closing paren after function parameters");
    if (match(SEMI))
    {
        AST *body = AST_NEW(EMPTY, 3);
        return AST_NEW(Function, name, parameters, body, type);
    }
    AST *body = block();
    return AST_NEW(Function, name, parameters, body, type);
}

AST *varDeclare()
{
    type type;

    if (previous().type == INT_KEY)
    {
        type.type = "int";
    }
    if (previous().type == FLOAT_KEY)
    {
        type.type = "float";
    }
    if (previous().type == STRING_KEY)
    {
        type.type = "string";
    }
    if (previous().type == BOOL_KEY)
    {
        type.type = "bool";
    }
    if (previous().type == VOID_KEY)
    {
        type.type = "void";
    }
    type.islist = false;
    type.isstruct = false;
    // Lists
    if (peek().type == LEFT_SQUARE)
    { 
        type.islist = true;
        AST *arguments = AST_NEW(EMPTY,3);
        getnexttoken();
        consume(RIGHT_SQUARE, "Expected ']' after '['");
        char *name = peek().value;
        getnexttoken();
        if (match(EQUAL))
        {

            arguments = expr();
        }
        if (match(OPEN_PAREN))
        {
            return functionparse(name, type);
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
        return functionparse(name, type);
    }
    consume(SEMI, "Expect ';' after variable declaration");
    return AST_NEW(VarDecl, name, type, init);
}
AST *declaration()
{
    if (match(INT_KEY) || match(STRING_KEY) || match(FLOAT_KEY) || match(BOOL_KEY) || match(VOID_KEY))
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
AST *parse(Token *tokens)
{
    tokens2 = tokens;
    getnexttoken();
    root = AST_NEW(AST_ROOT,
                   AST_NEW(EMPTY, 'f'), );
    AST *tree;

    parsestatement();
    return root;
}