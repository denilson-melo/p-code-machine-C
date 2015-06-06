#include <stdio.h>
#include "parsing.h"
#include "pcode.h"
#include "error.h"

FILE *fp;

void openFile(char * fileName){
    fp = fopen(fileName,"r");
    if ( fp == NULL ){
        error(ERROR_FILE_NOT_OPENED);
    }
}

void parseFile(){
    char foperation[4];
    int flevel;
    int fargument;
    int i=0;
    while ( (fscanf(fp, "%s", foperation)) != EOF ){
       fscanf(fp, "%d", &flevel);
       fscanf(fp, "%d", &fargument);
       instructions[i].operation = getInstructionCode(foperation);
       instructions[i].level = flevel;
       instructions[i].argument = fargument;
       codeLines++;
       i++;
    }
    
    fclose(fp);
}

void printInstructions(){
    int i = 0;
    printf("Instruction codes:\n");
    while ( i<codeLines ){
        printf("%d %d %d\n", instructions[i].operation, instructions[i].level, instructions[i].argument);
        i++;
    }
}