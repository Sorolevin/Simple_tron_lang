#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    /* is alpha etc*/
#include <string.h> 
#include <math.h> 
struct stackNode_1 {
    char data;
    struct stackNode_1 *nextPtr;
};

typedef struct stackNode_1 StackNode_1;
typedef StackNode_1 *StackNodePtr_1;


char stackTop_1( StackNodePtr_1  topPtr );

void convertToPostfix_1( char infix[], char postfix[] );

char pop_1( StackNodePtr_1  *topPtr );
void push_1( StackNodePtr_1  *topPtr, char info );
int isEmpty_1( StackNodePtr_1  topPtr );

int isOperator_1( char c );

int precedence_1( char operator1, char operator2 );




/*
int main()
{
    char infix[50];
    char postfix[50];
    
   //printf("Please enter infix expression: ");
   //getLine(infix, 50 ); 
   
   
    strcpy(infix, "43 + 32" );
   
    convertToPostfix( infix, postfix ); 
  
  
  
  
  
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}
*/

void convertToPostfix_1( char infix[], char postfix[] )
{
    int i=0, j=0;   
    char c;

    /* Push left parenthesis to stack */
    StackNodePtr_1  stackPtr = NULL;
    push_1( &stackPtr, '(' ); 
    
    /* Add right parenthesis to end of infix */
    while( infix[i]!='\0')
        i++;

    infix[i++] = ')';
    infix[i] = '\0';
    
    i=0;
    
    /* Do the conversion */
    while( !isEmpty_1( stackPtr ) && infix[i]!='\0' )
    {
        c = infix[i++];
        
        if( isdigit(c) || isalpha(c) ) 
        {
            while( isdigit(c)  || isalpha(c)          ) {
                postfix[j++] = c;
                c = infix[i++];
            }
            postfix[j++] = ' ';
            
            if(c == ')' || isOperator_1(c) )
                i--;
        }
        else if( c == '(')
            push_1( &stackPtr, '(' );
        else if( isOperator_1(c) == 1 ) 
        {
            if( !isEmpty_1( stackPtr ) && isOperator_1( stackTop_1(stackPtr) ) ) {
                while( isOperator_1( stackTop_1(stackPtr) ) && 
                       (precedence_1( stackTop_1(stackPtr), c )) >= 0 ) 
                {
                    postfix[j++] = pop_1( &stackPtr );
                    postfix[j++] = ' ';
                }
                push_1( &stackPtr, c );
            }
            else
                push_1( &stackPtr, c );
        }
        else if( c == ')') 
        {
            if( !isEmpty_1( stackPtr ) ) 
            {
                c = pop_1( &stackPtr ); 

                while( !isEmpty_1( stackPtr ) && c != '(' ) {
                    postfix[j++] = c;
                    postfix[j++] = ' ';
                    c = pop_1( &stackPtr ); 
                }
            }
        }
    }
    postfix[j] = '\0';
}





/* Returns -1 if operator1 has lower precedence than operator2,
 * 0 if it has the same precedence, and 1 if it has higher precedence 
 * order of precedence = ^ * / % + -   
 */
int precedence_1( char operator1, char operator2 )
{
    int result = 1;

    switch( operator1 )
    {
        case '^':
            if( operator2 == '^') result = 0;
            break;
        case '*': case '/': case '%':
            switch( operator2 ) {
                case '^':
                    result = -1;
                    break;
                case '*': case '/': case '%':
                    result = 0;
                    break;
                default:
                    break;
            }
            break;
        case '+': case '-': 
            switch( operator2 ) {
                case '-': case '+':
                    result = 0;
                    break;
                default:
                    result = -1;
                    break;
            }
            break;
    }

    return result;
}




/* Push value onto the stack */
void push_1( StackNodePtr_1  *topPtr, char info )
{
    StackNodePtr_1 newPtr;
    
    newPtr = malloc( sizeof( StackNode_1  ) ); /* Now points to a place in memory*/
    
    if( newPtr != NULL ) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else
        printf( "%c not inserted. No memory available.\n", info );
}


/* Pop value from the stack */
char pop_1( StackNodePtr_1  *topPtr )
{
    StackNodePtr_1  tempPtr;
    char popValue;
    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free( tempPtr );
    
    return popValue;
}


/* Return the value at the top of the stack */
char stackTop_1( StackNodePtr_1  topPtr )
{
    char topValue;
    
    topValue = topPtr->data;
    
    return topValue;    
}


/* Test if the list is empty */
int isEmpty_1( StackNodePtr_1  topPtr )
{
    return topPtr==NULL;
}





int isOperator_1( char c )
{
    int result = 0;

    switch( c )
    {
        case '^': case '*': case '/': case '%': case '+': case '-': 
            result = 1;
            break;
        default:
            break;
    }

    return result;
}
