#include <stdlib.h>
#include <string.h>
#ifndef RPNConverter
#define RPNConverter

int rpnconverter_autoselect(char *alg);
char *rpnconverter_infix2rpn(char *alg);
char *rpnconverter_rpn2infix(char *alg);

#endif