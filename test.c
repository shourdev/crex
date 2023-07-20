#include <stdio.h>

int main() {
    float floatValue = 42.75;
    int integerValue;

    // Convert the float to an integer
    integerValue = (int)floatValue;

    printf("Float value: %f\n", floatValue);
    printf("Integer value: %d\n", integerValue);

    return 0;
}
