#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "SML_macros.c"
#include "SML_header.h"

void load(double* memory,int instructionCounter)
{
    FILE * infile=NULL;

    infile=fopen("C:\\Users\\alvin\\OneDrive\\Desktop\\MiniCompilerFinal\\SML\\Program.txt","r");

    if (infile == NULL) {
        // File could not be opened
        perror("Error opening file");
        return ; // Return a non-zero value to indicate failure
    }

    //printf("Location\n");

    while(memory[instructionCounter-1]!=-999999)
    {
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

        fscanf(infile,"%lf",&memory[instructionCounter]);
        //scanf("%d",&memory[instructionCounter]);

        if((memory[instructionCounter]<=99999 && memory[instructionCounter]>=-99999)
           || memory[instructionCounter]==-999999)
            instructionCounter++;
        else
            printf("Inputed number exceeds the range -99999 to 99999\n");
    }

    //fclose(infile);
}

void execute(double* accumulator,int* instructionCounter,int* instructionRegister,
             int* operationCode,int* operand, double *memory)
{
    while(1)
    {
        *instructionRegister=memory[*instructionCounter];
        *operationCode=*instructionRegister/1000;
        *operand=*instructionRegister%1000;
        switch(*operationCode)
        {
            //Input Output operations

            case READ:
                printf("Enter the number for location %d: \n",*operand);
                scanf("%lf",&memory[*operand]);
                (*instructionCounter)++;
                break;
            case WRITE:
                printf("Output: %lf \n", memory[*operand]);
                (*instructionCounter)++;
                break;

                //Load/store operations

            case LOAD:
                *accumulator=memory[*operand];
                (*instructionCounter)++;
                break;
            case STORE:
                memory[*operand]=*accumulator;
                (*instructionCounter)++;
                break;

                //Arithmetic operations
            case ADD:
                if((*accumulator)+memory[*operand]<=99999 &&
                   (*accumulator)+memory[*operand]>=-99999)
                    (*accumulator)+=memory[*operand];
                else
                {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simple language execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;
            case SUBSTRACT:
                if((*accumulator)-memory[*operand]<=99999 &&
                   (*accumulator)-memory[*operand]>=-99999)
                    (*accumulator)-=memory[*operand];
                else
                {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }

                (*instructionCounter)++;
                (*instructionCounter)++;
                break;
            case DIVIDE:
                if(memory[*operand]!=0)
                {
                    (*accumulator)/=memory[*operand];
                }
                else
                {
                    printf("***Attempt to divide by 0***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;
            case MULTIPLY:
                if((*accumulator)* memory[*operand]<=99999 &&
                   (*accumulator)* memory[*operand]>=-99999)
                    (*accumulator)*=memory[*operand];
                else
                {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                (*instructionCounter)++;
                break;
            case REMAINDER:
                if(isInteger(*accumulator)&& isInteger(memory[*operand]))
                {
                    (*accumulator)=(int)*accumulator%(int)memory[*operand];
                    (*instructionCounter)++;
                }else
                {
                    perror("Trying to perform remainder with non-integer");
                    exit(1);
                }
                break;
            case EXPONENTIATION:
                if(pow(*accumulator,memory[*operand])<=99999 &&
                   pow(*accumulator,memory[*operand])>=-99999)
                    (*accumulator)=pow(*accumulator,memory[*operand]);
                else
                {
                    printf("***Value in accumulator exceeds 99999 or -99999***\n"
                           "***Simpletron execution abnormally terminated***\n");
                    exit(0);
                }
                (*instructionCounter)++;
                break;

                //Transfer-of-control operations:

            case BRANCH:
                (*instructionCounter)=*operand;
                break;
            case BRANCHNEG:
                if(*accumulator<0)
                    (*instructionCounter)=*operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHZERO:
                if(*accumulator==0)
                    (*instructionCounter)=*operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHPOS:
                if(*accumulator>0)
                    (*instructionCounter)=*operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHPOS_ZERO:
                if(*accumulator>=0)
                    (*instructionCounter)=*operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHNEG_ZERO:
                if(*accumulator<=0)
                    (*instructionCounter)=*operand;
                else
                    (*instructionCounter)++;
                break;
            case BRANCHNOT_ZERO:
                if(*accumulator!=0)
                    (*instructionCounter)=*operand;
                else
                    (*instructionCounter)++;
                break;
            case HALT:
                dump(*accumulator,*instructionCounter,*instructionRegister,
                     *operationCode,*operand,memory);
                exit(0);
            default:
                printf("Not valid keyword in SML. Program halted abnormally");
                dump(*accumulator,*instructionCounter,*instructionRegister,
                     *operationCode,*operand,memory);
                exit(0);
        }
    }
}

void dump(double accumulator,int instructionCounter,int instructionRegister,
          int operationCode,int operand, double *memory)
{
    printf("\nREGISTERS:\n");
    printf("Accumulator \t %lf\n",accumulator);
    printf("InstructionCounter \t %d\n", instructionCounter);
    printf("InstructionRegister \t %d\n", instructionRegister);
    printf("OperationCode \t %d \n",operationCode);
    printf("Operand \t %02d \n\n",operand);

    printf("MEMORY: \n");

    int sideNumber=10;
    printf("\t");

    for(int i=0; i<10; i++) //printing the above numbers
    {
        printf("%d\t",i);
    }

    printf("\n0\t");

    for(int i=0; i<1000; i++)
    {
        if(i%10==0&&i!=0)
        {
            puts("");
            printf("%d\t",sideNumber);
            sideNumber+=10;
        }
        if(isInteger(memory[i]))
        {
            printf("%+06.0lf ",memory[i]);
        }else
        printf("%+07.1lf ",memory[i]);
    }
}

int isInteger(double num) {
    double int_part;
    double frac_part = modf(num, &int_part);//num is split into int part and frac part
    return frac_part == 0.0;
}