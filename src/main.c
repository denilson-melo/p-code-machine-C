#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"
#include "pcode.h"
#include "error.h"

#define MAX_INSTRUCTIONS 1024


int codeLines;
extern int stack[];
struct instruction instructions[MAX_INSTRUCTIONS];

int main(int argc, char ** argv){
    
    if ( argc !=2 ){
        error(ERROR_WRONG_EXECUTION_FORMAT);
    }
    
    char * fileName = argv[1];
    openFile(fileName);
    
    printf("Parsing file...");
    parseFile();
    printf(" Success.\n");
    //printInstructions();
    printf("Step by step execution:\n");
    char temp;
    printf("(press enter to continue)\n");
    scanf("%c", &temp);
    run();
    return 0;
}