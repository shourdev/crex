#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
  const char* testval =  "Shourjjo"; 
  size_t testsz = strlen(testval); 
 char* test = (char*) malloc((testsz + 1) * sizeof(char)); 
     strcpy(test,testval); 
printf("ff %s \n ",test);

}
