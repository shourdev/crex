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
    case AST_NUMBER: {
      struct AST_NUMBER data = ast.data.AST_NUMBER;
      printf("%d", data.number);
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
int main(){
AST *term = 
 AST_NEW(AST_GREATER,
AST_NEW(AST_ADD,
AST_NEW(AST_NUMBER,4),
AST_NEW(AST_NUMBER,5),

),
AST_NEW(AST_NUMBER,8),
 );

     ast_print(term);
}
