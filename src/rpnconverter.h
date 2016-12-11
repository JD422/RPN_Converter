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
char *rpnconverter_rpn2infix_getoperators(char *alg);
int rpnconverter_countoperators(char *alg);
int rpnconverter_rpn2infix_span(int i, int span, char *rpnAlg);
char *rpnconverter_infix2rpn_getOperatorArray(char *alg);
char *rpnconverter_infix2rpn_orderOfOperation(int start, int span, char *alg);
int rpnconverter_infix2rpn_orderOfOperation_checkParentheses(char *alg);
int rpnconverter_autoselect(char *alg);
int rpnconverter_isValidOperator(char operator);

#endif