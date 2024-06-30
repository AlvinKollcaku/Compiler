#ifndef MINICOMPILERFINAL_COMPILERHEADER_H
#define MINICOMPILERFINAL_COMPILERHEADER_H

#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 300 //max length of line in input file that contains the simple program

struct tableEntry
{
    char symbol2[6];//This is for string variables->everything could have been stored here but since it
                    //was added later it need changes
    double symbol;//ASCII value of var, constant or line num
    char type;//'C'=constant 'V'=Variable 'L'=line number
    int location;//0 to 99 -> SMLs memory location associated with the symbol
    //char[20] command;
};

extern double SML[1000];// will hold the SML program
extern int SmlInstructionCounter;
extern int SmlVariableIndexCounter; //TODO check if SMLInstrcutioncounter > SMLVairableIndexCounter -> raise "out of memory error"
extern int flags[1000]; //flags array has the same size as SML because the index of the incomplete instruction
//in flags array will correspond to the index in SML array for the particular instruction

extern struct tableEntry SymbolTable[2000];
extern int SymbolTableIndex;
extern int lastValidLine;

typedef struct Postfix
{
    int address;
    struct Postfix * nextPtr;
}Postfix;

typedef struct Postfix * PostfixPtr;

//CompilerFunctions.c
void printSML();
bool isKeyword(char *str);
int returns_SML_location_from_SymbolTable(char *Symbol);
bool isVariable(char *var);
bool isKeyword(char *str);
bool isConstant(const char* str);
void printSymbolTable();
int returns_LineNum_location_from_SymbolTable(char* Symbol);
int returns_LineNum_location_from_SymbolTable2(int Symbol);
void printFlagsArray();
bool isVariableInSymbolTable(int address);
void completeInstructions();

//Keywords.c
void inputKeyword(char *tokenPtr);
void conditionKeyword(char *tokenPtr);
void printKeyword(char *tokenPtr);
bool isConditionalOperator(char c);
void letKeyword(char *tokenPtr);
void gotoKeyword(char *tokenPtr);
void inputS(char *tokenPtr);
void printS(char *tokenPtr);

//KeywordHelper.c
void handleOperators(char Operators[],int Operands[],char * tokenPtr);
int evaluatePostfixExpression2(char *expr[]);
void pushPostfix(PostfixPtr *topPtr, int value);
int popPostfix(PostfixPtr *topPtr);
void reorganizeStack(int a1,int a2,char operator,PostfixPtr *topPtr);
void printPostfixStack(PostfixPtr topPtr);
int find_operator_position(const char *str);

//InfixFunctions.c -> in InfixToPostfix folder
bool isOperator(char  c);
void convertToPostfix(char *infix,char *postfix2[]);
char* charToString(char c);

//SML_functions.c -> in SML folder
void dump(double accumulator,int instructionCounter,int instructionRegister,
          int operationCode,int operand, double *memory);

void execute(double* accumulator,int* instructionCounter,int* instructionRegister,
             int* operationCode,int* operand, double *memory);

void load(double* memory,int instructionCounter);
int isInteger(double num);

#endif //MINICOMPILERFINAL_COMPILERHEADER_H
