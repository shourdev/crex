#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
void main() {
char* test2type = "str"; 
  const char* test2val = "3"; 
  size_t test2sz = strlen(test2val); 
 char* test2 = (char*) malloc((test2sz + 1) * sizeof(char)); 
     strcpy(test2,test2val); 
char* test2isconst = "false"; 
if (strcmp( test2type,"int")==0) { 
 test2type = "int";
} 
if (strcmp( test2type,"float")==0) { 
 test2type = "int";
} 
if (strcmp( test2type,"str")==0) { 
} 
printf("%s",test2);

}
