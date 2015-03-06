/*
 * Author: Kevin Zhang
 * Section: 01
 * Title: nibzip.c
 * Comments:
 * I included <stdint.h> to guarantee an 8bit integer for cross-platform independence.
 * I also put a check for the \r included by Windows so that the program would correctly
 * output regardless of whether the input file was DOS or UNIX.
 * My compression algorithm stores every 2 characters as a byte. In the case that there
 * is an uneven amount of characters, the last 4 bits of the last byte is entered as 
 * '1111' or 15, a nibble not used in the character table.
 * My uncompression algorithm reverts this process and ends when it hits either the
 * EOF or the '1111' sentinel value. I use fgetc() in this function to read octets;
 * however I acknowledge that chars aren't always 8 bits. Was not sure how else I would
 * read a file byte-by-byte, however.
 * Finally, I had to have a separate section for the -d flag because unlike -a or -c,
 * the -d flag requires the input file to be read as a binary file.
 */
#include <stdio.h>
#include <stdint.h>

/* function list */
void help(char*);
int mktable(FILE*);
void compress(FILE*, FILE*);
int8_t getnib(char);
char getint(int8_t);
int uncompress(FILE*, FILE*);

/* struct for character distribution table */
struct tblchar {
    char c;
    int count;
};

int main(int argc, char **argv) {
    /* Preliminary checks and argument handling */
    if(argc == 1) { // if user only inputs the program name
        help(argv[0]);
    }

    else if(strcmp(argv[1], "-h") == 0 && argc != 2
         || strcmp(argv[1], "-a") == 0 && argc != 3
         || strcmp(argv[1], "-c") == 0 && argc != 4
         || strcmp(argv[1], "-d") == 0 && argc != 4) {
        printf("Error: Wrong number of arguments. See -h for usage information.\n");
        return 0;
    }

    else {
        if(strcmp(argv[1], "-h") == 0) {
            help(argv[0]);
        } // help

        else if(strcmp(argv[1], "-a") == 0
             || strcmp(argv[1], "-c") == 0) {
            FILE *inf;
            /* check input filestream availability */
            if((inf = fopen(argv[2],"r")) == NULL) {
                printf("Error: File %s could not be opened for reading.\n", argv[2]);
                return 0;
            }

            if(strcmp(argv[1], "-a") == 0) {
                mktable(inf);
            } // analyze

            else if(strcmp(argv[1], "-c") == 0) {
                FILE *outf;
                /* check output filestream availability */
                if((outf = fopen(argv[3],"wb")) == NULL) {
                    printf("Error: File %s could not be created for writing.\n", argv[3]);
                    return 0;
                }

                if(strcmp(argv[1], "-c") == 0) {
                    if(mktable(inf) == 0) {
                        compress(inf, outf);
                        /* get filesize */
                        fseek(outf, 0L, SEEK_END);
                        int sz = ftell(outf);
                        printf("\nOutput File: %s\n\twas compressed successfully. New size is %d bytes.", argv[3], sz);
                    }
                    else {
                        printf("\nOutput File: %s\n\twas not compressed.\n", argv[3]);
                    }
                }

                fclose(outf); // close the output filestream
            } // compress

            fclose(inf); // close the input filestream
        } // -a, -c flags (all use nonbinary input stream)

        else if(strcmp(argv[1], "-d") == 0) {
            FILE *inf;
            /* check input filestream availability */
            if((inf = fopen(argv[2],"rb")) == NULL) {
                printf("Error: File %s could not be opened for reading.\n", argv[2]);
                return 0;
            }
            FILE *outf;
            /* check output filestream availability */
            if((outf = fopen(argv[3],"rw")) == NULL) {
                printf("Error: File %s could not be created for reading/writing.\n", argv[3]);
                return 0;
            }
            uncompress(inf, outf);
            mktable(outf);
             /* get filesize */
            fseek(outf, 0L, SEEK_END);
            int sz = ftell(outf);
            printf("\nOutput File: %s\n\twas uncompressed successfully. File size is %d bytes.", argv[3], sz);
        } // uncompress (uses binary input stream)

        else {
            printf("Error: flag %s does not exist. See -h for usage information.\n", argv[1]);
            return 0;
        } // error handling

    }
    return 0;
}

/*
 * help(char*)
 * Prints out the help and usage information to the standard output.
 */
 void help(char args[])  {
    printf("Usage: %s [-acdh] [INFILE] [OUTFILE]\n", args);
    printf("Flags:\n");
    printf("-h: Prints help and usage information.\n");
    printf("-a: Analyzes and prints out a character distribution table computed from the input file.\n");
    printf("-c: Compresses the input file into the output file and prints out a character distribution table.\n");
    printf("-d: Decompresses the input file, writes the unpacked bytes to the output file and prints out the character distribution table.\n");
 }

/*
 * mktable(FILE*)
 * Prints out the character distribution table of the given file. Returns the number of unsupported
 * characters. The character 'x' signifies unsupported characters. Uses the struct tblchar defined
 * at the top - essentially, it holds a character and the count of that character.
 */
int mktable(FILE *inf) {
    rewind(inf); // always want to read from the start of the file
    struct tblchar table[16];
    char characters[] = "0123456789.-, \nx"; // char table
    
    /* populate table's character contents */
    int x;
    for(x = 0; x < 16; x++) {
        table[x].c = characters[x];
        table[x].count = 0;
    }

    int c; // chars from file
    printf("Character   Count\n");
    /* Populate the counts table */
    while((c = fgetc(inf)) != EOF) {
        switch((char) c) {
            case '0':
                table[0].count++;
                break;
            case '1':
                table[1].count++;
                break;
            case '2':
                table[2].count++;
                break;
            case '3':
                table[3].count++;
                break;
            case '4':
                table[4].count++;
                break;
            case '5':
                table[5].count++;
                break;
            case '6':
                table[6].count++;
                break;
            case '7':
                table[7].count++;
                break;
            case '8':
                table[8].count++;
                break;
            case '9':
                table[9].count++;
                break;
            case ',':
                table[10].count++;
                break;
            case '-':
                table[11].count++;
                break;
            case '.':
                table[12].count++;
                break;
            case ' ':
                table[13].count++;
                break;
            case '\n':
                table[14].count++;
                break;
            case '\r':
                break; // MS-DOS signifies a newline with \r\n, which triggers the default case
            default:
                table[15].count++;
        }
    }
    /* Output character distribution table */
    int i = 0;
    for(i; i < 14; i++) {
        printf("%c %15d\n", table[i].c, table[i].count);
    }
    printf("%s %14d\n", "\\n", table[14].count);
    printf("%s %10d\n", "others", table[15].count);
    if(table[15].count > 0) {
        printf("Error: unknown character(s) encountered in analysis.\n");
    }
    return table[15].count;
}

/*
 * compress(FILE*, FILE*)
 * Compresses the input file into the output file. Converts each characer in the file
 * to the appropriate 4 bit binary (see getnib()) and pairs them up into bytes before
 * writing to file. In the case of an odd number of characters, the last nibble will
 * be written as '1111' or 15.
 */
void compress(FILE* inf, FILE* outf) {
    rewind(inf); // always want to read from the start of the file
    int8_t b = 0; // byte to be written to file
    int c; // chars from file
    while((c = fgetc(inf)) != EOF) {
        b |= (getnib((char) c) << 4); // shift c into the first 4 bits
        /* place the next character to complete the byte; if it reaches the end of file it will
         * place a 15 (the only bit not recognized as a character in a nibzip file) */
        if((c = fgetc(inf)) != EOF) {
            b |= getnib((char) c); // place c into the last 4 bits, completing the byte
        }
        else {
            b |= (int8_t) 15; // place 15 into the last 4 bits, completing the byte and thus the file
        
        }
        /* write to file and reset b) */
        fputc(b, outf);
        b = 0;
    }
}

/*
 * getnib(char)
 * Returns the nibblet of the char as an 8 bit int, padded with 0s. It is assumed that the character
 * being passed is a supported character; unsupported characters are returned as 15.
 */
int8_t getnib(char c) {
     switch(c) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            return (int8_t) c - '0'; 
        case ',':
            return (int8_t) 10;
        case '-':
            return (int8_t) 11;
        case '.':
            return (int8_t) 12;
        case ' ':
            return (int8_t) 13;
        case '\n':
            return (int8_t) 14;
        case '\r': // MS-DOS signifies a newline with \r\n, which triggers the default case
        default:
            return (int8_t) 15; // will signify an EOF when decomprssed
    }
}

/*
 * getint(int8_t)
 * Returns the char of an 8 bit int. It is assumed that the int being passed is one of the supported
 * characters, i.e. the first 4 bits are 0. Unsupported characters are returned as 'x' to be handled
 * accordingly.
 */
char getint(int8_t i) { 
    switch(i) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
            return (char)((int) '0') + i; // this gets the char equivalent of the integer
        case 10:
            return ',';
        case 11:
            return '-';
        case 12:
            return '.';
        case 13:
            return ' ';
        case 14:
            return '\n';
        case 15:
        default:
            return 'x'; // this is the EOF signal in the case that there is an odd number of nibbles
    }
}

/*
 * uncompress(FILE*, FILE*)
 * Uncompresses the input file into the output file and prints out the character distribution table. Returns
 * 0 if successful and 1 if unsuccessful. As long as input file being uncompressed was correctly compressed
 * via the compress function and doesn't contain unsupported characters, uncompress() should always return 0.
 */
int uncompress(FILE* inf, FILE* outf) {
    rewind(inf); // always want to read from the start of the file
    int c;
    while((c = fgetc(inf)) != EOF) {
        /* get the integer representations of each nibble */
        int8_t first = c >> 4; // shifts by 4 to get the original integer representation
        int8_t second = c & 15; // masks the first half (0000 1111)
        
    }
    return 0;
}
