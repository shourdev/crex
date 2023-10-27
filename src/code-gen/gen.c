#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "gen.h"
FILE *code;
bool isfuncarg = false;
bool curgenforblock = false;

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
    code = fopen("code.py", "w");
    gencode(ptr);
    fclose(code);
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

        struct AST_BLOCK data = ast.data.AST_BLOCK;
        for (size_t i = 0; i < data.len; i++)
        {

            fprintf(code, "   ");

            gencode(&data.code[i]);
        }

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
        fprintf(code, "\"%s\"", data.value);
        return;
    }

    case PrintNode:
    {
        struct PrintNode data = ast.data.PrintNode;
        fprintf(code, "print( ");
        gencode(data.expr);
        fprintf(code, ")\n");
        return;
    }
    case VarDecl:
    {

        struct VarDecl data = ast.data.VarDecl;
        // printtype(data.type);
        fprintf(code, "%s", data.name);
        if (isempty(data.expr))
        { 
            if (isfuncarg == true)
            { 
                return;
            }
            else
            {
                fprintf(code, "= None\n");
               
                return;
            }
        }
        else
        { 
            fprintf(code, "=");
            gencode(data.expr);
            fprintf(code, "\n");
            return;
        }
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
        fprintf(code, "):\n");

        gencode(data.thenbranch);

        if (isempty(data.elsebranch))
        {
            return;
        }
        fprintf(code, "else:");
        gencode(data.elsebranch);

        return;
    }
    case WHILE_LOOP:
    {
        struct WHILE_LOOP data = ast.data.WHILE_LOOP;
        fprintf(code, "while(");
        gencode(data.condition);
        fprintf(code, "):\n");
        gencode(data.thenbranch);

        return;
    }

    case Call:
    {
        struct Call data = ast.data.Call;
        gencode(data.Callee);
        fprintf(code, "(");
        gencode(data.arguments);
        fprintf(code, ")");
        return;
    }
    case Function:
    {
        struct Function data = ast.data.Function;
        //  printtype(data.type);
        isfuncarg = true;
        fprintf(code, "def %s(", data.name);
        gencode(data.args);
        fprintf(code, "):\n");
        gencode(data.code);

        return;
    }

    case BOOL:
    {
        struct BOOL data = ast.data.BOOL;
        if (strcmp(data.value, "true") == 0)
        {
            fprintf(code, "True");
        }
        else
        {
            fprintf(code, "False");
        }
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

        fprintf(code, "%s", data.name);
        fprintf(code, "=");

        gencode(data.args);
        fprintf(code, "\n");

        return;
    }
    case Listac:
    {
        struct Listac data = ast.data.Listac;

        gencode(data.parent);
        fprintf(code, "[");

        gencode(data.index);
        fprintf(code, "]");
        return;
    }
    case Assign:
    {
        struct Assign data = ast.data.Assign;
        gencode(data.target);
        fprintf(code, "=");
        gencode(data.expr);
        return;
    }
    case Square:
    {
        struct Square data = ast.data.Square;
        fprintf(code, "[");
        gencode(data.arguments);
        fprintf(code, "]");
        return;
    }
    case Return_Node:
    {
        struct Return_Node data = ast.data.Return_Node;
        fprintf(code, "return ");
        gencode(data.expression);
        fprintf(code, "\n");
        return;
    }
    case Break_Node:
    {
        fprintf(code, "break\n");
        return;
    }
    case ExprStatement:
    {
        struct ExprStatement data = ast.data.ExprStatement;
        gencode(data.expression);
        fprintf(code,"\n");
        return;
    }
    case STRUCT_ACC:
    {
        struct STRUCT_ACC data = ast.data.STRUCT_ACC;
        gencode(data.left);
        fprintf(code, ".");
        gencode(data.right);
        return;
    }
    case EMPTY:
    {
        return;
    }
    }
}