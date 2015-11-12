#include <unistd.h>
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
	
	int c;
	int flagCount = 0;
	int studyMode = 0;
	opterr = 0;

	while ( (c = getopt (argc, argv, "s")) != -1 ){
		flagCount++;
		switch (c)
		{
			case 's':
				studyMode = 1;
				printf("DANI");
			break;
			case '?':
				if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n",	optopt);
				return 1;
			default:
				abort ();
		}
	}

	//if ( argc !=2 ){
		//error(ERROR_WRONG_EXECUTION_FORMAT);
	//}
	
	char * fileName = argv[1+flagCount];
	openFile(fileName);
	
	printf("Parsing file...");
	parseFile();
	printf(" Success.\n");

	if ( studyMode )
	{
		printInstructions();
		printf("Step by step execution:\n");
		char temp;
		printf("(press enter to continue)\n");
		scanf("%c", &temp);
	}
	run(studyMode);
	return 0;
}