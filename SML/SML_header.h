#ifndef MINICOMPILERFINAL_SML_HEADER_H
#define MINICOMPILERFINAL_SML_HEADER_H
#define CUSTOM_TAB "         "
void dump(double accumulator,int instructionCounter,int instructionRegister,
          int operationCode,int operand, double memory[100]);

void execute(double* accumulator,int* instructionCounter,int* instructionRegister,
             int* operationCode,int* operand, double *memory);

void load(double* memory,int instructionCounter);
int isInteger(double num);
#endif //MINICOMPILERFINAL_SML_HEADER_H
