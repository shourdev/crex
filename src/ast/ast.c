#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>
AST *ast_new(AST ast)
{
  AST *ptr = malloc(sizeof(AST));
  if (ptr)
    *ptr = ast;
  return ptr;
}
void ast_print(AST *ptr)
{
  AST ast = *ptr;
  switch (ast.tag)
  {
  case AST_ROOT:
  {
    printf("On Root: \n");
    struct AST_ROOT data = ast.data.AST_ROOT;
    for (size_t i = 0; i < data.len; i++)
    {
      ast_print(&data.code[i]);
    }

    return;
  }
  case AST_BLOCK:
  {
    printf("On Block: \n");
    struct AST_BLOCK data = ast.data.AST_BLOCK;
    for (size_t i = 0; i < data.len; i++)
    {
      ast_print(&data.code[i]);
    }

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

    printf("(");

    ast_print(data.left);

    printf("%s", data.op);
    ast_print(data.right);
    printf(")");

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
  case AndNode:
  {
    struct AndNode data = ast.data.AndNode;
    ast_print(data.left);
    printf("%s", data.op);
    ast_print(data.right);
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
    printf("%s %s = ", data.type, data.name);
    ast_print(data.expr);
    return;
  }
  case VarAssign:
  {
    struct VarAssign data = ast.data.VarAssign;
    printf("%s", data.name);
    printf("=");
    ast_print(data.value);
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
    printf("then\n");
    ast_print(data.thenbranch);
    printf("\n");
    printf("over\n");
    printf("else\n");
    ast_print(data.elsebranch);
    printf("\n");
    printf("over\n");
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

    case Call:{
      struct Call data = ast.data.Call;
      ast_print(data.Callee);
      printf("(");
      ast_print(data.arguments);
      printf(")");
      return;
    }
  case EMPTY:
  {
    return;
  }
  }
}
