## RPNConverter

RPNConverter allows the conversion of Reverse Polish Notation(RPN) to and from Infix Notation.
* Simple Single Function Design.
* Test Driven Development.

## API Reference

RPNConverter centers around the use of one main function that accepts a single algorithm as a string. The main function auto selects the currently used notation and then outputs the resepective opposite notation.

Valid Notation Syntax
* Operands include only lowercase letters: a, b, ..., z
* Operators include (,),^, /, *, -, +
* Does not support the unary negation operator

```c
rpnconverter("a+b"); //outputs "ab+"
```

## Tests

This library was built using test driven development and Check - Unit Testing Framework for C (https://libcheck.github.io/check/).