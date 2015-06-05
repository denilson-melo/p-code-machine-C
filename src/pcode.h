#ifndef PCODE_H
#define PCODE_H

#define STACK_SIZE 1024

enum { LIT, OPR, STO, INT } operationCode;
struct instruction{
    int operation;
    int level;
    int argument;
};
extern struct instruction instructions[];

void run();
void executeInstruction();
int getBase(int);
int getOperationCode(char *);
char * getOperationName(int);

#endif