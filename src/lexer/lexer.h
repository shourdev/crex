/*
Mainly contains all the different types of tokens
*/
#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
enum tokentype
{

  INT,
  STRING,
  FLOAT,
  PLUS_OP,
  TOKEN_EOF,
  INT_KEY,
  EQUAL,
  IDENTFIER,
  STRING_KEY,
  MUL_OP,
  OPEN_PAREN,
  CLOSE_PAREN,
  OVER_KEY,
  COMMA,
  FLOAT_KEY,
  MINUS,
  DIV,
  NEWLINE,
  GREATER,
  SMALLER,
  EQUALSTO,
  AND,
  BANG,
  OR,
  PRINT_KEY,
  SEMI,
IF,
 CURLY_OPEN,
 CURLY_CLOSE,
 ELSE,
 WHILE_KEY,
 BOOL_KEY,
 TRUE_kEY,
 FALSE_kEY,
 LEFT_SQUARE,
 RIGHT_SQUARE,
 NOTEQUAL,
 RETURN,
 BREAK,
 VOID_KEY,
 NULL_KEY,
 DOT,
 STRUCT_KEY,
 DECLKEY,
 GREATER_EQUAL,
 SMALLER_EQUAL,
 FN_KEY
};
typedef struct
{
  enum tokentype type;
  char *value;
  int line;

} Token;
Token *lexer(char *string, int *num_tokens);
#endif
