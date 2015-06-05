#include "pcode.h"
#include "error.h"
#include <string.h>

int stack[STACK_SIZE];

int base = 1;
int stackTop = 0;
int programCounter = 0;
struct instruction instructionRegister;

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