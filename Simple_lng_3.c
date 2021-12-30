#include "1_For_simltron_postfix.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM 100
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBSTRACT 31
#define DIVIDE 32
#define MUL 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

struct stackNode_2 {
  int data;
  struct stackNode_2 *nextPtr;
};

typedef struct stackNode_2 StackNode_2;
typedef StackNode_2 *StackNodePtr_2;

typedef struct tableEntry {
  int symbol;
  char type;
  int location;

} data;

int evaluatePostfixExpression_2(char *);
int calculate_2(int, int, char);
void push_2(StackNodePtr_2 *, int);
int pop_2(StackNodePtr_2 *);
int isEmpty_2(StackNodePtr_2);
int isOperator_2(char c);

void convertToPostfix_1(char infix[], char postfix[]);
int search_in_table(data *intro_search, int str_tok_search);
int evaluatePostfixExpression_2(char *);
int rem_break(char *token);
int let_past(data *base, char *infix, char *post_infix);

int count_down = 99;
int main(void) {

  char infix[150];
  char postfix[150];

  int line_simple_comands_input_print(int cmd, data *table, int token,
                                      int memory[]);

  int past_in_table_cons_or_value(data * table, int str_tok);

  int goto_search(data * table, int token);
  char *dictionary[] = {"input", "10", "print", "11", "goto", "40",
                        "end",   "43", "+",     "30", "-",    "31",
                        "/",     "32", "*",     "33"};

  char *command_dictinary[] = {"input", "print", "if", "goto",
                               "let",   "end",   "rem"};

  int search_cmd(char *dict[15], char *token);

  int token_string_count = 0;
  data symbolTable[100];

  int d = 0;
  int flags[100];
  int mem_smp[100];

  char post_buf[150];

  int count_cmd = 0;
  int lng = 0;

  FILE *mf;
  char *bufer = 0;
  int dz = 0;
  char bufer_postfix[150];

  char buf_data[150][150] = {{0}};

  char expr[] = "t = (t +  45 / 3 )  + (4 * 45) + t / (3 - 21) + 21 - g * 45";
  // char expr[] = "d = (g +  2 / s )  + (5 * 5) + 87 / (3 - 1) + 211 - w * 45";

  for (; d != 100; d++) {

    (symbolTable + d)->symbol = 0;
    (symbolTable + d)->location = 0;
    (symbolTable + d)->type = 'q';
    mem_smp[d] = 0;
    flags[d] = -1;
  }

  strcpy(infix, expr);
  convertToPostfix_1(infix, postfix);

  dz = let_past(symbolTable, postfix, post_buf);
  puts(post_buf);
  printf("%d\n", dz);

  /*
    printf("Postfix expression: %s\n", postfix);

   d = evaluatePostfixExpression_2( postfix );
   printf("Result: %d\n", d);
  */

  char data_txt[1000] = {};
  char str[100] = {};

  // mf = fopen ("rt.smp","r");

  /*
  for ( ;feof (mf) == 0 ;     ++lng)  {

          fgets ( &buf_data[lng][0]    ,150,mf );

    }

    fclose (mf) ;



  for(d = 0  ;buf_data[d][0] != 0  ;++d  ){

          bufer = strtok( &buf_data[d][0] , " " );

          for (token_string_count = 0   ;bufer !=  NULL;  token_string_count++,
  bufer = strtok ( NULL , " " ) ){


                  if( strcmp(bufer , "print" ) == 0 ||  strcmp(bufer , "input" )
  == 0   ){ dz  =  search_cmd( dictionary , bufer  );
                                          //printf("%d\n", dz );
                                          printf("%s %s\n", dictionary[dz] ,
  dictionary[dz + 1]   );
                          }




                  if(	rem_break(bufer  )  == 1){
                          break;
                  }

          }



  }

  */

  return 0;
}

int let_past(data *base, char *infix, char *post_infix) {
  char *bufer;

  int past_in_table_cons_or_value(data * table, int str_tok);
  int data_adress = 0;
  int lng = 0;
  int left_side = 0;
  past_in_table_cons_or_value(base, infix[0]);

  bufer = strtok(&infix[1], "  ");

  for (; bufer != (char *)'\0';
       post_infix[lng++] = ' ', bufer = strtok(NULL, " ")) {

    if (isdigit(*bufer) || isalpha(*bufer)) {

      data_adress = past_in_table_cons_or_value(
          base, isdigit(*bufer) ? atoi(bufer) : *bufer);

      sprintf(&post_infix[lng], "%d", data_adress);
      lng += 2;
    }

    else {
      post_infix[lng] = *bufer;
      lng++;
    }
  }

  post_infix[lng] = '\0';
  left_side = search_in_table(base, infix[0]);

  return left_side;
}

int rem_break(char *token) {

  if (memcmp(token, "rem", 3) == 0) {
    return 1;
  }
  return 0;
}

/* ����� ������ ������� sml  */
int search_in_table(data *intro_search, int str_tok_search) {

  int runner = 99, last_point = 0;

  while (1) {

    if ((intro_search + runner)->symbol == str_tok_search ||
        runner == count_down) {

      last_point = runner;
      break;
    }
    runner--;
  }
  return last_point;
}

int past_in_table_cons_or_value(data *table, int str_tok) {

  int search_in_table(data * intro_search, int str_tok_search);

  int find = search_in_table(table, str_tok);
  // ������� ����� ���� ����
  if ((table + find)->symbol == 0) {

    (table + find)->symbol = str_tok; //  or  str_tok don't atoi
    (table + find)->type = isalpha(str_tok) == 2 ? 'V' : 'C';
    (table + count_down)->location = count_down;

    count_down--;
  }
  // ����� �����  ��  ������  sml
  return (table + find)->location;
}

int line_simple_comands_input_print(int cmd, data *table, int token,
                                    int memory[]) {
  int x = cmd * 10, addres = 0;

  int search_in_table(data * intro_search, int str_tok_search);

  addres = search_in_table(table, token);

  return x += addres;
}

int search_cmd(char *dict[], char *token) {
  int x = 0;

  for (; dict[x] != 0; x++) {

    if (strcmp(dict[x], token) == 0) {
      return atoi(dict[x + 1]);
    }
  }
}

//
int goto_search(data *table, int token) {

  int search_in_table(data * intro_search, int str_tok_search);
  int x = search_in_table(table, token);

  if (x != 0) {
    return (table + x)->location;
  }

  return 0;
}

int evaluatePostfixExpression_2(char *expr) {
  StackNodePtr_2 stackPtr = NULL;
  char c;
  int x, y;
  int i = 0, mult = 1, num = 0;

  while (expr[i] != '\0') {
    mult = 1;
    num = 0;
    c = expr[i];
    if (isdigit(c)) {
      while (isdigit(c)) {
        num *= mult;
        num += c - 48;
        c = expr[++i];
        mult *= 10;
      }
      --i;
      push_2(&stackPtr, num);
    } else if (isOperator_2(c)) {
      if (isEmpty_2(stackPtr)) {
        printf("Invalid postfix expression!\n");
        return 0;
      }
      x = pop_2(&stackPtr);

      if (isEmpty_2(stackPtr)) {
        printf("Invalid postfix expression!\n");
        return 0;
      }
      y = pop_2(&stackPtr);

      push_2(&stackPtr, calculate_2(y, x, c));
    }
    i++;
  }

  if (isEmpty_2(stackPtr)) {
    printf("Invalid postfix expression!\n");
    return 0;
  }

  return pop_2(&stackPtr);
}

int calculate_2(int op1, int op2, char operator) {
  int result = 0;

  switch (operator) {
  case '+':
    result = op1 + op2;
    break;
  case '-':
    result = op1 - op2;
    break;
  case '*':
    result = op1 * op2;
    break;
  case '/':
    result = op1 / op2;
    break;
  case '^':
    result = pow(op1, op2);
    break;
  case '%':
    result = op1 % op2;
    break;
  default:
    break;
  }

  return result;
}

/* Push value onto the stack */
void push_2(StackNodePtr_2 *topPtr, int info) {
  StackNodePtr_2 newPtr;

  newPtr = malloc(sizeof(StackNode_2)); /* Now points to a place in memory*/

  if (newPtr != NULL) {
    newPtr->data = info;
    newPtr->nextPtr = *topPtr;
    *topPtr = newPtr;
  } else
    printf("%c not inserted. No memory available.\n", info);
}

/* Pop value from the stack */
int pop_2(StackNodePtr_2 *topPtr) {
  StackNodePtr_2 tempPtr;
  int popValue;

  tempPtr = *topPtr;
  popValue = (*topPtr)->data;
  *topPtr = (*topPtr)->nextPtr;
  free(tempPtr);

  return popValue;
}

/* Test if the list is empty */
int isEmpty_2(StackNodePtr_2 topPtr) { return topPtr == NULL; }

/* Returns 1 if the character is an Operator, otherwise 0 */
int isOperator_2(char c) {
  int result = 0;

  switch (c) {
  case '^':
  case '*':
  case '/':
  case '%':
  case '+':
  case '-':
    result = 1;
    break;
  default:
    break;
  }

  return result;
}