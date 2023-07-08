#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
printf( "Hello World");
  const char* testval =  "f"; 
  size_t testsz = strlen(testval); 
 char* test = (char*) malloc((testsz + 1) * sizeof(char)); 
     strcpy(test,testval); 
  const char* hival =  "helo"; 
  size_t hisz = strlen(hival); 
 char* hi = (char*) malloc((hisz + 1) * sizeof(char)); 
     strcpy(hi,hival); 
printf("%s",  test);
printf("%s",  hi);

}
void mai222n() {
printf( "Hello World");

}
