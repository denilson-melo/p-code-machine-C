#ifndef PCODE_H
#define PCODE_H

#define STACK_SIZE 1024
#define INSTRUCTION_COUNT 9
#define OPERATION_COUNT 14

enum { LIT, OPR, LOD, STO, CAL, INT, JMP, JPC, WRT } instructionCode;
enum { RTN, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ } operationCode;

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