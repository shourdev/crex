
#include <stdio.h>
#include "parser.h"
int tokenindex = -1;
Token current;
Token *full;
void getnexttoken(){
    tokenindex++;
    current = full[tokenindex];
}
void parse(Token *token){
full = token;
getnexttoken();
printf("%d",current.type);

}