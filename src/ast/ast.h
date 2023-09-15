#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED

#define AST_NEW(tag, ...) \
  ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})
typedef struct AST AST;
struct AST
{
    enum
    {
        AST_NUMBER,
        AST_ADD,
        AST_MUL,
    } tag;
    union
    {
        struct AST_NUMBER
        {
            int number;
        } AST_NUMBER;
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
    } data;
};
void ast_print(AST *ptr);
AST *ast_new(AST ast);

#endif