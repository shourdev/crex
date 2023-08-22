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
   struct Var * f  = malloc(sizeof(struct Var));
     f ->type = STRING;
         f ->value.stringvalue =  "h \n";
   struct Var * t  = malloc(sizeof(struct Var));
     t ->type = STRING;
         t ->value.stringvalue =  "hello world";
if (f->type == STRING){
printf("%s",f->value.stringvalue);
}
if (t->type == STRING){
printf("%s",t->value.stringvalue);
}
}
