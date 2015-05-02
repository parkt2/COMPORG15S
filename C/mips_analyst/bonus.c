/*
 * Author: Kevin Zhang
 * Section: 01
 * Title: bonus.c
 * Comments:
 * 
 */
#include <stdio.h> // general I/O functions
#include <stdlib.h> // certain overloaded functions (malloc in particular)

/* struct for identifier reference table */
struct tblref {
    char *identifier;
    int defined;
    int *lines;
};

/* function list */
void help(char*);
void analyze(FILE*, struct tblref*);
void print_file(FILE*, FILE*);
void print_table(struct tblref*);

int main(int argc, char **argv) {
    /* Preliminary checks and argument handling */
    if(argc == 1) { // if user only inputs the program name
        help(argv[0]);
    }
    /* Actual execution */
    else if(argc == 3) {
    	FILE *inf, *outf;
    	struct tblref references[100];

        /* check input filestream availability */
        if((inf = fopen(argv[1],"r")) == NULL) {
            printf("Error: File %s could not be opened for reading.\n", argv[1]);
            return 0;
        }

        /* check output filestream availability */
        if((outf = fopen(argv[3],"w")) == NULL) {
            printf("Error: File %s could not be created for writing.\n", argv[3]);
            return 0;
        }

        /* read file */
        analyze(inf, references);

        /* print file */
        print_file(inf, outf);

        /* print table */
        print_table(outf, references);

        /* close filestreams */
        fclose(inf);
        fclose(outf);
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

/*
 * analyze(FILE*, struct tblref*)
 * Reads in the file and updates the given reference table array.
 */
void analyze(FILE *inf, struct tblref* references) {

}

/*
 * print_file(FILE*, FILE*)
 * Prints the input file.
 */
void print_file(FILE* inf, FILE* outf){
	rewind(inf);
	while((c = fgetc(inf)) != EOF) {

	}
}

/*
 * print_table(struct tblref*)
 * Prints the reference table array.
 */
void print_table(struct tblref*) {

}