/*
This is the ast data structre
*/
#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <stdbool.h>
#define AST_NEW(tag, ...) \
    ast_new((AST){tag, {.tag = (struct tag){__VA_ARGS__}}})

struct type
{
    bool islist;
    bool isstruct;
    char *type;
};

typedef struct type type;
typedef struct AST AST;
struct AST
{
    enum
    {
        AST_NUM,

        AST_ADD,
        AST_MUL,
        AST_DIV,
        AST_GREATER,
        AST_ROOT,
        BinOpNode,
        EMPTY,
        UnaryNode,
        StringNode,
        PrintNode,
        VarDecl,
        VarAcess,
        AST_BLOCK,
        IF_STATEMENT,
        WHILE_LOOP,
        Call,
        AST_ARG,
        Function,
        FunctionARG,
        BOOL,
        AST_FLOAT,
        Listac,
        Assign,
        listelements,
        Square,
        Return_Node,
        Break_Node,
        ExprStatement,
        NULL_NODE,
        STRUCT_ACC,
        AST_STRUCT

    } tag;
    union
    {
        struct AST_NUM
        {
            char *val;
        } AST_NUM;

        struct AST_ADD
        {
            AST *left;
            AST *right;
        } AST_ADD;
        struct AST_MUL
        {
            AST *left;
            AST *right;
        } AST_MUL;
        struct AST_DIV
        {
            AST *left;
            AST *right;
        } AST_DIV;
        struct AST_GREATER
        {
            AST *left;
            AST *right;
        } AST_GREATER;
        struct AST_ROOT
        {
            AST *code;
            size_t len;
        } AST_ROOT;
        struct AST_BLOCK
        {
            AST *code;
            size_t len;
        } AST_BLOCK;
        struct AST_ARG
        {
            AST *args;
            size_t len;
        } AST_ARG;
        struct EMPTY
        {
            char t;
        } EMPTY;
        struct BinOpNode
        {
            AST *left;
            char *op;
            AST *right;
        } BinOpNode;
        struct UnaryNode
        {
            char *op;
            AST *node;
        } UnaryNode;
        struct StringNode
        {
            char *value;
        } StringNode;

        struct PrintNode
        {
            AST *expr;
        } PrintNode;
        struct VarDecl
        {
            char *name;
            AST *expr;
        } VarDecl;

        struct VarAcess
        {
            char *name;
        } VarAcess;
        struct IF_STATEMENT
        {
            AST *condition;
            AST *thenbranch;
            AST *elsebranch;
        } IF_STATEMENT;
        struct WHILE_LOOP
        {
            AST *condition;
            AST *thenbranch;
        } WHILE_LOOP;
        struct Call
        {
            AST *Callee;
            AST *arguments;
        } Call;
        struct Listac
        {
            AST *parent;
            AST *index;
        } Listac;
        struct Function
        {
            char *name;
            AST *args;
            AST *code;
        } Function;
        struct FunctionARG
        {
            char *name;

        } FunctionARG;
        struct BOOL
        {
            char *value;
        } BOOL;
        struct AST_FLOAT
        {
            char *value;
        } AST_FLOAT;

        struct Assign
        {
            AST *target;
            AST *expr;
        } Assign;
        struct Square
        {
            AST *arguments;
        } Square;
        struct Return_Node
        {
            AST *expression;
        } Return_Node;
        struct Break_Node
        {

        } Break_Node;
        struct ExprStatement
        {
            AST *expression;
        } ExprStatement;
        struct NULL_NODE
        {

        } NULL_NODE;
        struct STRUCT_ACC
        {
            AST *left;
            AST *right;
        } STRUCT_ACC;
        struct AST_STRUCT
        {
            char *name;
            AST *contents;
        } AST_STRUCT;

    } data;
};
void ast_print(AST *ptr);
AST *ast_new(AST ast);
void printtype(type type);
#endif