#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void main() {
char* dtype = "str"; 
  const char* dval = "f"; 
  size_t dsz = strlen(dval); 
 char* d = (char*) malloc((dsz + 1) * sizeof(char)); 
     strcpy(d,dval); 
char* disconst = "false"; 
printf("%s",d);

}
