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
        default :
        break;
    }
    
    char *error = calloc(30+1,sizeof(char));
    if(conAlg == NULL)
    {
        strcpy(error, "Error: Algorithm is NULL");
        return error;
    }
    free(error);
    return conAlg;
}

int rpnconverter_autoselect(char *alg)
{
    if(strlen(alg) <= 0)
    {
        perror("Error: Algorithm Size");
        return 0;
    }
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
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize main variables
    int i = 0, j = 0, span = 1;
    char * infixAlg = rpnconverter_infix2rpn_strip(alg);
    char * infixOperators = rpnconverter_orderOfOperation(alg);
    char * infixTemp = calloc(strlen(alg)+1,sizeof(char));
    
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the infixAlg string.
    //Assuming that the required change isnt just simply swapping the operator and an operand find the correct span for displacement
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
    free(error);
    free(infixTemp);
    free(infixOperators);
    return infixAlg;
};

char *rpnconverter_infix2rpn_strip(char *alg)
{
    //Initialize main variables
    int i = 0, j = 0;
    char * infixAlg = calloc(strlen(alg)+1,sizeof(char));
    char * specialOperator = "()";
 
    //Remove parentheses from the algorithm
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] != specialOperator[0] && alg[i] != specialOperator[1])
        {
            infixAlg[j] = alg[i];
            j++;
        }
    }
    
    return infixAlg;
};

char *rpnconverter_rpn2infix(char *alg)
{
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize main variables
    int i = 0, span = 1, p = 0, r=0, s=0, n=0;
    int numOperators = rpnconverter_rpn2infix_countoperators(alg);
    char * rpnOperators = "^/*-+";
    //Continue initializing variables
    char * rpnAlg = calloc(((int)strlen(alg)+(numOperators*2)+1),sizeof(char));
    char * rpnTemp = calloc(((int)strlen(alg)+(numOperators*2)+1),sizeof(char));
    char * brackets = "()";
    
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the infixAlg string.
    //Assuming that the required change isnt just simply swapping the operator and an operand find the correct span for displacement
    strcpy(rpnAlg, alg);
    strcpy(rpnTemp, rpnAlg);
    for(i=0;i<strlen(rpnAlg);i++)
    {
        for(int k=0;k<strlen(rpnOperators);k++)
        {
            if(rpnAlg[i] == rpnOperators[k])
            {
                strcpy(rpnTemp, rpnAlg);
                if(rpnconverter_isValidOperator(rpnAlg[i-2]) == 0 && rpnAlg[i-1] == brackets[1])
                {
                    span = 1;
                    r=rpnconverter_rpn2infix_span(i,span,rpnAlg);
                    r++;
                    span = 0;
                    if(rpnAlg[i-r] == brackets[1])
                    {
                        span++;
                        while(span > 0)
                        {
                            s++;
                            if(rpnAlg[i-r-s] == brackets[1])
                            {
                                span++;
                            }
                            else if(rpnAlg[i-r-s] == brackets[0])
                            {
                                span--;
                            }
                        }
                        rpnAlg[i-r-s] = brackets[0];
                        while(s>0)
                        {
                            rpnAlg[i-r-s+1] = rpnTemp[i-r-s];
                            s--;
                        }
                    }
                    else
                    {
                        rpnAlg[i-r] = brackets[0];        
                    }
                    rpnAlg[i-r+1] = rpnTemp[i-r];
                    r--;
                    rpnAlg[i-r+1] = rpnTemp[i];
                    while(r>0)
                    {
                        rpnAlg[i-r+2] = rpnTemp[i-r];
                        r--;
                    }
                    rpnAlg[i+2] = brackets[1];
                }
                else if(rpnconverter_isValidOperator(rpnAlg[i-2]) == 0 && rpnAlg[i-2] != brackets[1])
                {
                    rpnAlg[i-2] = brackets[0];
                    rpnAlg[i-1] = rpnTemp[i-2];
                    rpnAlg[i+1] = rpnTemp[i-1];
                    rpnAlg[i+2] = brackets[1];    
                }
                else
                {
                    span = 2;
                    r = rpnconverter_rpn2infix_span(i,span,rpnAlg);
                    rpnAlg[i-r] = brackets[0];
                    while(r>1)
                    {
                        rpnAlg[i-r+1] = rpnTemp[i-r];
                        r--;
                    }
                    rpnAlg[i+1] = rpnTemp[i-1];
                    rpnAlg[i+2] = brackets[1];
                }
                p=0;
                for(n = i+1;n<strlen(rpnTemp);n++)
                {
                    p++;
                    rpnAlg[i+2+p] = rpnTemp[n];
                }
                i+=2;
            }
        }
    }
    free(error);
    free(rpnTemp);
    return rpnAlg;
};

char *rpnconverter_rpn2infix_getoperators(char *alg)
{
    int j=0;
    int numOperators = rpnconverter_rpn2infix_countoperators(alg);
    char * rpnAlg = calloc(numOperators+1,sizeof(char));
    
    for(int i=0;i<strlen(alg);i++){
        switch(alg[i]) {
          case '^' :
             rpnAlg[j] = '^';
             j++;
             break;
          case '/' :
             rpnAlg[j] = '/';
             j++;
          case '*' :
             rpnAlg[j] = '*';
             j++;
             break;
          case '-' :
             rpnAlg[j] = '-';
             j++;
             break;
          case '+' :
             rpnAlg[j] = '+';
             j++;
             break;
       }
    }
    
    return rpnAlg;
};

int rpnconverter_rpn2infix_span(int i, int span, char *rpn)
{
    //Initialize main variables
    int j=0,k=span;
    char * brackets = "()";
    //Calculate the span between chosen brackets
    while(rpnconverter_isValidOperator(rpn[i-span]) == 0 && rpn[i-span] == brackets[1])
    {
        span++;
    }
    span-=k;
    j=span+k-1;
    while(span > 0)
    {
        j++;
        if(rpn[i-j]==brackets[0])
        {
            span--;  
        }
        else if(span >= 1 && rpn[i-j]==brackets[1])
        {
            span++;
        }
    }

    return j;
};

int rpnconverter_rpn2infix_countoperators(char *alg)
{
    //Initialize main variables
    int i = 0, j = 0, countOperators = 0;
    char * rpnOperators = "^/*-+";
    //Get number of Operators
    for(i=0;i<strlen(alg);i++)
    {
        for(j=0;j<strlen(rpnOperators);j++)
        {
            if(alg[i] == rpnOperators[j])
            {
                countOperators++;
            }
        }
    }
    return countOperators;
};

char *rpnconverter_orderOfOperation(char *alg)
{
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize Variables
    int i, j = 0, l = 0, n = 0, o = 0, q = 0, skip = 0, temp1,temp2;
    char * nullPointer = "0";
    char * specialOperator = "()";
    char * operators = "^/*-+";
    char * operatorsOne = "^";
    char * operatorsTwo = "/*";
    char * operatorsThree = "-+";
    
    //Get number of Operators to properly size orderArray
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
    //Check for Parentheses
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] == specialOperator[0])
        {
            q++;
        }
    }
    //If Parentheses found modify order of operation accordingly
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
        char * tempArray = calloc(strlen(alg)+1,sizeof(char));
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
        free(tempArray);
        free(special);
        free(specialStart);
    }
    //If Parentheses not found then use standard order of operation
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
    free(error);
    return orderArray;
};

int rpnconverter_isValidOperator(char operator)
{
    //Initialize Variables
    int isOperator = 0;
    char * validOperators = "^/*-+";
    //Loop through valid operators to check if char is a valid operator
    for(int i=0;i<strlen(validOperators);i++)
    {
        if(validOperators[i] == operator)
        {
            isOperator = 1;
            break;
        }
    }
    
    return isOperator;
};