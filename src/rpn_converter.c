#include "rpn_converter.h"

char *rpnconverter(char *alg)
{
    //Initialize main variables
    const char * operators = "-+";
    char * newAlg;
    int operatorFound;
    //Change the size of newAlg to match that of alg and exit with error code if unsuccessful.
    if((newAlg = malloc(strlen(alg)+1)) != NULL){
        newAlg[0] = '\0';
    } else {
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