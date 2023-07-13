#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
  const char* testval =  "Shourjjo"; 
  size_t testsz = strlen(testval); 
 char* test = (char*) malloc((testsz + 1) * sizeof(char)); 
     strcpy(test,testval); 
  const char* test2val =  "Majumder"; 
  size_t test2sz = strlen(test2val); 
 char* test2 = (char*) malloc((test2sz + 1) * sizeof(char)); 
     strcpy(test2,test2val); 
printf("Welcome, %s %s \n",test,test2);

}
