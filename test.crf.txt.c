#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void main() {
  const char* nameval =  ""; 
  size_t namesz = strlen(nameval); 
 char* name = (char*) malloc((namesz + 1) * sizeof(char)); 
     strcpy(name,nameval); 
char* nameisconst = "false"; 
  const char* ageval =  ""; 
  size_t agesz = strlen(ageval); 
 char* age = (char*) malloc((agesz + 1) * sizeof(char)); 
     strcpy(age,ageval); 
char* ageisconst = "false"; 
printf( "Enter your name: ");
 
 if (strcmp( nameisconst,"false")==0) { 
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
}
else{
printf("Cannot modify a constant ");
}
printf( "Enter your age: ");
 
 if (strcmp( ageisconst,"false")==0) { 
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
}
else{
printf("Cannot modify a constant ");
}
printf("Welcome, %s you are %s years old \n",name,age);

}
