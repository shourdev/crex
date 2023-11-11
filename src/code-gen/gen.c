#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "gen.h"
FILE *stdlib;
FILE *code;
bool isfuncarg = false;
int blockindent = 0;
bool iscout = false;
bool iscin = false;
bool isaddlist = false;
bool isclear = false;
bool issystem = false;
bool isclose = false;
void start()
{
    stdlib = fopen("stdlib.py", "w");
}
void gencout()
{
    if (iscout == false)
    {
        fprintf(stdlib, "def cout(*args):\n");
        fprintf(stdlib, "    for arg in args:\n");
        fprintf(stdlib, "        print(arg,end='')\n");
    }
    else
    {
        return;
    }

    iscout = true;
}
void gencin()
{
    if (iscin == false)
    {
        fprintf(stdlib, "def cin():\n");
        fprintf(stdlib, "    return input()\n");
    }
    else
    {
        return;
    }
    iscin = true;
}
void genaddlist()
{
    if (isaddlist == false)
    {
        fprintf(stdlib, "def addlist(list,pos,element):\n");
        fprintf(stdlib, "    list.insert(pos,element)\n");
    }
    else
    {
        return;
    }
    isaddlist = true;
}
void gensystemcode()
{
    if (issystem == false)
    {
        fprintf(stdlib, "import os\n");
    }
    else
    {
        return;
    }
    issystem = true;
}
void genclosecode()
{
    if (isclose == false)
    {
        fprintf(stdlib, "def close(f):\n");
        fprintf(stdlib, "    f.close()\n");
    }
    else
    {
        return;
    }
    isclose = true;
}
void spaceprint()
{
    for (int i = 0; i <= blockindent; i++)
    {
        fprintf(code, " ");
    }
}
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
    start();
    fprintf(code, "from stdlib import*\n");
    gencode(ptr);

    fclose(code);
    fclose(stdlib);
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
        blockindent = blockindent + 3;
        for (size_t i = 0; i < data.len; i++)
        {

            spaceprint();

            gencode(&data.code[i]);
        }
        blockindent = blockindent - 3;
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
        if (strcmp(data.op, "||") == 0)
        {
            fprintf(code, " or ");
            gencode(data.right);
            return;
        }
        if (strcmp(data.op, "&&") == 0)
        {
            fprintf(code, " and ");
            gencode(data.right);
            return;
        }
        
        else
        {
            fprintf(code, "%s", data.op);
            gencode(data.right);
            return;
        }
    }
    case UnaryNode:
    {
        struct UnaryNode data = ast.data.UnaryNode;
        if (strcmp(data.op, "!") == 0)
        {
            fprintf(code, " not ");
            gencode(data.node);

            return;
        }
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
    case NULL_NODE:
    {
        fprintf(code,"None");
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

        fprintf(code, "%s", data.name);
        if (isempty(data.expr))
        {
            if (isfuncarg == true)
            {
                return;
            }
            else
            {
                fprintf(code, " =");
                fprintf(code, " None\n");
                return;
            }
        }
        fprintf(code, " =");

        gencode(data.expr);
        fprintf(code, "\n");
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
        fprintf(code, "):\n");

        gencode(data.thenbranch);

        if (isempty(data.elsebranch))
        {
            return;
        }
        spaceprint();
        fprintf(code, "else:\n");
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
        // Std Lib functions
        // I/O
        if (strcmp(data.Callee->data.VarAcess.name, "cout") == 0)
        {
            gencout();
            fprintf(code, "cout(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "cin") == 0)
        {
            gencin();
            fprintf(code, "cin(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "toint") == 0)
        {

            fprintf(code, "int(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "tostr") == 0)
        {

            fprintf(code, "str(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "tofloat") == 0)
        {

            fprintf(code, "float(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "addlist") == 0)
        {
            genaddlist();
            fprintf(code, "addlist(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "len") == 0)
        {
            fprintf(code, "len(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "system") == 0)
        {
            gensystemcode();
            fprintf(code, "os.system(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }
        if (strcmp(data.Callee->data.VarAcess.name, "close") == 0)
        {
            genclosecode();
            fprintf(code, "close(");
            gencode(data.arguments);
            fprintf(code, ")");
            return;
        }

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
        isfuncarg = false;
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
        fprintf(code,"%s", data.value);
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
        fprintf(code, "\n");
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
    case AST_STRUCT:
    {
        struct AST_STRUCT data = ast.data.AST_STRUCT;
        fprintf(code, "class %s:\n", data.name);
        gencode(data.contents);
        return;
    }
    case EMPTY:
    {
        return;
    }
    }
}