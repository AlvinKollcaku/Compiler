/*
 * <Compiler>
 * Copyright (C) <2024> <Alvin Kollçaku>
 *
 * Author: Alvin Kollçaku
 * Contact: kollcakualvin@gmail.com
 * Year: 2024
 * Original repository of the project: https://github.com/AlvinKollcaku/Compiler
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MINICOMPILERFINAL_INFIXHEADER_H
#define MINICOMPILERFINAL_INFIXHEADER_H

#include <stdbool.h>

extern int lastValidLine;

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
