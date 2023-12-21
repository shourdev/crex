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
    int listdim;
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
        AST_STRUCT_INIT,
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
        AST_STRUCT,
        VAR_ARG,
        vardecnode,
        AST_THIS,
        STRING_KEY_NODE,
        VOID_KEY_NODE,
        BOOL_KEY_NODE,
        INT_KEY_NODE,
        FLOAT_KEY_NODE,
        COLON_NODE,
        asnode,
        infernode,
        returnarrow,
        paren

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
        struct paren{
            AST* stuff;
        }paren;
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
        struct COLON_NODE{
            AST* left;
            AST* right;
        }COLON_NODE;
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
        struct vardecnode
        {
            AST* expr;
        } vardecnode;
        struct BinOpNode
        {
            AST *left;
            char *op;
            AST *right;
        } BinOpNode;
        struct returnarrow{
            AST* left;
            AST* right;
        }returnarrow;
        struct UnaryNode
        {
            char *op;
            AST *node;
        } UnaryNode;
        struct asnode{
            AST* nod;
            AST* type;
        }asnode;
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
        struct infernode{
            AST* var;
            AST* expr;
        }infernode;
        struct VarAcess
        {
            char *name;
        } VarAcess;
        struct STRING_KEY_NODE{

        }STRING_KEY_NODE;
        struct INT_KEY_NODE{

        }INT_KEY_NODE;
        struct BOOL_KEY_NODE{

        }BOOL_KEY_NODE;
        struct FLOAT_KEY_NODE{

        }FLOAT_KEY_NODE;
        struct VOID_KEY_NODE{

        }VOID_KEY_NODE;
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
        struct VAR_ARG
        {
            char *name;
        } VAR_ARG;
        struct Function
        {
          AST* signature;
          AST* block;
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
            AST* sign;
            AST *contents;
        } AST_STRUCT;
        struct AST_THIS{

        }AST_THIS;
        struct AST_STRUCT_INIT{
            AST* structexpr;
            AST* init;
        }AST_STRUCT_INIT;

    } data;
};
void ast_print(AST *ptr);
AST *ast_new(AST ast);
void printtype(type type);
#endif