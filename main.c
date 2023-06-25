#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for isspace function
#define MAX_SIZE 100
#define MAX_NAME_LENGTH 50
#define MAX_VALUE_LENGTH 100
  
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
void splitString(const char* input, char* beforeComma, char* afterComma) {
    const char* commaPosition = strchr(input, ',');
  
    if (commaPosition == NULL) {
        // No comma found, store the entire string in 'beforeComma' and set 'afterComma' as an empty string
        strcpy(beforeComma, input);
        strcpy(afterComma, "");
    } else {
        // Calculate the length of the string before the comma
        size_t beforeLength = commaPosition - input;

        // Copy the strings
        strncpy(beforeComma, input, beforeLength);
        strcpy(afterComma, commaPosition + 1);
    }
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
        if (!isalpha(text[i])) {
            return 0;  // Not a string
        }
    }

    return 1;  // String
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

void changeArrayValue(char* name, char* value) {
    int i = 0;
    int arraySize = sizeof(array) / sizeof(array[0]);

    // Iterate until the end of the array
    while (i < arraySize) {
        if (strcmp(array[i], name) == 0) {
            // Check if the position is even
            if (i % 2 == 0) {
                // Calculate the next position
                int newPosition = i + 1;

                // Replace the value at the new position
                if (newPosition < arraySize) {
                    strcpy(array[newPosition], value);
                }
            }
            else{
                printf("Variable %s not found",name);
            }
            break;
        }
        i++;
    }
}
int countOccurrences(const char *str, const char *substr) {
    int count = 0;
    const char *ptr = str;
    
    while ((ptr = strstr(ptr, substr)) != NULL) {
        count++;
        ptr += strlen(substr);
    }
    
    return count;
}
void addQuotationMarks(char* str) {
    int len = strlen(str);
    char temp[len + 3]; // Length of original string + 2 (for opening and closing quotation marks) + 1 (for null terminator)

    temp[0] = '"';
    strcpy(&temp[1], str);
    temp[len + 1] = '"';
    temp[len + 2] = '\0';

    strcpy(str, temp);
}
int main(int argc, char *argv[]) {
    
    char line[10000];
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("Crex is a simple programming language designed to do anything! \n");
        printf("Run a file: ./crex <filename>.crf \n");
        printf("Documention can be found at: https://github.com/shourdev/crex#documentation \n");
        return 0;
    }

FILE *file = fopen(argv[1], "r");
 if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    

   

    while (fgets(line, sizeof(line), file)) {
         if (strstr(line, "var") != NULL) {
            char varName[100];
            char value[1000];

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
                   
if (strcmp(value, "add:") == 0 || countOccurrences(value, "add:") == 1) {
    char modifiedValue[MAX_VALUE_LENGTH];
    strcpy(modifiedValue, value);
    removeWord(modifiedValue, "add:");
    stripWhitespace(modifiedValue);

    char beforeComma[MAX_VALUE_LENGTH];  // Use MAX_VALUE_LENGTH for consistent array size
    char afterComma[MAX_VALUE_LENGTH];   // Use MAX_VALUE_LENGTH for consistent array size
    splitString(modifiedValue, beforeComma, afterComma);
  stripWhitespace(modifiedValue);

    if (isStringCheck(beforeComma) == 0) {
        int num1 = atoi(beforeComma);
        int num2 = atoi(afterComma);
        int sum = num1 + num2;

        char sumChar[MAX_VALUE_LENGTH];  // Use MAX_VALUE_LENGTH for consistent array size
        sprintf(sumChar, "%d", sum);
        stripWhitespace(sumChar);

        char finalvalue[MAX_VALUE_LENGTH];  // Use MAX_VALUE_LENGTH for consistent array size
     


addQuotationMarks(sumChar);
   addNameAndValue(varName,sumChar);
    
    }
    else{
     char bc[2000];
     char ac [2000];
     strcpy(bc,beforeComma);
     strcpy(ac,afterComma);
     const char* bv = findNameAndGetNextValue(bc);
      const char* av = findNameAndGetNextValue(ac);
      char bv1[2000];
      char av1[2000];
      strcpy(bv1,bv);
      strcpy(av1,av);

    removeQuotes(bv1);
    removeQuotes(av1);
    int nm = atoi(bv1);
    int nm2 = atoi(av1);
    int sum2 = nm + nm2;
       char sumChar2[MAX_VALUE_LENGTH];  // Use MAX_VALUE_LENGTH for consistent array size
        sprintf(sumChar2, "%d", sum2);
addQuotationMarks(sumChar2);
 addNameAndValue(varName,sumChar2);
    }
    
}
 else {
    if (hasQuotes(value)==0)
    {
addQuotationMarks(value);
stripWhitespace(value);
 addNameAndValue(varName,value);
    }
   else{
     addNameAndValue(varName,value);
   }

     
    }

      
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
   // In work
   removeWord(line,"cin:");
   char opt[2000];
   scanf(" %[^\n]",opt);
  

   changeArrayValue(line,opt);  


  }



       

    }

    fclose(file);
    return 0;
}