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
    // Copy the name to the array
    strcpy(array[currentPosition], name);

    // Remove quotes from the value before storing it
    char cleanValue[MAX_VALUE_LENGTH];
    strncpy(cleanValue, value + 1, strlen(value) - 2);
    cleanValue[strlen(value) - 2] = '\0';

    // Remove the last quote if it exists
    if (cleanValue[strlen(cleanValue) - 1] == '"') {
        cleanValue[strlen(cleanValue) - 1] = '\0';
    }

    strcpy(array[currentPosition + 1], cleanValue);

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
void removeQuotes(char* str) {
    int len = strlen(str);

    // Check if the string is long enough to have quotes
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        // Shift characters to remove the quotes
        for (int i = 1; i < len - 1; i++) {
            str[i - 1] = str[i];
        }
        str[len - 2] = ' '; // Replace the last quote with a space
        str[len - 1] = '\0'; // Null-terminate the string
    }
}



int isStringCheck(const char* text) {
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        if (!isdigit(text[i])) {
            return 1;  // Not a string
        }
    }

    return 0;  // String
}
void findNameAndUpdateValue(const char* name, const char* newValue) {
    for (int i = 0; i < currentPosition; i += 2) {
        if (strcmp(array[i], name) == 0) {
            // Check if the position is even
            if (i % 2 == 0) {
                // Remove the value at the position
                for (int j = i; j < currentPosition - 2; j++) {
                    strcpy(array[j], array[j + 2]);
                }
                currentPosition -= 2;

                // Insert the new value at the position
                strcpy(array[i + 1], newValue);
                return;
            } else {
                printf("Error variable not found.\n");
                return;
            }
        }
    }

    printf("Error variable not found.\n");
}
void removeWord(char *str, const char *word) {
    char *pos = strstr(str, word); // Find the first occurrence of the word

    while (pos != NULL) {
        size_t wordLen = strlen(word);
        memmove(pos, pos + wordLen, strlen(pos + wordLen) + 1); // Shift the remaining characters

        pos = strstr(str, word); // Find the next occurrence of the word
    }

    // Remove leading whitespace
    int len = strlen(str);
    int start = 0;
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    // Remove trailing whitespace
    int end = len - 1;
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Shift characters to remove leading and trailing whitespace
    int dst = 0;
    for (int src = start; src <= end; src++) {
        str[dst++] = str[src];
    }
    str[dst] = '\0'; // Null-terminate the resulting string
}
int main(int argc, char *argv[]) {
    char line[10000];
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
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
// Copy of varName
         
            // Extracting value
            pos = strchr(line, '=');
            if (pos != NULL) {
                pos += 1; // Skip "="
                while (*pos == ' ') {
                    pos++; // Skip spaces after "="
                }
                strcpy(value, pos);
                   

   addNameAndValue(varName,value);
      
            }
        }
   if (strstr(line, "cout:") != NULL) {
    removeWord(line, "cout:");
  //  stripWhitespace(line);
    if (hasQuotes(line) == 1) {
  
        removeQuotes(line);
     
        printf("%s\n", line);
    } else {
        int result = isStringCheck(line);

if (result){
  
   const char* val = findNameAndGetNextValue(line);
        if (val != NULL) {
            char newString[strlen(val) + 1];  // Add 1 for the null terminator
            strcpy(newString, val);
           removeQuotes(newString);
            
            printf("%s\n", newString);
        } else {
            printf("Variable %s not found.\n",line);
         break;
        }
}
else {
    printf("%s\n",line);
}
     
    }
}
        if (strstr(line, "cin:") != NULL) {
            char opt[10000];
            scanf("%s",opt);
            removeWord(line,"cin:");
;
            stripWhitespace(line);
            findNameAndUpdateValue(line,opt);
            
        }
       

    }

    fclose(file);
    return 0;
}