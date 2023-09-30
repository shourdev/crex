#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED

#define AST_NEW(tag, ...) \
    ast_new((AST){tag, {.tag = (struct tag){__VA_ARGS__}}})
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
        AndNode,
        PrintNode,
        VarDecl,
        VarAssign,
        VarAcess,
        AST_BLOCK
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
        struct AndNode
        {
            AST *left;
            char *op;
            AST *right;

        } AndNode;
        struct PrintNode
        {
            AST *expr;
        } PrintNode;
        struct VarDecl
        {
            char *name;
            AST *expr;
        } VarDecl;
        struct VarAssign
        {
            char *name;
            AST *value;
        } VarAssign;
        struct VarAcess
        {
            char *name;
        } VarAcess;
    } data;
};
void ast_print(AST *ptr);
AST *ast_new(AST ast);

#endif