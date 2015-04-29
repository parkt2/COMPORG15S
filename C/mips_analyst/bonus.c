/*
 * Author: Kevin Zhang
 * Section: 01
 * Title: bonus.c
 * Comments:
 * 
 */
#include <stdio.h> // general I/O functions
#include <stdlib.h> // certain overloaded functions (malloc in particular)

/* function list */
void help(char*);

int main(int argc, char **argv) {
    /* Preliminary checks and argument handling */
    if(argc == 1) { // if user only inputs the program name
        help(argv[0]);
    }
    /* Actual execution */
    else if(argc == 3) {

    }
    /* Errors */
    else {
    	printf("Error: Wrong number of arguments. Run without arguments for usage information.\n");
    }
    return 0;
}

/*
 * help(char*)
 * Prints out the help and usage information to the standard output.
 */
void help(char args[])  {
    printf("Usage: %s [INFILE] [OUTFILE]\n", args);
    printf("Summary:\n");
    printf("Analyzes a MIPS program and prints out a reference table of identifiers.\n");
}