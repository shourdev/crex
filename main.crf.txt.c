#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void main() {
char* dtype = "str"; 
  const char* dval = "hello"; 
  size_t dsz = strlen(dval); 
 char* d = (char*) malloc((dsz + 1) * sizeof(char)); 
     strcpy(d,dval); 
char* disconst = "true"; 
printf("%s",d);

}
