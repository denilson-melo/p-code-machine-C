#ifndef PCODE_H
#define PCODE_H

#define STACK_SIZE 1024

enum { LIT, OPR, LOD, STO, CAL, INT, JMP, JPC, WRT } instructionCode;
enum { RTN, NEG, ADD, SUB, MUL, DIV } operationCode;

struct instruction{
    int operation;
    int level;
    int argument;
};
extern struct instruction instructions[];

void run();
void executeInstruction();
void stackOperation();
int getBase(int);
int getInstructionCode(char *);
char * getInstructionName(int);
char * getOperationName(int);
void printStack();

#endif