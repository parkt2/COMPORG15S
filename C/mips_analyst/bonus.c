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
void print_table(FILE*, struct tblref*, int);
int whitespace(char);
char fpeek(FILE*);
void go_to_n(FILE*);

int main(int argc, char **argv) {
    /* Preliminary checks and argument handling */
    if(argc == 1) { // if user only inputs the program name
        help(argv[0]);
    }
    /* Actual execution */
    else if(argc == 3) {
    	FILE *inf, *outf;
    	struct tblref references[100]; // array holding all references
    	int tblsize = 0; // size of the above array

        /* check input filestream availability */
        if((inf = fopen(argv[1],"r")) == NULL) {
            printf("Error: File %s could not be opened for reading.\n", argv[1]);
            return 0;
        }

        /* check output filestream availability */
        if((outf = fopen(argv[2],"w")) == NULL) {
            printf("Error: File %s could not be created for writing.\n", argv[3]);
            return 0;
        }

        /* read file */
        analyze(inf, references);

        /* print file */
        print_file(inf, outf);

        /* print table */
        print_table(outf, references, tblsize);

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
	rewind(inf); // just in case
	char c;
	int newline = 1; // new line boolean
	int in_comment = 0; // comment boolean
	int line = 1; // line number
	while((c = fgetc(inf)) != EOF) {

		/* check if we're in a comment; if so, skip the line entirely */
		if(c == '#') go_to_n(inf);
		else printf("%c",c);

	}
}

/*
 * print_file(FILE*, FILE*)
 * Prints the input file.
 */
void print_file(FILE* inf, FILE* outf){
	rewind(inf);
	char c;
	int newline = 1; // new line boolean
	int line = 1; // line number
	while((c = fgetc(inf)) != EOF) {

		if(newline) {

			if(c != '\n') {
				fprintf(outf, "%d\t", line++);
				newline = 0;
			}

		} // print line number

		if(c == '\n') newline = 1;
		fprintf(outf, "%c", c);

	}
}

/*
 * print_table(FILE*, struct tblref*, int)
 * Prints the reference table array.
 */
void print_table(FILE *outf, struct tblref* references, int tblsize) {
	fprintf(outf, "\nIdentifier Reference Table\n\n");
	fprintf(outf, "\tIdentifier Definition-Line Use Line(s)\n");
	int i, j;
	for(i = 0; i < tblsize; ++i) {
		fprintf(outf, "\t%-11s", references[i].identifier);
		fprintf(outf, "%-16d", references[i].defined);
		for(j = 0; j < 10; ++j) {
			fprintf(outf, "%-4d", references[i].lines[j]);
		}
		fprintf(outf, "\n");
	}
}

/*
 * int whitespace(char)
 * Small helper function that determines whether something is whitespace.
 */
 int whitespace(char c) {
 	if(c == EOF || c == '\r' || c == '\t' || c == '\n' || c == ' ') return 1;
 	return 0;
 }

 /*
  * char fpeek(FILE*)
  * Small helper function that peeks at the next character in a filestream.
  */
char fpeek(FILE *fstream) {
	char c;
	c = fgetc(fstream);
	ungetc(c, fstream);
	return c;
}

/*
 * void go_to_n(FILE*)
 * Small helper function that skips to the end of line or file in a filestream.
 */
 void go_to_n(FILE* fstream) {
 	char c;
 	while((c = fgetc(fstream)) != EOF) {
 		if(c == '\n') {
 			ungetc('\n', fstream); // return back to newline
 			return;
 		}
 	}
 }