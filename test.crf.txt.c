#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
  const char* testval =  "hello"; 
  size_t testsz = strlen(testval); 
 char* test = (char*) malloc((testsz + 1) * sizeof(char)); 
     strcpy(test,testval); 
  const char* tset2val =  "world"; 
  size_t tset2sz = strlen(tset2val); 
 char* tset2 = (char*) malloc((tset2sz + 1) * sizeof(char)); 
     strcpy(tset2,tset2val); 
  const char* test3val =  "l"; 
  size_t test3sz = strlen(test3val); 
 char* test3 = (char*) malloc((test3sz + 1) * sizeof(char)); 
     strcpy(test3,test3val); 
printf("%s %s %s", test,tset2,test3);

}
