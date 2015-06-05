#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FILE_NOT_OPENED 1
#define ERROR_WRONG_EXECUTION_FORMAT 2
#define ERROR_UNKNOWN_OPERATION 3

#define MAX_INSTRUCTIONS 1024


FILE *fp;
void parseFile();
void error(int);

struct instruction{
    int operation;
    int level;
    int argument;
};
struct instruction instructions[MAX_INSTRUCTIONS];
enum { LIT, OPR } operationCode;
int getOperationCode(char *);
char * getOperationName(int);

int codeLines;
void printInstructions();

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
    
    return 0;
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
    error(ERROR_UNKNOWN_OPERATION);
    return -1;
}

char * getOperationName(int name){
    switch (name){
        case LIT:
            return "LIT";
        case OPR:
            return "OPR";
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
