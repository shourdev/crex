#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for isspace function
char name[1000];


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
char* translater(char* code){
if (strcmp(code,"cout:")==0)
{

 char* output = malloc(strlen("printf(\"hello world\");") + 1);
        strcpy(output, "printf(\"hello world\");");
        return output;

}else{return NULL;}
}


void write(const char* code) {


strcat(name, ".c");
    FILE* file = fopen(name, "w");  // Open file in write mode

    fprintf(file, "#include <stdio.h>\n");

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
 

          
                fprintf(file, "    //  code goes here\n");
printf("%s",result);


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
