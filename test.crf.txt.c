#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
  const char* nameval =  ""; 
  size_t namesz = strlen(nameval); 
 char* name = (char*) malloc((namesz + 1) * sizeof(char)); 
     strcpy(name,nameval); 
  const char* ageval =  ""; 
  size_t agesz = strlen(ageval); 
 char* age = (char*) malloc((agesz + 1) * sizeof(char)); 
     strcpy(age,ageval); 
printf( "Enter your name: ");
char*  namenewString = NULL;
size_t  namebufferSize = 0;
size_t  namecharsRead = getline(& namenewString, & namebufferSize, stdin);
if ( namenewString[ namecharsRead - 1] == '\n') {
     namenewString[ namecharsRead - 1] = '\0';
}
size_t  namenewSize = strlen( namenewString);
char*  nameresizedTest = (char*) realloc( name, ( namenewSize + 1) * sizeof(char));
strcpy( name,  namenewString);
free( namenewString);
printf( "Enter your age: ");
char*  agenewString = NULL;
size_t  agebufferSize = 0;
size_t  agecharsRead = getline(& agenewString, & agebufferSize, stdin);
if ( agenewString[ agecharsRead - 1] == '\n') {
     agenewString[ agecharsRead - 1] = '\0';
}
size_t  agenewSize = strlen( agenewString);
char*  ageresizedTest = (char*) realloc( age, ( agenewSize + 1) * sizeof(char));
strcpy( age,  agenewString);
free( agenewString);
printf("Welcome, %s you are %s years old \n",name,age);

}
