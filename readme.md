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
#### Infix2RPN_Strip Function
    This function takes a string with an algorithm written in Infix Notation and strips the parentheses from it.
```c
rpnconverter_infix2rpn_strip("(c+d)/(e-f)"); //outputs "c+d/e-f"
```
#### Infix2RPN_GetOperatorArray Function
    This function takes a string with an algorithm written in Infix Notation and returns an array of all the operators used while adjusting for the order of operation while handling changes due to parentheses.
```c
rpnconverter_infix2rpn_getoperatorarray("(a*b^((c+d)/(e-f))^g)"); //outputs "+-/^^*"
```
#### Infix2RPN_OrderOfOperation Function
    This function takes a starting index, a span, and a string with an algorithm written in Infix Notation. It returns an array of operators used according to order of operation. This function will ignore parentheses.
```c
rpnconverter_infix2rpn_orderofoperation(0,13,"a*b^c+d/e-f^g"); //outputs "^^*/+-"
```
#### Infix2RPN_OrderOfOperation_CheckParentheses Function
    This function takes a string with an algorithm written in Infix Notation with parentheses and returns the number of pairs of parentheses.
```c
rpnconverter_infix2rpn_orderofoperation_checkparentheses("(a*b^((c+d)/(e-f))^g)"); //outputs 4
```
#### RPN2Infix Function
    This function takes a string with an algorithm written in RPN and converts it directly to Infix Notation with Parentheses.
```c
rpnconverter_rpn2infix("ab+"); //outputs "(a+b)"
```
#### RPN2Infix_GetOperators Function
    This function takes a string with an algorithm written in RPN and returns an array of the operators used in the notation.
```c
rpnconverter_rpn2infix_getoperators("ag+ba-c+cedf^*+^*"); //outputs "+-+^*+^*"
```
#### RPN2Infix_Span Function
    This function takes a starting index, a span, and a string with an algorithm written in RPN and returns the span between parentheses.
```c
rpnconverter_rpn2infix_span(14,2,"((a/b)+(c^d))f+"); //outputs 14
```
#### Autoselect Function
    This function accepts a string with an algorithm in either RPN or Infix Notation and returns an identifier of 2 to represent that the inputted algorithm is in Infix Notation or 1 if the inputted algorithm is in RPN.
```c
rpnconverter_autoselect("a+b"); //outputs 2 for infix
rpnconverter_autoselect("ab+"); //outputs 1 for rpn
```
#### CountOperators Function
    This function accepts a string with an algorithm and returns the number of operators.
```c
rpnconverter_countoperators("ab+cd*-"); //outputs 3
```
#### IsValidOperator Function
    This function accepts a character and returns a one if it is a valid operator or a zero if it is not.
```c
rpnconverter_isvalidoperator("+"); //outputs 1
rpnconverter_isvalidoperator("a"); //outputs 0
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
valgrind --tool=memcheck --leak-check=full ./rpnconverter 
```