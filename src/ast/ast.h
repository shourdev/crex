#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED

#define AST_NEW(tag, ...) \
    ast_new((AST){tag, {.tag = (struct tag){__VA_ARGS__}}})
typedef struct AST AST;
struct AST
{
    enum
    {
        AST_INT,
        AST_FLOAT,
        AST_ADD,
        AST_MUL,
        AST_DIV,
        AST_GREATER,
        AST_ROOT
    } tag;
    union
    {
        struct AST_INT
        {
            int intval;
        } AST_INT;
        struct AST_FLOAT
        {
            float floatval;
        } AST_FLOAT;

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
        } AST_ROOT;

    } data;
};
void ast_print(AST *ptr);
AST *ast_new(AST ast);

#endif