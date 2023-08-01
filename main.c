#include <stdio.h>  
#include <string.h>  
#include <ctype.h>
FILE *write;
void cout(char* val,int varorno){
write = fopen("code.c","w");
// no var
if (varorno==1){
     fprintf(write,"printf(%s);\n");
}
}
void lexer(char* string)  
{  
char* output = NULL;
    int outputIndex = 0;
 
    int length = strlen(string);
          

      
    for(int i = 0; i < length; i++){  

        if (string[i] == 'c') {
         
            if (i + 1 < length) {
                 // cout  
        if (string[i+1]=='o' && string[i+2]=='u' && string[i+3]=='t' && string[i+4]==':'){
               int j = i + 5;
        while (j < length && isspace(string[j])) {
                    j++;
                }
                if (j < length && string[j] == '"') {
            
                }
        }
            } else {
  
            }
        }
   
    }  

 
}  
int main(){
    lexer("cout:          \"");
}