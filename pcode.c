#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FILE_NOT_OPENED 1
#define ERROR_WRONG_EXECUTION_FORMAT 2
#define ERROR_UNKNOWN_OPERATION 3

#define MAX_INSTRUCTIONS 1024
#define STACK_SIZE 1024


FILE *fp;
int codeLines;
void parseFile();
void run();
void error(int);
int getOperationCode(char *);
char * getOperationName(int);
void printInstructions();
void executeInstruction();

struct instruction{
    int operation;
    int level;
    int argument;
};

enum { LIT, OPR, STO, INT } operationCode;

//Stack
int stack[STACK_SIZE];

//Registers
int base = 1;
int stackTop = 0;
int programCounter = 0;
struct instruction instructionRegister;

//Instructions
struct instruction instructions[MAX_INSTRUCTIONS];


int main(int argc, char ** argv){
    
    if ( argc !=2 ){
        error(ERROR_WRONG_EXECUTION_FORMAT);
    }
    
    //Opening file
    char * fileName = argv[1];
    fp = fopen(fileName,"r");
    if ( fp == NULL ){
        error(ERROR_FILE_NOT_OPENED);
    }
    
    printf("Parsing file...");
    parseFile();
    printf(" Success.\n");
    printInstructions();
    run();
    printf("Stack top: %d\n", stack[1]);
    return 0;
}

void run(){
    stack[1] = stack[2] = stack[3] = 0;
    
    while ( base > 0 ){
        executeInstruction();
    }
}

void executeInstruction(){
    instructionRegister = instructions[programCounter];
    programCounter++;
    switch ( instructionRegister.operation ){
        case LIT:
            stackTop++;
            stack[stackTop] = instructionRegister.argument;
            break;
        case OPR:
            switch(instructionRegister.argument){
                case 0: //RTN
                    stackTop = base - 1;
                    programCounter = stack[stackTop+3];
                    base = stack[stackTop+2];
                case 2: //ADD
                    stackTop--;
                    stack[stackTop] += stack[stackTop+1];
            }
            break;
        case STO:
            stack[ getBase(instructionRegister.level) + instructionRegister.argument ] = stack[stackTop];
            stackTop--;
            break;
        case INT:
            stackTop += instructionRegister.argument;
            break;
    }
}

int getBase(int level){
    int newBase;
    newBase = base;
    while ( level>0 ){
        newBase = stack[newBase];
        level--;
    }
    return newBase;
}

void parseFile(){
    char foperation[4];
    int flevel;
    int fargument;
    int i=0;
    while ( (fscanf(fp, "%s", foperation)) != EOF ){
       fscanf(fp, "%d", &flevel);
       fscanf(fp, "%d", &fargument);
       instructions[i].operation = getOperationCode(foperation);
       instructions[i].level = flevel;
       instructions[i].argument = fargument;
       codeLines = i++;
    }
    codeLines = i;
}

int getOperationCode(char *str){
    if ( strcmp(str,"LIT")==0 ){
        return LIT;
    }
    if ( strcmp(str,"OPR")==0 ){
        return OPR;
    }
    if ( strcmp(str,"STO")==0 ){
        return STO;
    }
    if ( strcmp(str,"INT")==0 ){
        return STO;
    }
    error(ERROR_UNKNOWN_OPERATION);
    return -1;
}

char * getOperationName(int name){
    switch (name){
        case LIT:
            return "LIT";
        case OPR:
            return "OPR";
        case STO:
            return "STO";
        case INT:
            return "INT";
    }
    return "";
}

void printInstructions(){
    int i = 0;
    printf("Instruction codes:\n");
    while ( i<codeLines ){
        printf("%s(%d) %d %d\n", getOperationName(instructions[i].operation),instructions[i].operation, instructions[i].level, instructions[i].argument);
        i++;
    }
}

void error(int e){
    switch (e){
        case ERROR_FILE_NOT_OPENED:
            printf("File could not be opened\n");
            break;
        case ERROR_WRONG_EXECUTION_FORMAT:
            printf("Wrong format\n");
            break;
        case ERROR_UNKNOWN_OPERATION:
            printf("Unknown operation found!, Line: %d\n", codeLines+1);
            break;
    }
    exit(0);
}
