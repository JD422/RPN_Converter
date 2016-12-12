#include "rpnconverter.h"

char *rpnconverter(char *alg)
{
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize Variables
    char * conAlg = NULL;
    //Apply Switch Case To Autoselect Function And Then Run Either RPN2Infix Or Infix2RPN
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
    char * infixOperators = rpnconverter_infix2rpn_getoperatorarray(alg);
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
            if(rpnconverter_isvalidoperator(infixAlg[i+2]) == 0 && (i+2) < strlen(infixAlg))
            {
                while(rpnconverter_isvalidoperator(infixAlg[i+span]) == 0 && i+span < strlen(infixAlg))
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
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize main variables
    int i = 0, j = 0;
    char *infixAlg = calloc(strlen(alg)+1,sizeof(char));
    char *specialOperator = "()";
 
    //Remove parentheses from the algorithm
    for(i=0;i<strlen(alg);i++)
    {
        if(alg[i] != specialOperator[0] && alg[i] != specialOperator[1])
        {
            infixAlg[j] = alg[i];
            j++;
        }
    }
    free(error);
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
    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, span = 1;
    int numOperators = rpnconverter_countoperators(alg);
    char * rpnOperators = rpnconverter_rpn2infix_getoperators(alg);
    //Continue initializing variables
    char * rpnAlg = calloc(((int)strlen(alg)+(numOperators*2)+1),sizeof(char));
    char * rpnTemp = calloc(((int)strlen(alg)+(numOperators*2)+1),sizeof(char));
    char * brackets = "()";
    
    //Loop through all characters from the input string and check them against the operators array.
    //If an Operator is found then save the character in its corrected place in the infixAlg string.
    //Assuming that the required change isnt just simply swapping the operator and an operand find the correct span for displacement
    strcpy(rpnAlg, alg);
    strcpy(rpnTemp, rpnAlg);
    while(i<strlen(rpnAlg))
    {
        if(rpnAlg[i] == rpnOperators[k])
        {
            strcpy(rpnTemp, rpnAlg);
            if(rpnconverter_isvalidoperator(rpnAlg[i-2]) == 0 && rpnAlg[i-1] == brackets[1])
            {
                span = 1;
                l=rpnconverter_rpn2infix_span(i,span,rpnAlg);
                l++;
                span = 0;
                if(rpnAlg[i-l] == brackets[1])
                {
                    span++;
                    while(span > 0)
                    {
                        m++;
                        if(rpnAlg[i-l-m] == brackets[1])
                        {
                            span++;
                        }
                        else if(rpnAlg[i-l-m] == brackets[0])
                        {
                            span--;
                        }
                    }
                    rpnAlg[i-l-m] = brackets[0];
                    while(m>0)
                    {
                        rpnAlg[i-l-m+1] = rpnTemp[i-l-m];
                        m--;
                    }
                }
                else
                {
                    rpnAlg[i-l] = brackets[0];        
                }
                rpnAlg[i-l+1] = rpnTemp[i-l];
                l--;
                rpnAlg[i-l+1] = rpnTemp[i];
                while(l>0)
                {
                    rpnAlg[i-l+2] = rpnTemp[i-l];
                    l--;
                }
                rpnAlg[i+2] = brackets[1];
            }
            else if(rpnconverter_isvalidoperator(rpnAlg[i-2]) == 0 && rpnAlg[i-2] != brackets[1])
            {
                rpnAlg[i-2] = brackets[0];
                rpnAlg[i-1] = rpnTemp[i-2];
                rpnAlg[i+1] = rpnTemp[i-1];
                rpnAlg[i+2] = brackets[1];    
            }
            else
            {
                span = 2;
                l = rpnconverter_rpn2infix_span(i,span,rpnAlg);
                rpnAlg[i-l] = brackets[0];
                while(l>1)
                {
                    rpnAlg[i-l+1] = rpnTemp[i-l];
                    l--;
                }
                rpnAlg[i+1] = rpnTemp[i-1];
                rpnAlg[i+2] = brackets[1];
            }
            j=0;
            for(n = i+1;n<strlen(rpnTemp);n++)
            {
                j++;
                rpnAlg[i+2+j] = rpnTemp[n];
            }
            i+=2;
            k++;
        }
        i++;
    }
    free(error);
    free(rpnTemp);
    free(rpnOperators);
    return rpnAlg;
};

char *rpnconverter_rpn2infix_getoperators(char *alg)
{
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize Variables
    int j=0;
    int numOperators = rpnconverter_countoperators(alg);
    char * rpnAlg = calloc(numOperators+1,sizeof(char));
    //Use A For Loop And Switch Cases To Quickly Return An Array Of Operators From The RPN Function
    for(int i=0;i<strlen(alg);i++){
        switch(alg[i]) {
          case '^' :
             rpnAlg[j] = '^';
             j++;
             break;
          case '/' :
             rpnAlg[j] = '/';
             j++;
             break;
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
    free(error);
    return rpnAlg;
};

int rpnconverter_rpn2infix_span(int i, int span, char *rpn)
{
    if(strlen(rpn) <= 0)
    {
        perror("Error: Algorithm Size");
        return 0;
    }
    //Initialize main variables
    int j=0,k=span;
    char * brackets = "()";
    //Calculate the span between chosen brackets
    while(rpnconverter_isvalidoperator(rpn[i-span]) == 0 && rpn[i-span] == brackets[1])
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

int rpnconverter_countoperators(char *alg)
{
    //Initialize Variables
    int i = 0, countOperators = 0;
    //Get Number of Operators
    for(i=0;i<strlen(alg);i++)
    {
        switch(alg[i]){
            case '^':
                countOperators++;
                break;
            case '/':
                countOperators++;
                break;
            case '*':
                countOperators++;
                break;
            case '-':
                countOperators++;
                break;
            case '+':
                countOperators++;
                break;
        }
    }
    return countOperators;
};

char *rpnconverter_infix2rpn_getoperatorarray(char *alg)
{
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize Variables
    int i = 0, j = 0, k = 0, countSpan = 0, skipParentheses = 0, loop = 0;
    int countParentheses = rpnconverter_infix2rpn_orderofoperation_checkparentheses(alg);
    int numOperators = rpnconverter_countoperators(alg);
    char *operatorArray;
    char *tempArray;
    char *parentheses = "()";
    //If Algorithm Has No Parentheses Then Send Algorithm Directly To OrderOfOperation Function
    //If Algorithm Does Have Parentheses Then Parse Out Sub Algorithms Delimited By Parentheses And Perform OrderOfOperation Function On Each Sub Algorithm Then Combine Returned Operators Respecting OrderOfOperation Changes Caused By The Parentheses
    if(countParentheses == 0)
    {
        operatorArray = rpnconverter_infix2rpn_orderofoperation(0,strlen(alg),alg);
    }
    else
    {
        operatorArray = calloc(numOperators+1,sizeof(char));
        while(i<strlen(alg))
        {
            if(alg[i] == parentheses[1])
            {
                while(loop == 0)
                {
                    if(alg[i-countSpan] == parentheses[1])
                    {
                        skipParentheses++;
                    }
                    if(skipParentheses > 0 && alg[i-countSpan] == parentheses[0])
                    {
                        skipParentheses--;
                    }
                    countSpan++;
                    if(skipParentheses == 0)
                    {
                        countSpan--;
                        loop = 1;
                    }
                }
                loop = 0;
                tempArray = rpnconverter_infix2rpn_orderofoperation(i-countSpan+1,countSpan,alg);
                countSpan = 0;
                j=0;
                while(j<strlen(tempArray))
                {
                    operatorArray[k] = tempArray[j];
                    k++;
                    j++;
                }
                free(tempArray);
            }
            i++;
        }
    }
    free(error);
    return operatorArray;
};

char *rpnconverter_infix2rpn_orderofoperation(int start, int span, char *alg)
{
    char *error = calloc(30+1,sizeof(char));
    if(strlen(alg) <= 0)
    {
        strcpy(error, "Error: Algorithm Size");
        return error;
    }
    //Initialize Variables
    int i = 0, j = 0, nestFound = 0;
    int phase = 1;
    char *parentheses = "()";
    char *operatorsOne = "^";
    char *operatorsTwo = "/*";
    char *operatorsThree = "-+";
    char *orderArray = calloc(span+1,sizeof(char));
    
    //Loop Through Given Span And Return Operators With Respect To Order Of Operation
    //If Given Span Has Nested Parentheses Skip Over Them
    while(i<span && phase<4)
    {
        if(alg[start+i] == parentheses[0])
        {
            nestFound++;
        }
        else if(nestFound > 0 && alg[start+i] == parentheses[1])
        {
            nestFound--;
        }
        else if(phase == 1 && nestFound == 0)
        {
            if(alg[start+i] == operatorsOne[0])
            {
                orderArray[j] = alg[start+i];
                j++;
            }
        }
        else if(phase == 2 && nestFound == 0)
        {
            if(alg[start+i] == operatorsTwo[0] || alg[start+i] == operatorsTwo[1])
            {
                orderArray[j] = alg[start+i];
                j++;
            }
        }
        else if(phase == 3 && nestFound == 0)
        {
            if(alg[start+i] == operatorsThree[0] || alg[start+i] == operatorsThree[1])
            {
                orderArray[j] = alg[start+i];
                j++;
            }
        }
        i++;
        if(i == span && phase < 4)
        {
            i = 0;
            phase++;
        }
    }
    free(error);
    return orderArray;
};

int rpnconverter_infix2rpn_orderofoperation_checkparentheses(char *alg)
{
    //Initialize Variables
    int check = 0;
    char *specialOperator = "()";
    //Check The Input Algorithm For Any Parentheses. If Any Are Found Return The Number Of Occurences
    for(int i=0;i<strlen(alg);i++)
    {
        if(alg[i] == specialOperator[0])
        {
            check++;
        }
    }
    return check;
};

int rpnconverter_isvalidoperator(char operator)
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