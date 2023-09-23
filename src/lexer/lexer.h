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
  AND
};
typedef struct
{
  enum tokentype type;
  char *value;
  int line;

} Token;
Token *lexer(char *string, int *num_tokens);
#endif
