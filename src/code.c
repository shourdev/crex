#include <stdio.h> 
 #include <stdlib.h> 
enum types{
 STRING,
INT,
FLOAT
};
struct Var{
 enum types type;
 union 
  {
 int intvalue;
 float   floatvalue;
char* stringvalue;
  } value;
};
char*  main(){ 
   struct Var * test  = malloc(sizeof(struct Var));
     test ->type = STRING;
         test ->value.stringvalue =  "hi \n";
if (test->type == STRING){
printf("%s",test->value.stringvalue);
}
if (test->type == INT){
printf("%d",test->value.intvalue);
}
if (test->type == FLOAT){
printf("%f",test->value.floatvalue);
}
printf("also hi \n");
}
