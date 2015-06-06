#include "pcode.h"
#include "error.h"
#include <string.h>

int stack[STACK_SIZE];

int base = 1;
int stackTop = 0;
int programCounter = 0;
struct instruction instructionRegister;
char * instructionString[] = { "LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC", "WRT" };
char * operationString[] = { "RTN", "NEG", "ADD", "SUB", "MUL", "DIV" };

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
            stackOperation();
            break;
        case LOD:
            stackTop++;
            stack[ stackTop ] = stack[ getBase(instructionRegister.level) + instructionRegister.argument ];
            break;
        case STO:
            stack[ getBase(instructionRegister.level) + instructionRegister.argument ] = stack[stackTop];
            stackTop--;
            break;
        case INT:
            stackTop += instructionRegister.argument;
            break;
        case JMP:
            programCounter = instructionRegister.argument-1;
            break;
        case JPC:
            if ( stack[stackTop] == 0 ){
                programCounter = instructionRegister.argument-1;
                stackTop--;
            }
            break;
        default:
            notImplemented( instructionRegister.operation,ERROR_INSTRUCTION_NOT_IMPLEMENTED, programCounter);
    }
}

void stackOperation(){
    switch(instructionRegister.argument){
        case RTN:
            stackTop = base - 1;
            programCounter = stack[stackTop+3];
            base = stack[stackTop+2];
            break;
        case ADD:
            stackTop--;
            stack[stackTop] += stack[stackTop+1];
            break;
        case SUB:
            stackTop--;
            stack[stackTop] -= stack[stackTop+1];
            break;
        default:
            notImplemented(instructionRegister.argument, ERROR_STACK_OPERATION_NOT_IMPLEMENTED, programCounter);
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

int getInstructionCode(char *str){
    int i = 0;
    while ( i<9 ){
        if ( strcmp(str,instructionString[i])==0 ){
            return i;
        }
        i++;
    }
    error(ERROR_UNKNOWN_OPERATION);
    return -1;
}

char * getInstructionName(int code){
    if ( code >= 0 && code <9 ){
        return instructionString[code];
    }
    return "UNKNOWN INSTRUCTION";
}

char * getOperationName(int code){
    if ( code >= 0 && code <6 ){
        return operationString[code];
    }
    return "UNKNOWN OPERATION";
}