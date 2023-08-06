%{
#include <stdio.h>
%}

DIGIT       [0-9]
PLUS        "+"
MINUS       "-"
TIMES       "*"
DIVIDE      "/"
WHITESPACE  [ \t\n]

%%

{DIGIT}+    {
                printf("NUMBER: %.*s\n", yyleng, yytext);
            }
{PLUS}      {
                printf("PLUS\n");
            }
{MINUS}     {
                printf("MINUS\n");
            }
{TIMES}     {
                printf("TIMES\n");
            }
{DIVIDE}    {
                printf("DIVIDE\n");
            }
{WHITESPACE} /* Ignore whitespace */

%%
