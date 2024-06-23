//
// Created by alvin on 10.06.2024.
//

#ifndef MINICOMPILERFINAL_INFIXHEADER_H
#define MINICOMPILERFINAL_INFIXHEADER_H

#include <stdbool.h>

struct stackNode
{
    char data;
    struct stackNode * nextPtr;
};

typedef struct stackNode StackNode;
typedef struct stackNode * StackNodePtr;

//functions.c
bool isOperator(char  c);
bool precedence(char operator1, char operator2);
void push(StackNodePtr *topPtr, char value);
char pop(StackNodePtr *topPtr);
bool isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr topPtr);
void convertToPostfix(char *infix,char *postfix[]);
char* charToString(char c);

typedef struct stackNode2
{
    double data;
    struct stackNode2 * nextPtr;
}StackNode2;

typedef StackNode2 * StackNode2Ptr;

void push2(StackNode2Ptr *topPtr, double value);
double pop2(StackNode2Ptr *topPtr);
bool isEmpty2(StackNode2Ptr topPtr);
void printStack2(StackNode2Ptr topPtr);
double calculate(double op1, double op2, char Operator);
double evaluatePostfixExpression(char *expr[]);

#endif //MINICOMPILERFINAL_INFIXHEADER_H
