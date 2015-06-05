#include "error.h"
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