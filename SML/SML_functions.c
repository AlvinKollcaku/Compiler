#include <stdio.h>
#include <stdbool.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "SML_macros.c"
#include "SML_header.h"

void load(double *memory, int instructionCounter) {
    FILE *infile = NULL;

    infile = fopen("C:\\Users\\alvin\\OneDrive\\Desktop\\MiniCompilerFinal\\SML\\Program.txt", "r");

    if (infile == NULL) {
        // File could not be opened
        perror("Error opening file");
        return; // Return a non-zero value to indicate failure
    }

    //printf("Location\n");

    while (memory[instructionCounter - 1] != -999999) {
        /* This is for memory[1000]
        if(instructionCounter<10)
            printf("00");
        else if(instructionCounter<100)
            printf("0");
        */

        /*
        if(instructionCounter<10)
            printf("0");

        printf("%d ?  \t", instructionCounter);
         */

        fscanf(infile, "%lf", &memory[instructionCounter]);
        //scanf("%d",&memory[instructionCounter]);

        if ((memory[instructionCounter] <= 99999 && memory[instructionCounter] >= -99999)
            || memory[instructionCounter] == -999999)
            instructionCounter++;
        else
            printf("Inputted number exceeds the range -99999 to 99999\n");
    }

    //fclose(infile);
}

void execute(double *accumulator, int *instructionCounter, int *instructionRegister,
             int *operationCode, int *operand, double *memory) {
    while (1) {

        *instructionRegister = (int) memory[*instructionCounter];
        *operationCode = *instructionRegister / 1000;
        *operand = *instructionRegister % 1000;
        switch (*operationCode) {
            //Input Output operations

            case READ:
                printf("Enter the number for location %d: \n", *operand);
                double number;
                scanf("%lf", &number);
                if (number > 99999 || number < -99999) {
                    printf("The inputted number at location %d exceeds the range -99999 and 99999", *operand);
                    exit(1);
                }
                memory[*operand] = number;
                (*instructionCounter)++;
                break;
            case READ_STRING:
                char input[6]="";
                printf("Enter the string for location %d (not more than 5 characters)\n", *operand);

                if (fgets(input, sizeof(input), stdin) != NULL) {
                    // Removing newline character if present
                    size_t len = strlen(input);
                    if (len > 0 && input[len - 1] == '\n') {
                        input[len - 1] = '\0';
                    } else {
                        // Input was truncated, clear the remaining characters in the buffer
                        clear_input_buffer();
                    }
                }
                size_t len = strlen(input);
                //Now that we are dealing with a valid string we store it in memory in sequence
                int startingLocation = *operand;
                memory[startingLocation]=len*10000+(int)input[0];
                for(int i=1;i<len;i++)
                {
                    memory[--startingLocation]=(int)input[i];
                }
                (*instructionCounter)++;
                break;
            case WRITE:
                printf(": %.2lf \n", memory[*operand]);
                (*instructionCounter)++;
                break;
            case WRITE_STRING:
                //First we extract the length of the string from the memory location
                int length=(int)memory[*operand]/10000;
                //Now we extract the characters in sequence

                int length2=(int)memory[*operand]/10000;
                char result[6];
                int currentLocation=*operand;
                int i=0;
                for(;i<length2;i++)
                {
                    result[i]=(char)((int)memory[currentLocation--]%1000);
                    //%1000 just to skip the integer that specifies the length the first time
                }
                result[i]='\0';
                printf(": %s\n",result);
                (*instructionCounter)++;

                break;
                //Load/store operations

            case LOAD:
                *accumulator = memory[*operand];
                (*instructionCounter)++;
                break;
            case STORE:
                memory[*operand] = *accumulator;
                (*instructionCounter)++;
                break;

                //Arithmetic operations
            case ADD:
                if ((*accumulator) + memory[*operand] <= 99999 &&
                    (*accumulator) + memory[*operand] >= -99999)
                    (*accumulator) += memory[*operand];
                else {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simple language execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;
            case SUBTRACT:
                if ((*accumulator) - memory[*operand] <= 99999 &&
                    (*accumulator) - memory[*operand] >= -99999)
                    (*accumulator) -= memory[*operand];
                else {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;
            case DIVIDE:
                if (memory[*operand] != 0) {
                    (*accumulator) /= memory[*operand];
                } else {
                    printf("***Attempt to divide by 0***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;
            case MULTIPLY:
                if ((*accumulator) * memory[*operand] <= 99999 &&
                    (*accumulator) * memory[*operand] >= -99999)
                    (*accumulator) *= memory[*operand];
                else {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;
            case REMAINDER:
                if (isInteger(*accumulator) && isInteger(memory[*operand])) {
                    (*accumulator) = (int) *accumulator % (int) memory[*operand];
                    (*instructionCounter)++;
                } else {
                    perror("Trying to perform remainder with non-integer");
                    exit(1);
                }
                break;
            case EXPONENTIATION:
                if (pow(*accumulator, memory[*operand]) <= 99999 &&
                    pow(*accumulator, memory[*operand]) >= -99999)
                    (*accumulator) = pow(*accumulator, memory[*operand]);
                else {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;

                //Transfer-of-control operations:

            case BRANCH:
                (*instructionCounter) = *operand;
                break;
            case BRANCHNEG:
                if (*accumulator < 0)
                    (*instructionCounter) = *operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHZERO:
                if (*accumulator == 0)
                    (*instructionCounter) = *operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHPOS:
                if (*accumulator > 0)
                    (*instructionCounter) = *operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHPOS_ZERO:
                if (*accumulator >= 0)
                    (*instructionCounter) = *operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHNEG_ZERO:
                if (*accumulator <= 0)
                    (*instructionCounter) = *operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHNOT_ZERO:
                if (*accumulator != 0)
                    (*instructionCounter) = *operand;
                else
                    (*instructionCounter)++;
                break;
            case HALT:
                dump(*accumulator, *instructionCounter, *instructionRegister,
                     *operationCode, *operand, memory);
                exit(0);
            default:
                printf("Not valid keyword in SML. Program halted abnormally");
                dump(*accumulator, *instructionCounter, *instructionRegister,
                     *operationCode, *operand, memory);
                exit(0);
        }
    }
}


void dump(double accumulator, int instructionCounter, int instructionRegister,
          int operationCode, int operand, double *memory) {
    printf("\nREGISTERS:\n");
    printf("Accumulator \t %lf\n", accumulator);
    printf("InstructionCounter \t %d\n", instructionCounter);
    printf("InstructionRegister \t %d\n", instructionRegister);
    printf("OperationCode \t %d \n", operationCode);
    printf("Operand \t %02d \n\n", operand);

    printf("MEMORY: \n");

    int sideNumber = 0;
    printf("\t");

    for (int i = 0; i < 10; i++) //printing the above numbers
    {
        printf("%d      ", i);
    }

    for (int i = 0; i < 1000; i++) {
        if (i % 10 == 0) {
            puts("");
            printf("%d\t", sideNumber);
            sideNumber += 10;
        }
        if (isInteger(memory[i])) {
            printf("%+06.0lf ", memory[i]);
        } else
            printf("%+07.1lf ", memory[i]);
    }
}

int isInteger(double num) {
    double int_part;
    double frac_part = modf(num, &int_part);//num is split into int part and frac part
    return frac_part == 0.0;
}

bool is_valid_float(const char *str) {
    char *endptr;
    double value = strtod(str, &endptr);
    // converts a string to a double and sets the endptr to point to the first character after the numeric value
    if (*endptr ==
        '\0')//if the first character after the numeric value is the string terminator than we have a valid float
    {
        double int_part;
        double frac_part = modf(value, &int_part);//num is split into int part and frac part
        if (int_part > -99999 && int_part < 99999)
            return true;
    }

    return false;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters until end of line or end of file
    }
}