/*
This file is just so that the parsing functions can be called from the main code.
*/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "../lexer/lexer.h"
#include "../ast/ast.h"
AST* parse(Token* tokens);
#endif