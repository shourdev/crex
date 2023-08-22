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
         test ->value.stringvalue =  "hello \n";
   struct Var * test2  = malloc(sizeof(struct Var));
     test2 ->type = FLOAT;
         test2 ->value.floatvalue =  2.2;
   struct Var * test3  = malloc(sizeof(struct Var));
     test3 ->type = INT;
         test3 ->value.intvalue =  2;
if (test->type == STRING){
printf("%s",test->value.stringvalue);
}
if (test->type == INT){
printf("%d",test->value.intvalue);
}
if (test->type == FLOAT){
printf("%f",test->value.floatvalue);
}
if (test2->type == STRING){
printf("%s",test2->value.stringvalue);
}
if (test2->type == INT){
printf("%d",test2->value.intvalue);
}
if (test2->type == FLOAT){
printf("%f",test2->value.floatvalue);
}
printf("\n");
if (test3->type == STRING){
printf("%s",test3->value.stringvalue);
}
if (test3->type == INT){
printf("%d",test3->value.intvalue);
}
if (test3->type == FLOAT){
printf("%f",test3->value.floatvalue);
}
}
