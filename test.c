#include <stdio.h>
#include <ctype.h>

int main() {
    char input_string[100]; // Assuming the input will not exceed 100 characters
    scanf("%s", input_string);

    int is_numeric = 1;
    for (char* ptr = input_string; *ptr != '\0'; ptr++) {
        if (!isdigit(*ptr)) {
            is_numeric = 0;
            break;
        }
    }

    printf(is_numeric ? "bye\n" : "hi\n");
    return 0;
}
