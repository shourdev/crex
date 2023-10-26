/*
This contains function used to make the ast, and also to walk the ast
*/
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>
#include <stdbool.h>
AST *ast_new(AST ast)
{
  AST *ptr = malloc(sizeof(AST));
  if (ptr)
    *ptr = ast;
  return ptr;
}
void printtype(type type)
{
  printf("%s", type.type);
  if (type.islist == true)
  {
    printf("[]");
  }
}
void ast_print(AST *ptr)
{
  AST ast = *ptr;
  switch (ast.tag)
  {
  case AST_ROOT:
  {

    struct AST_ROOT data = ast.data.AST_ROOT;
    printf("{\n");
    for (size_t i = 0; i < data.len; i++)
    {

      ast_print(&data.code[i]);
    }
    printf("}\n");
    return;
  }
  case AST_BLOCK:
  {
    printf("{ \n");
    struct AST_BLOCK data = ast.data.AST_BLOCK;
    for (size_t i = 0; i < data.len; i++)
    {
      ast_print(&data.code[i]);
    }
    printf("}\n");
    return;
  }
  case AST_ARG:
  {

    struct AST_ARG data = ast.data.AST_ARG;
    for (size_t i = 0; i < data.len; i++)
    {
      ast_print(&data.args[i]);

      printf(",");
    }

    return;
  }
  case AST_NUM:
  {
    struct AST_NUM data = ast.data.AST_NUM;
    printf("%s", data.val);
    return;
  }

  case BinOpNode:
  {
    struct BinOpNode data = ast.data.BinOpNode;

    ast_print(data.left);

    printf("%s", data.op);
    ast_print(data.right);

    return;
  }
  case UnaryNode:
  {
    struct UnaryNode data = ast.data.UnaryNode;
    printf("%s", data.op);
    ast_print(data.node);
    return;
  }
  case StringNode:
  {
    struct StringNode data = ast.data.StringNode;
    printf("%s", data.value);
    return;
  }
  case PrintNode:
  {
    struct PrintNode data = ast.data.PrintNode;
    printf("print: ");
    ast_print(data.expr);
    return;
  }
  case VarDecl:
  {

    struct VarDecl data = ast.data.VarDecl;
    printtype(data.type);
    printf(" %s = ", data.name);
    ast_print(data.expr);

    return;
  }

  case VarAcess:
  {
    struct VarAcess data = ast.data.VarAcess;
    printf("%s", data.name);
    return;
  }
  case IF_STATEMENT:
  {
    struct IF_STATEMENT data = ast.data.IF_STATEMENT;
    printf("if ");
    ast_print(data.condition);
    printf("\n");

    ast_print(data.thenbranch);
    printf("\n");

    printf("else\n");
    ast_print(data.elsebranch);
    printf("\n");

    return;
  }
  case WHILE_LOOP:
  {
    struct WHILE_LOOP data = ast.data.WHILE_LOOP;
    printf("While ");
    ast_print(data.condition);
    printf("\n");
    printf("then\n");
    ast_print(data.thenbranch);
    printf("\n");
    printf("over\n");
    return;
  }

  case Call:
  {
    struct Call data = ast.data.Call;
    ast_print(data.Callee);
    printf("(");
    ast_print(data.arguments);
    printf(")");
    return;
  }
  case Function:
  {
    struct Function data = ast.data.Function;
    printtype(data.type);
    printf(" %s(", data.name);
    ast_print(data.args);
    printf(")");
    ast_print(data.code);

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
    ast_print(data.args);

    return;
  }
  case Listac:
  {
    struct Listac data = ast.data.Listac;

    ast_print(data.parent);
    printf("[");

    ast_print(data.index);
    printf("]");
    return;
  }
  case Assign:
  {
    struct Assign data = ast.data.Assign;
    ast_print(data.target);
    printf("=");
    ast_print(data.expr);
    return;
  }
  case Square:
  {
    struct Square data = ast.data.Square;
    printf("[");
    ast_print(data.arguments);
    printf("]");
    return;
  }
  case Return_Node:
  {
    struct Return_Node data = ast.data.Return_Node;
    printf("return ");
    ast_print(data.expression);
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
    ast_print(data.expression);
    return;
  }
  case NULL_NODE:
  {
    printf("null");
    return;
  }
  case STRUCT_ACC:
  {
    struct STRUCT_ACC data = ast.data.STRUCT_ACC;
    ast_print(data.left);
    printf(".");
    ast_print(data.right);
    return;
  }
  case EMPTY:
  {
    return;
  }
  }
}
