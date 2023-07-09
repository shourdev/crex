#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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


int main() {
    const char* inputString = "hi,bye,lol,";
    char* formattedString = getFormattedString(inputString);
    
    printf("%s\n", formattedString);
    
    free(formattedString);  // Don't forget to free the memory
    
    return 0;
}