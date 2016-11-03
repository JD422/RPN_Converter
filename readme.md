## RPNConverter

RPNConverter allows the conversion of Reverse Polish Notation(RPN) to and from Infix Notation.
* Simple Single Function Design.
* Test Driven Development.

## Why

This project was created at the request of Pillar Technology and is based off an online exercise found [here](http://www.spoj.com/problems/ONP/). The ultimate goal of this project is to create a C library that can be used to convert an algorithm between Reverse Polish Notation and Infix Notation. This conversion must also be able handle the use of parentheses which can have the affect of changing the order of operation for operators in Infix Notation.

## How

The basic strategy used to develop this project was test driven development. To ellaborate, I started by creating a simple test and function to convert the infix algorithm "a+b" into its rpn counterpart "ab+". I then wrote the test and function to do the inverse and convert "ab+" to "a+b". Each test that I wrote to solve became progressively more complex to handle the specific nuances that was required by the converter. Depending upon the specific nuance covered by the test I either created a new function to handle the nuance or I made modifications directly to the existing functions. Once the main elements were completed I created a single function that would combine all the functionality into an easy to use function.

## Environment

* Ubuntu 14.04
* GNU GCC(c99)
* GNU Make
* Check Unit Testing Framework
* Valgrind
* Git

## Installation

To install this library
* Download and Unzip
* Copy rpnconverter.c and rpnconverter.h from the src folder
* Paste into the folder where you are going to use the code
* Add the following to your code where needed changing {SRC_DIR} to point to the folder containing rpnconverter.c and rpnconverter.h 
```c
#include "{SRC_DIR}/rpnconverter.h"
```

## Assumptions

It is assumed that all returns for functions, excluding the Autoselect Function, will be stored in a variable that will be freed using the proper method upon completion of use. This will keep the library from causing a memory leak. As an example

```c
#include <stdio.h>
#include "{SRC_DIR}/rpnconverter.h"

int main( ) {

   char str[100];

   printf( "Enter Algorithm: ");
   scanf("%s", str);

   char * alg = rpnconverter(str);
    
   printf( "\nConverted Algorithm: %s \n", alg);

   free(alg);
    
   return 0;
}
```

## API Reference

RPNConverter centers around the use of one main function that accepts a single algorithm as a string. The main function auto selects the currently used notation and then outputs the resepective opposite notation.

Valid Notation Syntax
* Operands include only lowercase letters: a, b, ..., z
* Operators include ^, /, *, -, +
* Parentheses, (), can be used to surround groups of operands and operators to indicate
the intended order in which operations are to be performed only in Infix Notation
* Does not support the unary negation operator

```c
rpnconverter("a+b"); //outputs "ab+"
```

## Low Level API Access

#### Infix2RPN Function
    This function takes a string with an algorithm written in Infix Notation and converts it directly to RPN.
```c
rpnconverter_infix2rpn("a+b"); //outputs "ab+"
```
#### RPN2Infix Function
    This Function takes a string with an algorithm written in RPN and converts it directly to Infix Notation with Parentheses.
```c
rpnconverter_rpn2infix("ab+"); //outputs "(a+b)"
```
#### Autoselect Function
    This function accepts a string with an algorithm in either RPN or Infix Notation and returns an identifier of 2 to represent that the inputted algorithm is in Infix Notation or 1 if the inputted algorithm is in RPN.
```c
rpnconverter_autoselect("a+b"); //outputs 2 for infix
rpnconverter_autoselect("ab+"); //outputs 1 for rpn
```
#### OrderOfOperation Function
    This function accepts a string with an algorithm in Infix Notation and returns a string of the operators from the inputted string in the correct order of operation. This algorithm also automatically handles change of order of operation due to parentheses.
```c
rpnconverter_orderOfOperation("(a*b^((c+d)/(e-f))^g)"); //outputs "+-/^^*"
```

## Tests

This library was built using test driven development and Check - Unit Testing Framework for C (https://libcheck.github.io/check/).

To access the tests you need to
* Download and Unzip to git repository
* Enter the folder from the command line


To run the tests for this library
```c
make test
```

To clean up the directory
```c
make clean
```

Valgrind was used to test for memory leaks using the following command
```c
valgrind ./rpnconverter --leak-check=full
```