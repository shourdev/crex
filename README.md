### crex
A programming language
### Documentation
[Syntax](#basic-syntax) <br>
[Standard-lib](#standard-lib) <br>
[Data-Types](#data-types)
### Basic syntax
Back to [Documentation](#documentation)
```
cout: "Hello, enter your name:"
var name = ""
cin: name
cout: "Welcome,"
cout: name
exit:
```
This code uses cout: to print the line "hello, enter your name:" than defines a variable called name, then it uses cin to ask for input and set it's variable to name, then it uses cout again to print "welcome," and then uses cout one last time to print the value of the variable "name"
### Data Types
Back to [Documentation](#documentation) <br>
Variables:
```
var test = "hi"
```
Note: numbers don't need "" 
```
var test2 = 1
```
Output a data type <br>
Variables:
```
var test = "hi"
cout: test
```

### Standard Lib
Back to [Documentation](#documentation) <br>
This section will have the different functions of the standard lib. <br>
Functions: <br>
[I/O](#io) <br>
[Maths](#maths) <br>
[Misc](#misc)

### io
This section is for I/O or input and output in the std lib.
# cout:
Back to [Documentation](#documentation) <br>
cout: is a function in the I/O module of crex's std lib which is used to output stuff to the console. <br>
```
var test = "hi"
cout: "hello world"
cout: test
```
This code first demonstrates printing "hello world" the second cout prints the data of the variable test defined at the first line. 
```
cout: 1
```
Numbers don't need ""
# cin:
Cin is a std lib function from i/o module which i used to read user input.
```
var input = ""
cin: input
cout: input
```
This code makes an empty variable than uses cin to ask for input and then uses cout to print it to the console.
### maths
This section is for the maths module in the std lib.
# add:
add: is a std lib function from the maths module, used to add.
Use with variable
```
var nm = 1
var nm2 = 2
var sum = add:nm,nm2
cout: sum
```
Use without variable
```
var sum = add:1,2
cout: sum
```
The sum: function is a function which is to be used with a variable and won't work without it.
### misc
Misc functions of the stdlib
# exit:
```
cout: "hi"
exit:
```
Used to exit.

