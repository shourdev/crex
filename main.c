#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for isspace function
#define MAX_SIZE 100
#define MAX_NAME_LENGTH 50
#define MAX_VALUE_LENGTH 50
   int hasqu = 0;
// Global array to store names and values
char array[MAX_SIZE][MAX_NAME_LENGTH + MAX_VALUE_LENGTH];

int currentPosition = 0;

void addNameAndValue(const char* name, const char* value) {
    // Copy the name and value to the array
    strcpy(array[currentPosition], name);
    strcpy(array[currentPosition + 1], value);

    // Move the current position to the next pair
    currentPosition += 2;
}

void stripWhitespace(char* str) {
    int len = strlen(str);
    int dst = 0;

    for (int src = 0; src < len; src++) {
        if (!isspace((unsigned char)str[src])) {
            str[dst++] = str[src];
        }
    }

    str[dst] = '\0';  // Null-terminate the resulting string
}

const char* findNameAndGetNextValue(const char* name) {
    for (int i = 0; i < currentPosition; i += 2) {
        if (strcmp(array[i], name) == 0) {
            return array[i + 1];
        }
    }

    return NULL;
}
void removeWord(char *str, const char *word) {
    char *pos = strstr(str, word); // Find the first occurrence of the word

    while (pos != NULL) {
        size_t wordLen = strlen(word);
        memmove(pos, pos + wordLen, strlen(pos + wordLen) + 1); // Shift the remaining characters

        pos = strstr(str, word); // Find the next occurrence of the word
    }
}
int hasQuotes(const char* str) {
    int len = strlen(str);

    // Check if the string has at least two characters
    if (len >= 2) {
        // Check if the first and last characters are double quotation marks
        if (str[0] == '"' && str[len - 1] == '"') {
            return 1; // String has quotes
        }
    }

    return 0; // String does not have quotes
}

char removeQuotes(char* str) {
    if (hasQuotes(str) == 1) {
        int len = strlen(str);
        hasqu = 1;
      
        // Check if the string is long enough to have quotes
        if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
            // Shift all characters one position to the left to overwrite the quotes
            for (int i = 0; i < len - 2; i++) {
                str[i] = str[i + 1];
            }

            // Null-terminate the string to remove the trailing quote
            str[len - 2] = '\0';
        }
    }
}


int main(int argc, char *argv[]) {
    char line[10000];
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "cout:") != NULL) {
            removeWord(line, "cout:");
            stripWhitespace(line);
            if(hasQuotes==1){
removeQuotes(line);
printf("%s",line); 
            }
            else{
                
                const char* val = findNameAndGetNextValue(line);
               char newString[strlen(val) + 1];  // Add 1 for the null terminator

    // Copy the data to the new array
    strcpy(newString, val);
                removeQuotes(newString);
                printf("%s \n",newString);
                
            }
            
       
           
        }
        if (strstr(line, "cin:") != NULL) {
            // Handle cin statements here
        }
        if (strstr(line, "var") != NULL) {
            char varName[100];
            char value[100];

            // Extracting variable name
            char *pos = strstr(line, "var");
            if (pos != NULL) {
                pos += strlen("var") + 1;
                char *end = strchr(pos, ' ');
                if (end != NULL) {
                    strncpy(varName, pos, end - pos);
                    varName[end - pos] = '\0';
                }
            }
 char varNameCopy[100]; // Copy of varName
         
            // Extracting value
            pos = strchr(line, '=');
            if (pos != NULL) {
                pos += 1; // Skip "="
                while (*pos == ' ') {
                    pos++; // Skip spaces after "="
                }
                strcpy(value, pos);
                   strcpy(varNameCopy, varName);
                   stripWhitespace(varName);
 stripWhitespace(value);
   addNameAndValue(varName,value);
      
            }
        }
    }

    fclose(file);
    return 0;
}
