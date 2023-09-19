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
void ast_print(AST *ptr) {
  AST ast = *ptr;
  switch (ast.tag) {
    case AST_ROOT: {
      printf("On Root: \n");
       struct AST_ROOT data = ast.data.AST_ROOT;
      ast_print(data.code);
      return;
    }
    case AST_INT: {
      struct AST_INT data = ast.data.AST_INT;
      printf("%d", data.intval);
      return;
    }
    case AST_FLOAT:{
      struct AST_FLOAT data = ast.data.AST_FLOAT;
      printf("%f",data.floatval);
      return;
    }
    case AST_ADD: {
      struct AST_ADD data = ast.data.AST_ADD;
      printf("(");
      ast_print(data.left);
      printf(" + ");
      ast_print(data.right);
      printf(")");
      return;
    }
    case AST_MUL: {
      struct AST_MUL data = ast.data.AST_MUL;
      printf("(");
      ast_print(data.left);
      printf(" * ");
      ast_print(data.right);
      printf(")");
      return;
    }
    case AST_DIV: {
      struct AST_DIV data = ast.data.AST_DIV;
      printf("(");
      ast_print(data.left);
      printf(" / ");
      ast_print(data.right);
      printf(")");
      return;
    }
    case AST_GREATER: {
      struct AST_DIV data = ast.data.AST_DIV;
   
      ast_print(data.left);
      printf(" > ");
      ast_print(data.right);
    
      return;
    }
  }
}
