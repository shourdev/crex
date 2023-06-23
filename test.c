#include <stdio.h>
#include <string.h>
void removeQuotes(char* str) {
    int len = strlen(str);

    // Check if the string is long enough to have quotes
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        // Shift characters to remove the quotes
        for (int i = 1; i < len - 1; i++) {
            str[i - 1] = str[i];
        }
        str[len - 2] = '\0'; // Null-terminate the string
    }
}

int main(){
    char str[] = "hello world";
removeQuotes(str);
printf("%s",str);
}