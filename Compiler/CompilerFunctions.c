#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "CompilerHeader.h"

bool isKeyword(char *str) {
    return (strcmp(str, "input") == 0 || strcmp(str, "if") == 0 || strcmp(str, "let") == 0 ||
            strcmp(str, "goto") == 0 || strcmp(str, "print") == 0 || strcmp(str, "end") == 0 ||
            strcmp(str, "inputS") == 0 || strcmp(str, "printS") == 0|| strcmp(str, "letS") == 0);
}

bool isConstant(const char *str) {
    if (str == NULL || strlen(str) == 0) {
        return false;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit((unsigned char) str[i])) {
            return false;
        }
    }
    return true;
}

bool isConditionalOperator(char c) {
    return c == '=' || c == '>' || c == '<' || c == '!';
}

int returns_SML_location_from_SymbolTable(char *Symbol) //this is for variables,constants and String Literal
{
    remove_newline(Symbol);
    if (Symbol[0] == '\"') // We are looking for a string literal
    {
        for (int i = 0; i < SymbolTableIndex; i++) {

            if (SymbolTable[i].type != 'S')
                continue;

            //printf("Current %s\n",SymbolTable[i].variable);
            if (strcmp(Symbol, SymbolTable[i].variable) == 0) {
                //printf("%s is in symbol table\n",Symbol);
                return SymbolTable[i].location;
            }
        }
    }
    if (isalpha((unsigned char) Symbol[0])) {
        // printf("Checking %s if in symbol table\n",Symbol);
        for (int i = 0; i < SymbolTableIndex; i++) {

            if (SymbolTable[i].type != 'V' && SymbolTable[i].type != 'S')
                continue;

            //printf("Current %s\n",SymbolTable[i].variable);
            if (strcmp(Symbol, SymbolTable[i].variable) == 0) {
                //printf("%s is in symbol table\n",Symbol);
                if (SymbolTable[i].type == 'S')
                    isString = true;

                return SymbolTable[i].location;
            }

        }
    } else {
        for (int i = 0; i < SymbolTableIndex; i++) {
            if (SymbolTable[i].type != 'C')
                continue;

            if (strcmp(Symbol, SymbolTable[i].variable) == 0)
                return SymbolTable[i].location;
        }
    }

    return -1;
}

//Using another function since line numbers can be double digits and strings need to
//be used with atoi() --> atoi("A")=0 Problem!
int returns_LineNum_location_from_SymbolTable(char *Symbol) //this is for line numbers
{
    for (int i = 0; i < SymbolTableIndex; i++) {
        if (atoi(Symbol) == SymbolTable[i].symbol && SymbolTable[i].type == 'L')
            return SymbolTable[i].location;
    }
    return -1;
}

int returns_LineNum_location_from_SymbolTable2(int Symbol) //this is for line numbers for the flags array
{
    for (int i = 0; i < SymbolTableIndex; i++) {
        if (SymbolTable[i].symbol == Symbol && SymbolTable[i].type == 'L')
            return SymbolTable[i].location;
    }
    return -1;
}

void printSymbolTable() {
    // printf("SymbolTableIndex: %d\n",SymbolTableIndex);
    printf("Symbol \t Type \t Location\n");
    for (int i = 0; i < SymbolTableIndex; i++) {
        if (SymbolTable[i].type == 'L')
            printf("%.0lf\t %c\t %d\n", SymbolTable[i].symbol, SymbolTable[i].type, SymbolTable[i].location);
        else if (SymbolTable[i].type == 'V')
            printf("%s\t %c\t %d\n", SymbolTable[i].variable, SymbolTable[i].type, SymbolTable[i].location);
        else if (SymbolTable[i].type == 'C')
            printf("%.2lf\t %c\t %d\n", SymbolTable[i].symbol, SymbolTable[i].type, SymbolTable[i].location);
        else
            printf("%s\t %c\t %d\n", SymbolTable[i].variable, SymbolTable[i].type, SymbolTable[i].location);
    }
}

void printSML() {
    puts("");
    puts("-----------------------------------");
    puts("Printing the SML program");

    for (int i = 0; i <= SmlInstructionCounter; i++) {
        if (SML[i] == 0)
            break;
        printf("%.0lf\t", SML[i]);

        switch ((int) SML[i] / 1000) {
            case 10:
                printf("  // Read and store in location %d\n", (int) SML[i] % 1000);
                break;
            case 11:
                printf("  // Write to console value in location %d\n", (int) SML[i] % 1000);
                break;
            case 12:
                printf("  // Read string and store in location %d\n", (int) SML[i] % 1000);
                break;
            case 13:
                printf("  // Write to console string in location %d\n", (int) SML[i] % 1000);
                break;
            case 14:
                printf("  // Print NewLine\n", (int) SML[i] % 1000);
                break;
            case 20:
                printf("  // Load value from location %d in accumulator\n", (int) SML[i] % 1000);
                break;
            case 21:
                printf("  // Store value in accumulator in location %d\n", (int) SML[i] % 1000);
                break;
            case 30:
                printf("  //  Value in accumulator + value in location %d\n", (int) SML[i] % 1000);
                break;
            case 31:
                printf("  //  Value in accumulator - value in location %d\n", (int) SML[i] % 1000);
                break;
            case 32:
                printf("  // Value in accumulator / value in location %d\n", (int) SML[i] % 1000);
                break;
            case 33:
                printf("  //  Value in accumulator * value in location %d\n", (int) SML[i] % 1000);
                break;
            case 34:
                printf("  // Value in accumulator % value in location %d\n", (int) SML[i] % 1000);
                break;
            case 35:
                printf("  //  Value in accumulator ^ value in location %d\n", (int) SML[i] % 1000);
                break;
            case 40:
                printf("  // Branch to location %d\n", (int) SML[i] % 1000);
                break;
            case 41:
                printf("  // Branch to location %d if accumulator is negative\n", (int) SML[i] % 1000);
                break;
            case 42:
                printf("  // Branch to location %d if accumulator is negative or zero\n", (int) SML[i] % 1000);
                break;
            case 43:
                printf("  // Branch to location %d if accumulator is positive\n", (int) SML[i] % 1000);
                break;
            case 45:
                printf("  // Branch to location %d if accumulator is positive or zero\n", (int) SML[i] % 1000);
                break;
            case 46:
                printf("  // Branch to location %d if accumulator is zero\n", (int) SML[i] % 1000);
                break;
            case 49:
                printf("  // Halt program\n");
                break;
            default:
                puts("");

        }
    }
}

void printFlagsArray() {
    puts("Flags array");
    for (int i = 1; i <= SymbolTableIndex; i++) {
        printf("%d ", flags[i]);
        if (i % 10 == 0)
            puts("");
    }
}

bool isVariableInSymbolTable(int address) {
    for (int i = 0; i < SymbolTableIndex; i++) {
        if (SymbolTable[i].location == address && SymbolTable[i].type == 'V')
            return true;
    }
    return false;
}

void completeInstructions() {
    for (int i = 0; i < 1000; i++) {
        if (flags[i] != -1) {
            int loc = returns_LineNum_location_from_SymbolTable2(flags[i]);
            if (loc == -1) {
                printf("Goto to unknown line number.");
                exit(1);
            } else {
                // printf("SML instruction %d with goto location %d\n",i,loc);
                SML[i] += loc;
            }
        }
    }
}

void checkCounters() {
    if (SmlInstructionCounter >= SmlVariableIndexCounter) {
        printf("The inputted Simple program is too large for SML[1000]");
        exit(1);
    }
}

bool isValidVariable(char *var) {
    remove_newline(var);
    size_t len = strlen(var);
    if (len > 25) {
        printf("Variable %s at line %d exceeds length of 25 chars\n", var, lastValidLine);
        exit(1);
    }
    //printf("Variable being validated %s has length %d\n",var,len);
    for (int i = 0; i < len; i++) {
        if (!isalpha(var[i])) {
            return false;
        }
    }
    return true;
}

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    if (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
    }
}

void check_String_length(char *var) {
    if (strlen(var) > 25) {
        printf("Variable %s at line %d exceeds length of 25 chars\n", var, lastValidLine);
        exit(1);
    }
}

bool isValidStringLiteral(char *var) {
    size_t len = strlen(var);
    // printf("Length %llu\n", strlen(var));
    if (var[len - 1] == '\n' || var[len - 1] == ' ') {
        //printf("Replacing \n or space in string literal %s var\n");
        var[len - 1] = '\0';
    }

    //printf("var[0] = %c , var[len-1]=%c and length=%llu\n",var[0],var[len-1],len);

    if (*var == '\"' && var[len - 1] == '\"' && len - 2 <= 10) //We will not input the two \" in memory
        return true;

    printf("The string literal %s at line %d is not valid or is longer than 10 chars.", var, lastValidLine);
    exit(1);
}