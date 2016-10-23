#include "rpnconverter.h"

char *rpnconverter(char *alg)
{
    char * conAlg = NULL;
    switch(rpnconverter_autoselect(alg))
    {
        case 1 :
        conAlg = rpnconverter_rpn2infix(alg);
        break;
        case 2 :
        conAlg = rpnconverter_infix2rpn(alg);
        break;
    }
    return conAlg;
}

int rpnconverter_autoselect(char *alg)
{
    //Initialize main variables
    const char * autoOperators = "-+";
    int operandFound = 0;
    //Loop through all characters from the input string and check them against the operators array.
    //If 2 or more operands are found back to back then assume notation is RPN else assume notation is Infix.
    for(int i=0;i<strlen(alg);i++)
    {
        operandFound++;
        for(int j=0;j<strlen(autoOperators);j++)
        {
            if(alg[i] == autoOperators[j])
            {
                operandFound = 0;
                break;
            }
        }
        if(operandFound >=2)
        {
            return 1; // 1 represents Reverse Polish Notation
        }
    }
    return 2; // 2 represents Infix Notation
}

char *rpnconverter_infix2rpn(char *alg)
{
    //Initialize main variables
    char * infixAlg = calloc(strlen(alg)+1,sizeof(char));
    char * infixOperators = rpnconverter_orderOfOperation(alg);
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the newAlg string.
    for(int j=0;j<strlen(infixOperators);j++)
    {
        for(int i=0;i<strlen(alg);i++)
        {
            if(alg[i] == infixOperators[j])
            {
                infixAlg[i] = alg[i+1];
                infixAlg[i+1] = alg[i];
                i++;
            }
            else
            {
                infixAlg[i] = alg[i];
            }
        }
    }
    free(infixOperators);
    return infixAlg;
};

char *rpnconverter_rpn2infix(char *alg)
{
    //Initialize main variables
    char * rpnAlg = calloc(strlen(alg)+1,sizeof(char));
    char * rpnOperators = rpnconverter_orderOfOperation(alg);
    
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the newAlg string.
    for(int j=0;j<strlen(rpnOperators);j++)
    {
        for(int i=0;i<strlen(alg);i++)
        {
            if(alg[i] == rpnOperators[j])
            {
                rpnAlg[i] = alg[i-1];
                rpnAlg[i-1] = alg[i];
                i++;
            }
            else
            {
                rpnAlg[i] = alg[i];
            }
        }
    }
    free(rpnOperators);
    return rpnAlg;
};

char *rpnconverter_orderOfOperation(char *alg)
{
    int i, j = 0, l = 0;
    char * operators = "^/*-+";
    char * operatorsOne = "^";
    char * operatorsTwo = "/*";
    char * operatorsThree = "-+";
    
    for(i=0;i<strlen(alg);i++)
    {
        for(int k=0;k<strlen(operators);k++)
        {
            if(alg[i] == operators[k])
            {
                l++;
            }
        }
    }
    
    char *orderArray = calloc(l+1, sizeof(char));
    
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == operatorsOne[0])
        {
            orderArray[j] = alg[i];
            j++;
        }
    }
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == operatorsTwo[0] || alg[i] == operatorsTwo[1])
        {
            orderArray[j] = alg[i];
            j++;
        }
    }
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == operatorsThree[0] || alg[i] == operatorsThree[1])
        {
            orderArray[j] = alg[i];
            j++;
        }
    }
    return orderArray;
}