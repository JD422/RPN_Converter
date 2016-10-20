#include "rpnconverter.h"

char *rpnconverter(char *alg)
{
    char * newAlg;
    //Change the size of newAlg to match that of alg and exit with error code if unsuccessful.
    if((newAlg = malloc(strlen(alg)+1)) != NULL)
    {
        newAlg[0] = '\0';
    } 
    else 
    {
        exit(1);
    }
    switch(rpnconverter_autoselect(alg))
    {
        case 1 :
        newAlg = rpnconverter_rpn2infix(alg);
        break;
        case 2 :
        newAlg = rpnconverter_infix2rpn(alg);
        break;
    }
    return newAlg;
}

int rpnconverter_autoselect(char *alg)
{
    //Initialize main variables
    const char * operators = "-+";
    int operandFound = 0;
    //Loop through all characters from the input string and check them against the operators array.
    //If 2 or more operands are found back to back then assume notation is RPN else assume notation is Infix.
    for(int i=0;i<strlen(alg);i++)
    {
        operandFound++;
        for(int j=0;j<strlen(operators);j++)
        {
            if(alg[i] == operators[j])
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
    const char * operators = "-+";
    char * newAlg;
    int operatorFound;
    //Change the size of newAlg to match that of alg and exit with error code if unsuccessful.
    if((newAlg = malloc(strlen(alg)+1)) != NULL)
    {
        newAlg[0] = '\0';
    } 
    else 
    {
        exit(1);
    }
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the newAlg string.
    for(int i=0;i<strlen(alg);i++)
    {
        operatorFound = 0;
        for(int j=0;j<strlen(operators);j++)
        {
            if(alg[i] == operators[j])
            {
                operatorFound = 1;
                newAlg[i] = alg[i+1];
                newAlg[i+1] = alg[i];
                i++;
            }
        }
        if(operatorFound == 0)
        {
            newAlg[i] = alg[i];
        }
    }
    return newAlg;
};

char *rpnconverter_rpn2infix(char *alg)
{
    //Initialize main variables
    const char * operators = "-+";
    char * newAlg;
    int operatorFound;
    //Change the size of newAlg to match that of alg and exit with error code if unsuccessful.
    if((newAlg = malloc(strlen(alg)+1)) != NULL)
    {
        newAlg[0] = '\0';
    } 
    else 
    {
        exit(1);
    }
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the newAlg string.
    for(int i=0;i<strlen(alg);i++)
    {
        operatorFound = 0;
        for(int j=0;j<strlen(operators);j++)
        {
            if(alg[i] == operators[j])
            {
                operatorFound = 1;
                newAlg[i] = alg[i-1];
                newAlg[i-1] = alg[i];
                i++;
            }
        }
        if(operatorFound == 0)
        {
            newAlg[i] = alg[i];
        }
    }
    return newAlg;
};

char *rpnconverter_orderOfOperation(char *alg)
{
    int i;
    char * orderArray = malloc(1);
    char * operatorsOne = "^";
    char * operatorsTwo = "/*";
    char * operatorsThree = "-+";
    strcpy(orderArray, "0");
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == operatorsOne[0])
        {
            orderArray = realloc(orderArray, strlen(orderArray)+1);
            orderArray[strlen(orderArray)] = alg[i];
        }
    }
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == operatorsTwo[0] || alg[i] == operatorsTwo[1])
        {
            orderArray = realloc(orderArray, strlen(orderArray)+1);
            orderArray[strlen(orderArray)] = alg[i];
        }
    }
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == operatorsThree[0] || alg[i] == operatorsThree[1])
        {
            orderArray = realloc(orderArray, strlen(orderArray)+1);
            orderArray[strlen(orderArray)] = alg[i];
        }
    }
    memmove(orderArray, orderArray+1, strlen(orderArray+1) + 1);
    return orderArray;
}