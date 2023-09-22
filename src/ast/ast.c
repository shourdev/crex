#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
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
  }
}
