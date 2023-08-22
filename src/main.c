#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define NAMEMAXSIZE 100000
int oc;
char name[NAMEMAXSIZE] = "teset";
bool hasvarcode = false;
FILE *write;
int checkNumberType(const char *str) {
    int len = strlen(str);

    bool hasDecimal = false;
    bool hasDigits = false;

    for (int i = 0; i < len; i++) {
        if (i == 0 && (str[i] == '-' || str[i] == '+')) {
            continue; // Allow leading sign for numbers
        }

        if (isdigit(str[i])) {
            hasDigits = true;
        } else if (str[i] == '.' && !hasDecimal) {
            hasDecimal = true;
        }
    }

    if (!hasDigits) {
        return 0; // No digits in the string
    }

    if (hasDecimal) {
        return 2; // Decimal number (float)
    }

    return 1; // Integer
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Dynamically allocate memory for the string
    char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
    if (buffer == NULL) {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t result = fread(buffer, 1, file_size, file);
    if (result != file_size) {
        printf("Error reading the file.\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0'; // Add null terminator at the end

    fclose(file);
    return buffer;
}
void cout(int varorno,char* output) {
  
    // no var
    if (varorno == 1) {
     
        fprintf(write, "printf(\"%s\");\n",output);
   
     
    }
    else{
            fprintf(write, "if (%s->type == STRING){\n",output); 
    fprintf(write, "printf(\"%%s\",%s->value.stringvalue);\n",output);
        fprintf(write, "}\n"); 
          fprintf(write, "if (%s->type == INT){\n",output); 
              fprintf(write, "printf(\"%%d\",%s->value.intvalue);\n",output);
             fprintf(write, "}\n");
                      fprintf(write, "if (%s->type == FLOAT){\n",output); 
                       fprintf(write, "printf(\"%%f\",%s->value.floatvalue);\n",output);
                         fprintf(write, "}\n");    
    }
  
}
void varcodegen(){
if (hasvarcode==false){
fprintf(write,"enum types{\n");
fprintf(write," STRING,\n");
fprintf(write,"INT,\n");
fprintf(write,"FLOAT\n");
fprintf(write,"};\n");
fprintf(write,"struct Var{\n");
fprintf(write," enum types type;\n");
fprintf(write," union \n");
fprintf(write,"  {\n");
fprintf(write," int intvalue;\n");
fprintf(write," float   floatvalue;\n");
fprintf(write,"char* stringvalue;\n");
fprintf(write,"  } value;\n");
fprintf(write,"};\n");
hasvarcode = true;
}
}
void lexer(char* string, int calltype) {
    
     char* output = NULL;
      char *result = NULL;
       char *result2 = NULL;
    int outputIndex = 0;
    int length = strlen(string);
    int isNewLine = 0; 

    for (int i = 0; i < length; i++) {
        if (string[i] == '\n') {
            isNewLine = 1; 
        }
      if (string[i] == 'f') {
            int charsBeforeC = i;
                    int t = -1;
                    int isstr = 0;
      if (i + 1 < length) {
                  if (string[i + 1] == 'u' && string[i + 2] == 'n' && string[i + 3] == 'c') {
                    int k = i - 1;
                    while (k >= 0 && string[k] != '\n') {
                        if (string[k] == '"') {
                            isstr = 1; 
                            break;
                        }
                        k--;
                    }
                
                  if (isstr == 0) {
                    
                  

                   
                    
                    
                         int n = 4;
                     int l = n;
                     
    int resultLength = 0;
     int result2Length = 0;
                    


     while (string[i + n] != '\0') {
  if (isalpha(string[i + n]) || string[i+n] != '\0') { 
   
     if (string[i+n] == '('){
break;
 }
      
         resultLength++;
            result = realloc(result, resultLength * sizeof(char));
           
            result[resultLength - 1] = string[i + n];
 


 

           
        }

     
   
        n++;
     
    }
      result = realloc(result, (resultLength + 1) * sizeof(char));
  
    result[resultLength] = '\0';

l = 4;
int f;
int nest = 0;
while (1)

{
    if(string[i+l] == '-'){

    i =     i+1;
        break;
    }
    i++;
}
int ifistr = 0;
int elsestr = 0;
int overstr = 0;
while (1) {

  l++;

         result2Length++;
             result2 = realloc(result2, result2Length * sizeof(char));
           
            result2[result2Length - 1] = string[i + l - 1];
 if (string[i+l]=='i' && string[i+l+1]== 'f'){
      int k3 = i + l - 1;
ifistr = 0;
   while (k3 >= 0 && string[k3] != '\n') {

                        if (string[k3] == '"') {
                    
                          ifistr = 1;
                            break;
                        }
                        else{
                            ifistr = 0;
                        }
                        k3--;
                    }
                    if (ifistr==0){
                    
                       
                    
 nest++;
                    }
                                    
                 
                   
                 
               
                   
                
  
 }
 if (string[i+l]=='e' && string[i+l+1]== 'l' && string[i+l+2] == 's' && string[i+l+3] == 'e'){
        int k3 = i + l - 1;
    elsestr = 0;
                    while (k3 >= 0 && string[k3] != '\n') {
                        if (string[k3] == '"') {
                       
                         elsestr = 1;
                            break;
                        }
                        k3--;
                    }
                    if(elsestr==0){
   nest++;}
 }
   if (string[i+l] == 'o' && string[i+l+1] == 'v' && string[i+l+2] == 'e' && string[i+l+3] == 'r') {
           int k3 = i + l - 1;
    overstr = 0;
                    while (k3 >= 0 && string[k3] != '\n') {
                        if (string[k3] == '"') {
                       
                         overstr = 1;
                            break;
                        }
                        k3--;
                    }
                    if (overstr==0){
 if(nest>0){
            nest--;
          }
          else{
            break;
          }
                    }
         
        }
      
}
      result2 = realloc(result2, (result2Length + 1) * sizeof(char));
  
    result2[result2Length] = '\0';
//printf("%s",result2);
  fprintf(write, "char* %s(){ \n",result);
lexer(result2,1);
  fprintf(write, "}\n");
    
                    }
                   

                  }
               
        }
    
    }
     
         if (string[i] == 'c') {
         if (calltype == 0){
         }
         else{
             int isstr = 0; 
            if (i + 1 < length) {
                // cout
                if (string[i + 1] == 'o' && string[i + 2] == 'u' && string[i + 3] == 't' && string[i + 4] == ':') {
                    int k = i - 1;
                    while (k >= 0 && string[k] != '\n') {
                        if (string[k] == '"') {
                            isstr = 1; // Set isstr to 1 if a double quote is found on the same line
                            break;
                        }
                        k--;
                    }

                    if (isstr == 0) {
                     
                        int j = i + 5;
                        while (j < length && isspace(string[j])) {
                            j++;
                        }
                        if (j < length && string[j] == '"') {
                            j++; // Move past the opening double quote
                            while (j < length) {
                                if (string[j] == '"' && string[j - 1] != '\\') {
                                    break; // Found the closing double quote
                                }

                                // Instead of using putchar, append the character to the output string
                                output = (char*)realloc(output, (outputIndex + 2) * sizeof(char));
                                output[outputIndex++] = string[j];
                                output[outputIndex] = '\0'; // Null-terminate the output string

                                j++;
                            }
                           
                            cout(1, output);

                            free(output);
                            output = NULL;
                            outputIndex = 0;
                        }
                        else{
                    
                            while (string[j]!='\n')
                            {
                               output = (char*)realloc(output, (outputIndex + 2) * sizeof(char));
                                output[outputIndex++] = string[j];
                                output[outputIndex] = '\0'; // Null-terminate the output string
                                j++;
                            }
                          cout(0,output);
                            free(output);
                            output = NULL;
                            outputIndex = 0;
                        }
                    }
                }
            }
        }
        }
          if (string[i] == 'i') {
 if (calltype == 0){
         }
         else{
            if (string[i + 1] == 'f') {
                int nest = 0;
              int  ifistr = 0;
              int   overstr = 0;
                 int k = i - 1;
                 int isstr = 0;
                    while (k >= 0 && string[k] != '\n') {
                        if (string[k] == '"') {
                            isstr = 1; // Set isstr to 1 if a double quote is found on the same line
                            break;
                        }
                        k--;
                    }
                    if (isstr==0){
                            int resultLength = 0;
                            char* result = NULL;
                                 int result2Length = 0;
                            char* result2 = NULL;
                          int n = 2;
                          int foundbrack = 0;
                          while(1){
                            if (string[i+n] == '('){
                           foundbrack = 1;
                             break;
                            }
                            
                            n++;
                          }
                      if (foundbrack==1){
                        while(string[i+n+1] != ')'){
                            resultLength++;
            result = realloc(result, resultLength * sizeof(char));
           
            result[resultLength - 1] = string[i + n + 1];
 
                            n++;
                        }
                           result = realloc(result, (resultLength + 1) * sizeof(char));
  
    result[resultLength] = '\0';
                      }
                   while(string[i+n] != '\n'){
                    n++;
                   }
                      while(1){
                      
                                           result2Length++;
            result2 = realloc(result2, result2Length * sizeof(char));
           
            result2[result2Length - 1] = string[i + n];
                        n++;
                        if (string[i+n]=='i' && string[i+n+1]== 'f'){
      int k3 = i + n - 1;
ifistr = 0;
   while (k3 >= 0 && string[k3] != '\n') {

                        if (string[k3] == '"') {
                    
                          ifistr = 1;
                            break;
                        }
                        else{
                            ifistr = 0;
                        }
                        k3--;
                    }
                    if (ifistr==0){
                    
                       
                    
 nest++;
                    }
                                    
                 
                   
                 
               
                   
                
  
 }
 if (string[i+n] == 'o' && string[i+n+1] == 'v' && string[i+n+2] == 'e' && string[i+n+3] == 'r') {
           int k3 = i + n - 1;
    overstr = 0;
                    while (k3 >= 0 && string[k3] != '\n') {
                        if (string[k3] == '"') {
                       
                         overstr = 1;
                            break;
                        }
                        k3--;
                    }
                    if (overstr==0){
 if(nest>0){
            nest--;
          }
          else{
            break;
          }
                    }
         
        }
                      }
                                  result2 = realloc(result2, (result2Length + 1) * sizeof(char));
  
    result2[result2Length] = '\0';
    i = i + n;

printf("%s",result2);
lexer(result2,1);
                    }  
         }
          }
  
}
        if (string[i] == 'v') {
 if (calltype == 0){
         }
         else{
            // variables
            char* type = "   ";
               if (i + 1 < length) {
            if (string[i+1] == 'a' && string[i+2] == 'r'){
                int isstr = 0;
                   int k = i - 1;
                    while (k >= 0 && string[k] != '\n') {
                        if (string[k] == '"') {
                            isstr = 1; // Set isstr to 1 if a double quote is found on the same line
                            break;
                        }
                        k--;
                    }
if (isstr==0){
    int d = 3;
         int resultLength = 0;
                            char* result = NULL;
                                   int result2Length = 0;
                            char* result2 = NULL;
 while(string[i+d] != '='){
                resultLength++;
            result = realloc(result, resultLength * sizeof(char));
           
            result[resultLength - 1] = string[i + d];
    d++;
 }
d = d+1;

 
 while(string[i+d]!='\n'){
   
        result2Length++;
            result2 = realloc(result2, result2Length * sizeof(char));
           
            result2[result2Length - 1] = string[i + d];
    d++;
 }
      result = realloc(result, (resultLength + 1) * sizeof(char));
  
    result[resultLength] = '\0';

  result2 = realloc(result2, (result2Length + 1) * sizeof(char));
  
    result2[result2Length] = '\0';

  int t = checkNumberType(result2);

if (t==0){
fprintf(write,"   struct Var *%s = malloc(sizeof(struct Var));\n",result);
fprintf(write,"    %s->type = STRING;\n",result);
fprintf(write,"        %s->value.stringvalue = %s;\n",result,result2);
}
if (t==1){
  fprintf(write,"   struct Var *%s = malloc(sizeof(struct Var));\n",result);
  fprintf(write,"    %s->type = INT;\n",result);
  fprintf(write,"        %s->value.intvalue = %s;\n",result,result2);
}
if (t==2){
      fprintf(write,"   struct Var *%s = malloc(sizeof(struct Var));\n",result);
        fprintf(write,"    %s->type = FLOAT;\n",result);
          fprintf(write,"        %s->value.floatvalue = %s;\n",result,result2);
}
}

            }
            }
         }
        }

    }


}
int main() {
FILE *FL;
FL = fopen("main.crf","r");
  write = fopen("code.c", "w");
    fprintf(write, "#include <stdio.h> \n #include <stdlib.h> \n");
    char* file_content = read_file("main.crf");
    varcodegen();
  lexer(file_content,0);
   fclose(write);
   system("gcc code.c -o output");
   system("./output");
}