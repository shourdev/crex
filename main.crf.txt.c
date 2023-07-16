#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void main() {
char* dtype = "int"; 
  const char* dval = "9"; 
  size_t dsz = strlen(dval); 
 char* d = (char*) malloc((dsz + 1) * sizeof(char)); 
     strcpy(d,dval); 
char* disconst = "false"; 
 
 if (strcmp( disconst,"false")==0) { 
char*  dnewString = NULL;
size_t  dbufferSize = 0;
size_t  dcharsRead = getline(& dnewString, & dbufferSize, stdin);
if ( dnewString[ dcharsRead - 1] == '\n') {
     dnewString[ dcharsRead - 1] = '\0';
}
size_t  dnewSize = strlen( dnewString);
char*  dresizedTest = (char*) realloc( d, ( dnewSize + 1) * sizeof(char));
    char*  dstr = (char*)malloc(( dnewSize + 1) * sizeof(char));
      int  dinteger;
       float  ddecimal;
       float  disFloat = 0;
        if (sscanf( dnewString, "%f", & ddecimal) == 1) {
   if (strchr( dnewString, '.') != NULL) {
  disFloat = 1;
   }
   }
      if   ( disFloat) {   
        dtype = "float";
       }
           else if (sscanf( dnewString, "%d", & dinteger) == 1) {
        dtype = "int";
       }
      else {  
        dtype = "str";
       }
strcpy( d,  dnewString);
free( dnewString);
}
else{
printf("Cannot modify a constant ");
}
printf("%s",d);

}
