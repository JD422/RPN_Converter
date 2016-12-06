#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifndef RPNConverter
#define RPNConverter

char *rpnconverter(char *alg);
char *rpnconverter_infix2rpn(char *alg);
char *rpnconverter_infix2rpn_strip(char *alg);
char *rpnconverter_rpn2infix(char *alg);
int rpnconverter_rpn2infix_countoperators(char *alg);
int rpnconverter_rpn2infix_span(int i, int span, char *rpnAlg);
char *rpnconverter_orderOfOperation(char *alg);
int rpnconverter_autoselect(char *alg);
int rpnconverter_isValidOperator(char operator);

#endif