// Generated by the crex compiler. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
int isStringOrInt(const char* input) { 
  int i, len; 
len = strlen(input);
   bool isInteger = true;
 for (i = 0; i < len; i++) {
   if (input[i] < '0' || input[i] > '9') {
 isInteger = false;
  break;
  }
  }
    if (isInteger){
   return 0;
  }
  else {
   return 1;
  }
  }
  int isDecimalOrString(const char* str) {
  char* endptr;
     strtod(str, &endptr);
         if (*endptr == '\0') {
    return 0;   
  }
  else{
    return 1;
  }
  }
void main() {
char* testtype = "str"; 
  const char* testval = "gg"; 
  size_t testsz = strlen(testval); 
 char* test = (char*) malloc((testsz + 1) * sizeof(char)); 
     strcpy(test,testval); 
char* testisconst = "false"; 
printf( "%test");

}
