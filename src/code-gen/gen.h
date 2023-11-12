#ifndef GEN_H_INCLUDED
#define GEN_H_INCLUDED

#include "../lexer/lexer.h"
#include "../ast/ast.h"
void gencode(AST *ptr);
void caller(AST* ptr);
#endif