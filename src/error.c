#include "error.h"
#include "pcode.h"
#include <stdio.h>
#include <stdlib.h>

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

void notImplemented(int code, int e, int line){
    switch ( e ){
        case ERROR_INSTRUCTION_NOT_IMPLEMENTED :
            printf("Sorry, the '%s' instruction is not available yet\n", getInstructionName(code));
            printf("Program counter: %d\n", line);
            break;
        case ERROR_STACK_OPERATION_NOT_IMPLEMENTED :
            printf("Sorry, the '%s' OPR is not available yet\n", getOperationName(code));
            printf("Program counter: %d\n", line);
            break;
    }
    exit(0);
}