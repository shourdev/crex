#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h> 

char name[1000];
char acname[1000];

void remove_leading_whitespace(char *str) {
    if (str == NULL) {
        return; // Handle NULL pointer case
    }

    int len = strlen(str);
    if (len == 0) {
        return; // Empty string, nothing to remove
    }

    int start_index = 0;
    while (isspace(str[start_index])) {
        start_index++;
    }

    if (start_index > 0) {
        memmove(str, str + start_index, len - start_index + 1);
    }
}
int isDecimalOrNumber(const char* str) {
    // Helper function to check if a character is a digit
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    int decimalPoints = 0;
    int digits = 0;

    // Check if the string is empty
    if (str == NULL || *str == '\0') {
        return -1; // Indicate an error (e.g., empty string)
    }

    // Check the first character (it could be a negative sign or a digit)
    if (*str == '-') {
        str++; // Skip the negative sign if present
    }
    else if (!isDigit(*str)) {
        return -1; // Invalid input (not a digit or negative sign)
    }

    // Loop through the rest of the string to check for digits and decimal point
    while (*str) {
        if (isDigit(*str)) {
            digits++;
        }
        else if (*str == '.') {
            decimalPoints++;
        }
        else {
            return -1; // Invalid character encountered
        }
        str++; // Move to the next character
    }

    // Check if there is at most one decimal point and at least one digit
    if (decimalPoints > 1 || digits == 0) {
        return -1; // Invalid decimal format
    }

    return decimalPoints == 1 ? 1 : 0; // Return 1 if it's a decimal, 0 if it's an integer
}

int is_number(char *str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (!isdigit(str[i]) && str[i] != '.' && str[i] != '-' && str[i] != '+') {
      return 1;
    }
  }
  return 0;
}
void removeTrailingQuotes(char* str) {
    int length = strlen(str);
    
    if (length > 0 && str[length - 1] == '\"') {
        str[length - 1] = '\0';
    }
}

int hasWhitespaceAtEnd(const char* str) {
    int len = strlen(str);
    if (len > 0 && isspace(str[len - 1])) {
        return 0;
    }
    return 1;
}
void removeQuotes(char* str) {
    char* i = str;  // input string pointer
    char* o = str;  // output string pointer

    while (*i) {
        if (*i != '"') {
            *o = *i;
            o++;
        }
        i++;
    }

    *o = '\0';  // add null terminator to the end of the output string
}
char* checkString(const char* input) {
    const char delimiter = '%';
    char* words = NULL;
    bool hasPercentage = false;

    // Check if the input contains '%'
    if (strchr(input, delimiter) != NULL) {
        hasPercentage = true;

        // Create a copy of the input string
        char* inputCopy = strdup(input);

        // Find the words after each '%'
        char* token = strtok(inputCopy, " ");
        while (token != NULL) {
            if (token[0] == delimiter && strlen(token) > 1) {
                if (words == NULL) {
                    words = strdup(token + 1); // Exclude the '%' character
                } else {
                    // Append the comma and the word to the existing words
                    size_t len = strlen(words);
                    words = realloc(words, len + strlen(token) + 2); // +2 for comma and null terminator
                    strcat(words, ",");
                    strcat(words, token + 1); // Exclude the '%' character
                }
            }

            token = strtok(NULL, " ");
        }

        // Free the memory allocated for the input copy
        free(inputCopy);
    }

    // Return the appropriate value
    if (hasPercentage && words != NULL) {
        return words;
    } else {
        return strdup("1");
    }
}
char* replaceWords(char *str) {
    const char *delimiter = " ";
    char *token;
    char *replaceToken = "%s";
    char *newString = NULL;
    char *result = NULL;
    int count = 0;

    newString = strdup(str);
    token = strtok(newString, delimiter);

    while (token != NULL) {
        if (token[0] == '%' && strlen(token) > 1 && isalpha(token[1])) {
            token = replaceToken;
            count++;
        }

        if (result == NULL) {
            result = strdup(token);
        } else {
            result = realloc(result, strlen(result) + strlen(token) + 1);
            strcat(result, delimiter);
            strcat(result, token);
        }

        token = strtok(NULL, delimiter);
    }

return result;

}
void stripTrailingWhitespace(char* str) {
    int i = strlen(str) - 1;
    while (i >= 0 && isspace((unsigned char)str[i])) {
        str[i] = '\0';
        i--;
    }
}

char* getFormattedString(const char* str) {
    int count = 0;
    int length = strlen(str);
    
    // Count the number of commas
    for (int i = 0; i < length; i++) {
        if (str[i] == ',') {
            count++;
        }
    }
    
    // Calculate the length required for the formatted string
    int formattedLength = 3 * count + 1;
    
    // Allocate memory for the formatted string
    char* formattedStr = (char*)malloc(formattedLength * sizeof(char));
    
    int j = 0;
    
    // Add "%s " to the formatted string for each comma
    for (int i = 0; i < count; i++) {
        formattedStr[j++] = '%';
        formattedStr[j++] = 's';
        formattedStr[j++] = ' ';
    }
    
    // Null-terminate the formatted string
    formattedStr[j] = '\0';
    
    return formattedStr;
}
char* removeBeforeEquals(char* input) {
    char* equals = strchr(input, '=');

    if (equals != NULL) {
        // Move the pointer to the character after the '='
        equals++;

        // Calculate the length of the remaining string
        size_t length = strlen(equals) + 1;

        // Move the remaining characters to the beginning of the input string
        memmove(input, equals, length);
    }

    return input;
}
char* getFirstWord(const char* inputString) {
    // Find the length of the input string
    size_t inputLength = strlen(inputString);

    // Allocate memory for a new string (plus 1 for the null terminator)
    char* firstWord = (char*)malloc((inputLength + 1) * sizeof(char));

    // Copy the first word into the new string
    sscanf(inputString, "%s", firstWord);

    return firstWord;
}
int hasQuotes(const char* str) {
    int len = strlen(str);

    // Skip leading whitespace
    int start = 0;
    while (start < len && isspace(str[start])) {
        start++;
    }

    // Skip trailing whitespace
    int end = len - 1;
    while (end >= start && isspace(str[end])) {
        end--;
    }

    // Check if the remaining string has at least two characters
    if (end - start >= 1) {
        // Check if the first and last characters are double quotation marks
        if (str[start] == '"' && str[end] == '"') {
            return 1; // String has quotes
        }
    }

    return 0; // String does not have quotes
}
char* get_text_between_func_and_over(const char* string, const char* func_name) {
    const char* func_start = strstr(string, func_name);
    if (func_start == NULL) {
        return NULL; // Function name not found in string
    }

    const char* func_end = strstr(func_start, "over");
    if (func_end == NULL) {
        return NULL; // "over" not found after function name in string
    }

    const char* target_start = func_start + strlen(func_name);
    while (target_start < func_end && (*target_start == ' ' || *target_start == '\t' || *target_start == '\n')) {
        target_start++; // Skip whitespace characters
    }

    size_t result_size = func_end - target_start;
    char* result = malloc(result_size + 1);
    strncpy(result, target_start, result_size);
    result[result_size] = '\0';

    return result;
}
void removeCharacters(char* str) {
    int i, j = 0;
    int length = strlen(str);

    for (i = 0; i < length; i++) {
        if (str[i] != '(' && str[i] != ')' && str[i] != '-') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
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

void removeWordFromString(char *str, const char *wordToRemove) {
    char *result = NULL;
    int i, cnt = 0;
    size_t wordToRemoveLen = strlen(wordToRemove);

    // Count the occurrences of the word to remove
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], wordToRemove) == &str[i]) {
            cnt++;
            i += wordToRemoveLen - 1;
        }
    }

    // Allocate memory for the resulting string
    result = (char *)malloc(i - cnt * wordToRemoveLen + 1);
    if (result == NULL) {
        printf("Memory allocation error.\n");
        return;
    }

    // Remove the word from the string
    i = 0;
    while (*str) {
        if (strstr(str, wordToRemove) == str) {
            strcpy(&result[i], &str[wordToRemoveLen]);
            i += wordToRemoveLen;
            str += wordToRemoveLen;
        } else {
            result[i++] = *str++;
        }
    }
    result[i] = '\0';

    // Copy the modified string back to the original string
    strcpy(str, result);

    // Free the allocated memory
    free(result);
}

void removeAfterAsterisk(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* tempFile = tmpfile();  // Create a temporary file
    if (tempFile == NULL) {
        printf("Failed to create a temporary file.\n");
        fclose(file);
        return;
    }

    char* line = NULL;
    size_t lineSize = 0;
    size_t bytesRead;

    while ((bytesRead = getline(&line, &lineSize, file)) != -1) {
        if (bytesRead > 0 && line[bytesRead - 1] == '\n') {
            line[bytesRead - 1] = '\0';  // Remove the newline character from the line
        }

        char* asteriskPtr = strchr(line, '*');
        if (asteriskPtr != NULL) {
            *asteriskPtr = '\0';  // Truncate the line at the position of the asterisk
        }
        fprintf(tempFile, "%s\n", line);  // Write the modified line to the temporary file
    }

    free(line);  // Free the dynamically allocated line

    fclose(file);
    rewind(tempFile);  // Move the temporary file pointer to the beginning

    file = fopen(filename, "w");  // Reopen the original file in write mode
    if (file == NULL) {
        printf("Failed to reopen the file.\n");
        fclose(tempFile);
        return;
    }

    int ch;
    while ((ch = fgetc(tempFile)) != EOF) {
        fputc(ch, file);  // Copy the contents of the temporary file to the original file
    }

    fclose(file);
    fclose(tempFile);
}
char* translater(char* code,char* funcname){
       FILE *file;
    char name3[2000];
    strcpy(name3,name);

 char* name2 = strcat(name3,funcname);
 
  removeCharacters(name2);
  strcat(name2,".txt");
 
  file = fopen(name2, "w");
 char outputString[1000];
    char* line = strtok(code, "\n");
    while (line != NULL) {
        // Check if the line contains "cout:"
        if (strstr(line, "cout:") != NULL) {
            // Extract the text after "cout:"
            char* extractedText = strstr(line, "cout:") + strlen("cout:");
            strcpy(outputString, extractedText);  // Copy the extracted text to the output string
            if (hasQuotes(outputString)==1){
if (strcmp(checkString(outputString),"1")==0){
 
        fprintf(file,"printf(%s);\n",outputString);
}
else{
  char* test1 = checkString(outputString);
    char* test = replaceWords(outputString);

    size_t test_len = strlen(test);
    size_t test1_len = strlen(test1);

    // Allocate memory for the destination buffer
    char* result = malloc((test_len + test1_len + 2) * sizeof(char));  // +2 for the added double-quote and null-terminating character
    char res2[1000];
strcpy(res2,test);

removeTrailingQuotes(res2);
removeTrailingQuotes(test);


 if (hasWhitespaceAtEnd(res2)==1)
 { 
   strcat(test, "\"");
 

 }
 else{
    strcat(test, "\"");

 }
 
    
 


      strcat(test, ",");
  
    strcpy(result, test);

    removeQuotes(test1);
    
  
    strcat(result, test1);

    
 fprintf(file, "printf(%s);\n", result);


   
}
            }
               else{
       
               remove_leading_whitespace(outputString);
               if (is_number(outputString) == 0)
               {
             

          fprintf(file,"printf(\"%s\");",outputString);
               }

                else{
                char optstring2[1000];
                strcpy(optstring2,outputString);
                strcat(optstring2,",");
                   char* formattedString = getFormattedString(optstring2);
                   stripTrailingWhitespace(formattedString);
fprintf(file, "printf(\"%s\",%s);\n",formattedString, outputString);
                }
               }
        }
              if (strstr(line, "var") != NULL) {
          
            char* extractedText = strstr(line, "var") + strlen("var");
            strcpy(outputString, extractedText);  // Copy the extracted text to the output string
        char* firstWord = getFirstWord(outputString);


        
       char* result = removeBeforeEquals(outputString);
   char sec[1000];
   char sec2[1000];
   strcpy(sec,firstWord);
    strcpy(sec2,firstWord);
char* var = strcat(sec,"val");
char* var2 = strcat(sec2,"sz");
char* fl = "false";
 remove_leading_whitespace(outputString);
if (is_number(outputString)==1)
{
        fprintf(file,"char* %stype = \"str\"; \n",firstWord); 
         fprintf(file,"  const char* %s = %s; \n",var,outputString);
}
else{
if (isDecimalOrNumber(outputString)==0){

   fprintf(file,"char* %stype = \"int\"; \n",firstWord); 
 fprintf(file,"  const char* %s = \"%s\"; \n",var,outputString);
}
else{
   fprintf(file,"char* %stype = \"float\"; \n",firstWord); 
    fprintf(file,"  const char* %s = \"%s\"; \n",var,outputString);
}
}
     
       fprintf(file,"  size_t %s = strlen(%s); \n",var2,var);
             fprintf(file," char* %s = (char*) malloc((%s + 1) * sizeof(char)); \n",firstWord,var2);
                fprintf(file,"     strcpy(%s,%s); \n",firstWord,var);   
          fprintf(file,"char* %sisconst = \"%s\"; \n",firstWord,fl); 

          free(firstWord);
   
     
         
        }
          if (strstr(line, "const") != NULL) {
          
            char* extractedText = strstr(line, "const") + strlen("const");
            strcpy(outputString, extractedText);  // Copy the extracted text to the output string
        char* firstWord = getFirstWord(outputString);


        
       char* result = removeBeforeEquals(outputString);
   char sec[1000];
   char sec2[1000];
   strcpy(sec,firstWord);
    strcpy(sec2,firstWord);
char* var = strcat(sec,"val");
char* var2 = strcat(sec2,"sz");
char* fl = "true";
remove_leading_whitespace(outputString);
if (is_number(outputString)==1)
{
        fprintf(file,"char* %stype = \"str\"; \n",firstWord); 
         fprintf(file,"  const char* %s = %s; \n",var,outputString);
}
else{
if (isDecimalOrNumber(outputString)==0){

   fprintf(file,"char* %stype = \"int\"; \n",firstWord); 
 fprintf(file,"  const char* %s = \"%s\"; \n",var,outputString);
}
else{
   fprintf(file,"char* %stype = \"float\"; \n",firstWord); 
    fprintf(file,"  const char* %s = \"%s\"; \n",var,outputString);
}
}
     
       fprintf(file,"  size_t %s = strlen(%s); \n",var2,var);
             fprintf(file," char* %s = (char*) malloc((%s + 1) * sizeof(char)); \n",firstWord,var2);
                fprintf(file,"     strcpy(%s,%s); \n",firstWord,var);   
          fprintf(file,"char* %sisconst = \"%s\"; \n",firstWord,fl); 

          free(firstWord);
   
     
         
        }
         if (strstr(line, "cin:") != NULL) {
      
            char* extractedText = strstr(line, "cin:") + strlen("cin:");
            strcpy(outputString, extractedText);
            int i;
         remove_leading_whitespace(outputString);
         
    fprintf(file, " \n if (strcmp(%sisconst,\"false\")==0) { \n", outputString);    
fprintf(file, "char* %s%dnewString = NULL;\n", outputString,i);
fprintf(file, "size_t %s%dbufferSize = 0;\n", outputString,i);
fprintf(file, "size_t %s%dcharsRead = getline(&%s%dnewString, &%s%dbufferSize, stdin);\n", outputString,i, outputString,i, outputString,i);
fprintf(file, "if (%s%dnewString[%s%dcharsRead - 1] == '\\n') {\n", outputString,i, outputString,i);
fprintf(file, "    %s%dnewString[%s%dcharsRead - 1] = '\\0';\n", outputString,i, outputString,i);
fprintf(file, "}\n");
fprintf(file, "size_t %s%dnewSize = strlen(%s%dnewString);\n", outputString,i, outputString,i);
fprintf(file, "char* %s%dresizedTest = (char*) realloc(%s, (%s%dnewSize + 1) * sizeof(char));\n",outputString,i, outputString, outputString,i);
fprintf(file, "    char* %s%dstr = (char*)malloc((%s%dnewSize + 1) * sizeof(char));\n", outputString,i, outputString,i);
fprintf(file, "%stype = \"str\";\n", outputString);
fprintf(file, "strcpy(%s, %s%dnewString);\n", outputString, outputString,i);
fprintf(file, "free(%s%dnewString);\n", outputString,i);
fprintf(file, "}\n");

fprintf(file, "else{\n");
fprintf(file, "printf(\"Cannot modify a constant \");\n");
fprintf(file, "}\n");
i++;
         }
             if (strstr(line, "exit:") != NULL) {
      
            fprintf(file,"exit(0)");
             }
               if (strstr(line, "int:") != NULL) {
                int i2;
                remove_leading_whitespace(outputString);
             char* extractedText = strstr(line, "int:") + strlen("int:");
            strcpy(outputString, extractedText); 
            fprintf(file, "if (strcmp(%stype,\"int\")==0) { \n", outputString);
fprintf(file, "%stype = \"int\";\n", outputString);
fprintf(file,"} \n");
         fprintf(file, "if (strcmp(%stype,\"float\")==0) { \n", outputString);
         fprintf(file, "%stype = \"int\";\n", outputString);
         fprintf(file,"} \n");
            fprintf(file, "if (strcmp(%stype,\"str\")==0) { \n", outputString);

               
             
        fprintf(file,"} \n");
                i2++;
             }
           if (strstr(line, "str:") != NULL) {
              
      
             char* extractedText = strstr(line, "str:") + strlen("str:");
              strcpy(outputString, extractedText); 
                        remove_leading_whitespace(outputString);
             fprintf(file,"%stype = \"str\"; \n",outputString);
           }
             if (strstr(line, "flt:") != NULL) {
              int i3;
      
             char* extractedText = strstr(line, "flt:") + strlen("flt:");
              strcpy(outputString, extractedText); 
          
           }
        line = strtok(NULL, "\n");
        // Move to the next line
    }
       
fclose(file);
 char* file_content = read_file(name2);
remove(name2);
return file_content;
}


void write(const char* code) {
strcat(name, ".c");
strcpy(acname,name);
    FILE* file = fopen(name, "w");  // Open file in write mode

    fprintf(file, "#include <stdio.h>\n");
      fprintf(file, "#include <stdlib.h>\n");
           fprintf(file, "#include <string.h>\n");
                      fprintf(file, "#include <ctype.h>\n");
fprintf(file,"#include <stdbool.h> \n");
    const char* searchStr = "func";
    const char* delimiter = "()";
    const size_t codeLength = strlen(code);




    size_t pos = 0;
    while (pos < codeLength) {
        const char* funcPos = strstr(code + pos, searchStr);
        if (funcPos == NULL) {
            break;
        }

        pos = funcPos - code + strlen(searchStr);
        const char* endLine = strchr(code + pos, '\n');
        if (endLine == NULL) {
            endLine = code + codeLength;  // Reached end of code
        }

        const char* openingParenthesis = strchr(code + pos, '(');
        if (openingParenthesis != NULL && openingParenthesis < endLine) {
            const char* closingParenthesis = strchr(openingParenthesis, ')');
            if (closingParenthesis != NULL && closingParenthesis < endLine) {
                const size_t functionNameLength = openingParenthesis - (funcPos + strlen(searchStr) + 1);
                char* functionName = (char*)malloc(functionNameLength + 1);
                strncpy(functionName, funcPos + strlen(searchStr) + 1, functionNameLength);
                functionName[functionNameLength] = '\0';
                removeCharacters(functionName);
      fprintf(file, "void %s() {\n", functionName);
      strcat(functionName,"()-");
    char* result = get_text_between_func_and_over(code, functionName);
 

          
              

char* returned = translater(result,functionName);

   fprintf(file, "%s\n",returned);

                fprintf(file, "}\n");

                free(functionName);
            }
        }

        pos = endLine - code + 1;
    }
   fclose(file);
 
}
void compstg1(char* code){
      FILE *file;
    
 
    
   file = fopen(name, "w");
       fprintf(file, "%s", code);
       fclose(file);
removeAfterAsterisk(name);

   char* file_content = read_file(name);
  remove(name);
write(file_content);
free(file_content);

    char command[1024];
    snprintf(command, sizeof(command), "gcc %s -o program --static ", acname);
    system(command);
 //   remove(acname);
    snprintf(command, sizeof(command), "./program");
    system(command);
  
}
int main(int argc, char *argv[]) {
    

       

    
    if (strcmp(argv[1], "--help") == 0) {
        printf("Crex is a simple programming language designed to do anything! \n");
        printf("Run a file: ./crex <filename>.crf \n");
        printf("Documentation can be found at: https://github.com/shourdev/crex#documentation \n");
        return 0;
    }

   char* file_content = read_file(argv[1]);
    if (file_content == NULL) {
        return 1;
    }

strcpy(name,argv[1]);
strcat(name,".txt");

compstg1(file_content);


    free(file_content);
    return 0;
}