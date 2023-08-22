#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum DataType {
    INT,
    FLOAT,
    STRING,
    
};

struct DynamicValue {
    enum DataType type;
    union {
        int intValue;
        float floatValue;
        char* stringValue;

    } value;
};

void createStringDynamicValue(struct DynamicValue *value, const char* str) {
    value->type = STRING;
    value->value.stringValue = malloc(strlen(str) + 1);  // +1 for null terminator
    strcpy(value->value.stringValue, str);
}

void freeDynamicValue(struct DynamicValue *value) {
    if (value->type == STRING) {
        free(value->value.stringValue);
    }
}
struct DynamicValue *test(struct DynamicValue *inp){
inp->type = INT;
return inp;
}
int main() {
    struct DynamicValue strValue;
    createStringDynamicValue(&strValue, "Hello, world!");
 struct DynamicValue *strval2;
 strval2 =    test(&strValue);

switch (strval2->type)
{
case STRING:
    printf("string");
    break;
case INT:
    printf("int");
    break;
case FLOAT:
    printf("float");
    break;
default:
    break;
}
switch (strValue.type)
{
case STRING:
    printf("string");
    break;
case INT:
    printf("int");
    break;
case FLOAT:
    printf("float");
    break;
default:
    break;
}
    freeDynamicValue(&strValue);

    return 0;
}





