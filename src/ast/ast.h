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
        AST_BLOCK,
        IF_STATEMENT,
        WHILE_LOOP,
        Call,
        AST_ARG,
        Function,
        FunctionARG,
        BOOL,
        AST_FLOAT,
        AST_LIST,
        Listac
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
            char *type;
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
        struct Listac{
            AST* name;
            AST* index;
        }Listac;
        struct Function
        {
            char *name;
            AST *args;
            AST *code;
            char *type;
        } Function;
        struct FunctionARG
        {
            char *name;
            char *type;
        } FunctionARG;
        struct BOOL
        {
            char *value;
        } BOOL;
        struct AST_FLOAT
        {
            char *value;
        } AST_FLOAT;
        struct AST_LIST
        {
            AST *args;

            char *type;
            char *name;
             }AST_LIST;
             
    } data;
};
void ast_print(AST *ptr);
AST *ast_new(AST ast);

#endif