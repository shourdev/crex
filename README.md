### Download
Not done yet.
### Documentation
## Hello world
```
cout("Hello World");
```
# Contents
[Syntax](#syntax) <br>
[Data](#data) <br>
[Expressions](#expressions) <br>
[Conditionals](#conditionals) <br>
[Loop](#loops) <br>
[Functions](#functions)
# Syntax
Syntax are the rules that define how the statements and expressions of the language should be. <br>
All this means is that it's like the grammer of the language. <br>
Here is the basic syntax <br>
Statements and expressions(individual) are terminated with a ";" <br>
```
cout("hi");
```
Blocks can't be used alone, they only work with functions,ifs,structs,loops etc. They end with a #
```
if (2+2==4)
cout("true");
#
```

# Data
In crex to store data we can use a variable and a list. A variable is a named memory location, you can store 5 types of data in it those are: <br> int (integers), <br> float (decimals),<br> strings (text), <Br>bool (true or false) and <br> structs <br> We will talk about structs later on. <br>
## Variables
To make an int variable
```
int myvar = 2;
```
```
int myvar2 = 2+2;
```
The first example makes an int called as myvar and store 2 in it and in the second we have myvar2 which stores the value of 2+2 which is 4 <br>
For float
```
float myvar = 2.2;
```
For strings
```
string myvar = "hello!";
```
and for bool
```
bool myvar = true;
```
or 
```
bool myvar2 = false;
```
Structs will be in the [structs]() <br>
## Lists
Lists is a sequence of several variables grouped under one name called the list <br>
Int lists
```
int[] mylist = [2,4];
```
This stores 2 and 4. Lists index starts from 0 so 2 is stored in the 0 index while 4 in the 1 index. <br>
Float
```
float[] mylist = [2.2,3.4];
```
String
```
string[] mylist = ["hi","hello"];
```
## Accessing variables and lists 
Variables can be accessed using their name, while to access list you use the name and [] where you mention the index, for example to access
```
int[] numbers = [2,3];
```
use 
```
numbers[0];
```
This will refer to the data in the 0th index which is 2 (keep in mind the index starts at 0 not 1!) <br>
Obviously just writing the name of the variable or doing numbers[0] won't do anything they are the part of *expressions* which will be in the next section, and these expressions can be passed to functions to do something out of their data. <br>
If you want to output the values you can do like this.
```
cout(myvar);
cout(mylist[0]);
```
I will go in an order so these functions like cout shall be in the functions chapter but cout is a pretty common function, so knowing it from now can benefit you, in the next section.
## Assignment
To change value of a variable just write the name = the new data.
```
int t;
t = 1
```
(Note, when you don't give any =, strings will be null, int will be 0 and float will be 0.0) <br>
Here we reassign the data of t as 1 <br>
For lists
```
int[] list = [2,3];
list[0] = 1;
```
this changes 2 to 1
# Expressions
Expressions are anything that will execute and turns into a value, like 2+2 is an expression test+test2 is an expression. In crex we have 3 types of expressions they are arithmetic,relational and logical. Expressions is made up of 
- Literals: are anything like int data (2,3,43 etc) string literals are "hi", "hello" etc float are 2.2,2.4 <Br>
- Variables: as you know was in the last section <br>
- Operators: like + for addition - for subtraction * for multiplication etc <br>
- Functions calls: are calling functions like we called cout() <br>
## Types of expressions
### Arithmetic
Addition,subtraction,multiplication and division <br>
Addition
```
2+2
```
Multiplication
```
2*2
```
Subtraction
```
2-2
```
Division
```
2/2
```
### Relational
They produce output as true or false <br>
Evaluates to true is 2+2 is equal to 4
```
2+2==4
```
Evaluates to true is 2+2 is not equal to 5
```
2+2!=5
```
Evaluates to true is 2 is greater than 1
```
2>1
```
Evaluates to true is 2 is smaller than 4
```
2<4
```
### Logical 
They combine relational expressions. <br>
Evaluates to true if 2+2 is 4 and 3+3 is 6
```
2+2==4 && 3+3==6
```
Evaluates to true if either of the two expressions are true
```
2+2==4 || 3+3 == 9
```
## Misc stuff
Assignment of variables (when you change value of a variable) is an expression in crex like languages like c. <br>
# Conditionals
Conditionals in crex are if and else statements. <br>
First use the if keyword followed by a ( the expression, which must evaluate to 1 or true, then followed by the ) if the condition is true or 1 the if block will run if not then the else block will run and if their is any other if that matches the condition that will run. 
```
if (2+2==4)
cout("Yes true");
#
if (2+2==5)
cout("HOW!");
#
else
cout("Maths is broken or something!");
#
```
In this code if 2+2 is 4 it will print yes true if 2+2 is 5 it will print "HOW!" and if none of these if are evaluated than the else will be run

