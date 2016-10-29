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
    const char * autoOperators = "^/*-+";
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
    int i = 0, j = 0, k = 0, span = 1;
    char * infixAlg = calloc(strlen(alg)+1,sizeof(char));
    char * infixTemp = calloc(strlen(alg)+1,sizeof(char));
    char * infixOperators = rpnconverter_orderOfOperation(alg);
    char * specialOperator = "()";
    
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] != specialOperator[0] && alg[i] != specialOperator[1])
        {
            infixAlg[k] = alg[i];
            k++;
        }
    }
    
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the infixAlg string.
    strcpy(infixTemp, infixAlg);
    while(j<strlen(infixOperators))
    {
        if(infixAlg[i] == infixOperators[j])
        {
            strcpy(infixTemp, infixAlg);
            if(rpnconverter_isValidOperator(infixAlg[i+2]) == 0 && (i+2) < strlen(infixAlg))
            {
                while(rpnconverter_isValidOperator(infixAlg[i+span]) == 0 && i+span < strlen(infixAlg))
                {
                        span++;
                }
                span = span + span - 2;
                for(int l=0;l<span;l++)
                {
                    infixAlg[i+l] = infixTemp[i+l+1];
                }
                infixAlg[i+span-1] = infixOperators[j];
                i=i+span-1;
            }
            else
            {
                infixAlg[i] = infixTemp[i+1];
                infixAlg[i+1] = infixTemp[i];
                i++;
            }
            if((j) != strlen(infixOperators))
            {
                span=1;
                j++;
            }
        }
        if(i<strlen(infixAlg))
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    free(infixTemp);
    free(infixOperators);
    return infixAlg;
};

char *rpnconverter_rpn2infix(char *alg)
{
    //Initialize main variables
    int i = 0, j = 0, span = 1;
    char * rpnAlg = calloc(strlen(alg)+1,sizeof(char));
    char * rpnTemp = calloc(strlen(alg)+1,sizeof(char));
    char * rpnOperators = rpnconverter_orderOfOperation(alg);
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the infixAlg string.
    strcpy(rpnAlg, alg);
    strcpy(rpnTemp, rpnAlg);
    while(j<strlen(rpnOperators))
    {
        if(rpnAlg[i] == rpnOperators[j])
        {
            strcpy(rpnTemp, rpnAlg);
            if(rpnconverter_isValidOperator(rpnAlg[i-2]) == 1)
            {
                while(rpnconverter_isValidOperator(rpnAlg[i-span*2]) == 1 && i-span > 0)
                {
                        span++;
                }
                span = span * 2 - 1;
                for(int l=0;l<span;l++)
                {
                    rpnAlg[i-l] = rpnTemp[i-l-1];
                }
                rpnAlg[i-span] = rpnOperators[j];
                i=i+span-1;
            }
            else
            {
                rpnAlg[i] = rpnTemp[i-1];
                rpnAlg[i-1] = rpnTemp[i];
                i++;
            }
            if((j) != strlen(rpnOperators))
            {
                span=1;
                j++;
            }
        }
        else
        {
            if(i<strlen(rpnAlg))
            {
                i++;
            }
            else
            {
                i=0;
            }
        }
    }
    free(rpnTemp);
    free(rpnOperators);
    return rpnAlg;
};

char *rpnconverter_orderOfOperation(char *alg)
{
    int i, j = 0, l = 0, n = 0, o = 0, q = 0, skip = 0, temp1,temp2;
    char * nullPointer = "0";
    char * specialOperator = "()";
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
        if(alg[i] == specialOperator[0])
        {
            q++;
        }
    }
    if(q > 0)
    {
        char * specialStart = calloc(q,sizeof(int));
        o=0;
        for(i=0;i<strlen(alg);i++)
        {
            if(alg[i] == specialOperator[0])
            {
                specialStart[o] = i;
                o++;
            }
        }

        char * special = calloc(q*2,sizeof(int));
        o=0;
        for(i=0;i<q;i++)
        {
            special[o] = specialStart[i];
            o++;
            n = specialStart[i]+1;
            while(n<strlen(alg))
            {
                if(alg[n] == specialOperator[0])
                {
                    skip++;
                }
                else if(alg[n] == specialOperator[1] && skip != 0)
                {
                    skip--;
                }
                else if(alg[n] == specialOperator[1] && skip == 0)
                {
                    special[o] = n;
                    o++;
                    break;
                }
                n++;
            }
        }
        for(int z=0;z<q*2;z+=2)
        {
            if(special[z] < special[z+2] && special[z+1] > special[z+3])
            {
                temp1 = special[z];
                temp2 = special[z+1];
                special[z] = special[z+2];
                special[z+1] = special[z+3];
                special[z+2] = temp1;
                special[z+3] = temp2;
                z = -2;
            }
        }
        char * tempArray = calloc(strlen(alg),sizeof(char));
        strcpy(tempArray,alg);
        for(int x=0;x<q*2;x+=2)
        {
            for(i=special[x];i<special[x+1];i++)
            {
                if(tempArray[i] == operatorsOne[0])
                {
                    orderArray[j] = tempArray[i];
                    tempArray[i] = nullPointer[0];
                    j++;
                }
            }
            for(i=special[x];i<special[x+1];i++)
            {
                if(tempArray[i] == operatorsTwo[0] || tempArray[i] == operatorsTwo[1])
                {
                    orderArray[j] = tempArray[i];
                    tempArray[i] = nullPointer[0];
                    j++;
                }
            }
            for(i=special[x];i<special[x+1];i++)
            {
                if(tempArray[i] == operatorsThree[0] || tempArray[i] == operatorsThree[1])
                {
                    orderArray[j] = tempArray[i];
                    tempArray[i] = nullPointer[0];
                    j++;
                }
            }
        }
    }
    else
    {
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
    }
    return orderArray;
}

int rpnconverter_isValidOperator(char operator)
{
    int isOperator = 0;
    char * validOperators = "^/*-+";
    
    for(int i=0;i<strlen(validOperators);i++)
    {
        if(validOperators[i] == operator)
        {
            isOperator = 1;
            break;
        }
    }
    
    return isOperator;
}