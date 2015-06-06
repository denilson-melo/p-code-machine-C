#ifndef ERROR_H
#define ERROR_H

#define ERROR_FILE_NOT_OPENED 1
#define ERROR_WRONG_EXECUTION_FORMAT 2
#define ERROR_UNKNOWN_OPERATION 3
#define ERROR_INSTRUCTION_NOT_IMPLEMENTED 4
#define ERROR_STACK_OPERATION_NOT_IMPLEMENTED 5


void error(int);
void notImplemented(int, int, int);

extern int codeLines;

#endif