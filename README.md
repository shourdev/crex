### Download
Not done yet.
### Documentation
## Hello world
```
cout("Hello World");
```
## Contents
[Data](#data) <br>
[Expressions](#expressions) <br>
[Conditionals](#conditionals) <br>
[Loop](#loops) <br>
[Functions](#functions)
# Data
In crex to store data we can use a variable and a list. A variable is a named memory location, you can store 5 types of data in it those are: <br> int (integers), <br> float (decimals),<br> strings (text), <Br>bool (true or false) and <br> structs <br> We will talk about structs later on. <br>
# Variables
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
# Lists
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
# Accessing variables and lists 
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