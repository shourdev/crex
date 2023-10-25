#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "gen.h"
FILE *code;
bool isempty(AST *ptr)
{
    AST ast = *ptr;
    switch (ast.tag)
    {
    case EMPTY:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}
void caller(AST *ptr)
{
    code = fopen("code.js", "w");
    gencode(ptr);
}
void gencode(AST *ptr)
{
    AST ast = *ptr;
    switch (ast.tag)
    {
    case AST_ROOT:
    {
        struct AST_ROOT data = ast.data.AST_ROOT;
        for (size_t i = 0; i < data.len; i++)
        {

            gencode(&data.code[i]);
        }
        return;
    }
    case AST_BLOCK:
    {
        fprintf(code, "{ \n");
        struct AST_BLOCK data = ast.data.AST_BLOCK;
        for (size_t i = 0; i < data.len; i++)
        {
            gencode(&data.code[i]);
        }
        fprintf(code, "}\n");
        return;
    }
    case AST_ARG:
    {

        struct AST_ARG data = ast.data.AST_ARG;

        for (size_t i = 0; i < data.len; i++)
        {
            gencode(&data.args[i]);
            if (data.len - i == 1)
            {
                break;
            }
            fprintf(code, ",");
        }

        return;
    }
    case AST_NUM:
    {
        struct AST_NUM data = ast.data.AST_NUM;
        fprintf(code, "%s", data.val);
        return;
    }

    case BinOpNode:
    {
        struct BinOpNode data = ast.data.BinOpNode;

        gencode(data.left);

        fprintf(code, "%s", data.op);
        gencode(data.right);

        return;
    }
    case UnaryNode:
    {
        struct UnaryNode data = ast.data.UnaryNode;
        fprintf(code, "%s", data.op);
        gencode(data.node);
        return;
    }
    case StringNode:
    {
        struct StringNode data = ast.data.StringNode;
        fprintf(code, "%s", data.value);
        return;
    }

    case PrintNode:
    {
        struct PrintNode data = ast.data.PrintNode;
        fprintf(code, "console.log(");
        gencode(data.expr);
        fprintf(code, ");");
        return;
    }
    case VarDecl:
    {

        struct VarDecl data = ast.data.VarDecl;
        printtype(data.type);
        fprintf(code, "var %s = ", data.name);
        gencode(data.expr);
        fprintf(code, ";\n");
        return;
    }

    case VarAcess:
    {
        struct VarAcess data = ast.data.VarAcess;
        fprintf(code, "%s", data.name);
        return;
    }
    case IF_STATEMENT:
    {
        struct IF_STATEMENT data = ast.data.IF_STATEMENT;
        fprintf(code, "if (");
        gencode(data.condition);
        fprintf(code, ")\n");

        gencode(data.thenbranch);

        if (isempty(data.elsebranch))
        {
            return;
        }
        fprintf(code, "else");
        gencode(data.elsebranch);

        return;
    }
    case WHILE_LOOP:
    {
        struct WHILE_LOOP data = ast.data.WHILE_LOOP;
        printf("while(");
        gencode(data.condition);
        printf(")");
        gencode(data.thenbranch);

        return;
    }

    case Call:
    {
        struct Call data = ast.data.Call;
        gencode(data.Callee);
        printf("(");
        gencode(data.arguments);
        printf(")");
        return;
    }
    case Function:
    {
        struct Function data = ast.data.Function;
      //  printtype(data.type);
        printf(" function %s(", data.name);
        gencode(data.args);
        printf(")");
        gencode(data.code);

        return;
    }
    case FunctionARG:
    {
        struct FunctionARG data = ast.data.FunctionARG;
        printf("%s %s", data.type, data.name);
        return;
    }
    case BOOL:
    {
        struct BOOL data = ast.data.BOOL;
        printf("%s", data.value);
        return;
    }
    case AST_FLOAT:
    {
        struct AST_FLOAT data = ast.data.AST_FLOAT;
        printf("%s", data.value);
        return;
    }
    case AST_LIST:
    {
        struct AST_LIST data = ast.data.AST_LIST;
        printtype(data.type);

        printf("%s", data.name);
        printf("=");
        gencode(data.args);

        return;
    }
    case Listac:
    {
        struct Listac data = ast.data.Listac;

        gencode(data.parent);
        printf("[");

        gencode(data.index);
        printf("]");
        return;
    }
    case Assign:
    {
        struct Assign data = ast.data.Assign;
        gencode(data.target);
        printf("=");
        gencode(data.expr);
        return;
    }
    case Square:
    {
        struct Square data = ast.data.Square;
        printf("[");
        gencode(data.arguments);
        printf("]");
        return;
    }
    case Return_Node:
    {
        struct Return_Node data = ast.data.Return_Node;
        printf("return ");
        gencode(data.expression);
        return;
    }
    case Break_Node:
    {
        printf("break");
        return;
    }
    case ExprStatement:
    {
        struct ExprStatement data = ast.data.ExprStatement;
        gencode(data.expression);
    }
    case EMPTY:
    {
        return;
    }
    }
}