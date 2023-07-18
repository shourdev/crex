#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
void main() {
char* testtype = "float"; 
  const char* testval = "3.3"; 
  size_t testsz = strlen(testval); 
 char* test = (char*) malloc((testsz + 1) * sizeof(char)); 
     strcpy(test,testval); 
char* testisconst = "false"; 
if (strcmp( testtype,"int")==0) { 
 testtype = "int";
} 
if (strcmp( testtype,"float")==0) { 
 testtype = "int";
} 
if (strcmp( testtype,"str")==0) { 
bool  test0is_integer = true; 
if (* test == '-' || * test == '+') {  
   test++; 
} 
for (; * test != '\0'; ) { 
  if (!isdigit(* test)) { 
   test0is_integer = false; 
 break; 
} 
 test++; 
} 
 if ( test0is_integer) { 
 testtype = "int";
} 
else{ 
printf(" test is not an integer \n "); 
} 
} 
if (strcmp( testtype,"int")==0) { 
 testtype = "int";
} 
if (strcmp( testtype,"float")==0) { 
 testtype = "int";
} 
if (strcmp( testtype,"str")==0) { 
bool  test1is_integer = true; 
if (* test == '-' || * test == '+') {  
   test++; 
} 
for (; * test != '\0'; ) { 
  if (!isdigit(* test)) { 
   test1is_integer = false; 
 break; 
} 
 test++; 
} 
 if ( test1is_integer) { 
 testtype = "int";
} 
else{ 
printf(" test is not an integer \n "); 
} 
} 
printf("%s",testtype);
}
