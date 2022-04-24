// tail.c
// Solution IJC-DU2, example a), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// implementation of POSIX-like tail command

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// limit for number of characters in ine line
#define CHAR_PER_LINE 511
// limit for number of characters in filename (goes for full path), most systems use this number
#define FILENAME_LIMIT 255

// checks if number is valid after argument
bool is_valid_num(char *str)
{
    // anything other than number or +/- sign will be stored here
    char *junk;
    // finds number in string and returns it, the rest will be moved to junk variable
    long ret = strtol(str, &junk, 10);
    // if junk isn't empty and present characters are anything else than + sign, value is invalid
    if (strlen(junk) != 0 && strcmp(junk, "+") != 0)
        return false;
    // negative number is invalid 
    if (ret < 0) 
        return false;
    // number is valid
    return true;
}

// converts string to number
int convert_to_num(char *num_to_convert)
{
    // anything other than number or +/- sign will be stored here
    char *junk;
    // finds number in string and returns it, the rest will be moved to junk variable
    long ret = strtol(num_to_convert, &junk, 10);

    // returns number
    return (int)ret;
}


int main(int argc, char **argv)
{
    // buffer for text from file or stdin
    char *filename = NULL;
    FILE *fptr = stdin;

    // number of lines, that are supposed to be printed
    int print_lines_num = 10;
    // bool num_found = false;

    if (argc > 1) {
        // loop through args if there are some
        for (int i = 1; i < argc; i++) {
            // if -n is found
            if (!strcmp(argv[i], "-n")) {
                // check value after -n (if it's valid number)
                if (is_valid_num(argv[i + 1])) {
                    // change number of lines, that are supposed to be printed
                    print_lines_num = convert_to_num(argv[i + 1]);
                } else {
                    fprintf(stderr, "WARNING! - number after -n switch is not valid. Value 10 will be used instead.\n");
                }
                // move over one argument (number value of -n will be skipped)
                i++;
            // rest or arguments should contain only filename 
            } else {
                // checks length of filename
                if (strlen(argv[i]) > FILENAME_LIMIT) {
                    fprintf(stderr, "ERROR! - filename is too long.\n");
                    // fptr = stdin;
                    return 1;
                }
                // allocates space for filename
                filename = malloc(FILENAME_LIMIT);

                // checks allocation
                if (filename == NULL) {
                    // fptr = stdin;
                    fprintf(stderr, "ERROR! - filename allocation failed.\n");
                }

                // saves filename from argument
                strcpy(filename, argv[i]);
            }
        }
    }

    // saves size for allocation of buffer
    // + 1 added for terminate symbol '\0' 
    int alloc_size = CHAR_PER_LINE * print_lines_num;
    // creates and allocates buffer 
    char *buffer = malloc(alloc_size);
    // checks allocation of buffer
    if (buffer == NULL) {
        fprintf(stderr, "ERROR! - buffer allocation failed.\n");
        return 1;
    }

    // check if filename exists
    if (filename != NULL) {
        // open file
        fptr = fopen(filename, "r");
        // if file did not open throw error
        if (fptr == NULL) {
            fprintf(stderr, "ERROR! - couldn't open the file.\n");
            fptr = stdin;
            return 1;
        } 
    }

    // position in buffer, where character will be written
    int buffer_pos = 0;
    // number of lines in file
    int line_counter = 0;

    // variable for reading inputs from file by chars
    int c;
    // number of characters in one line
    int char_per_line_counter = 0;
    // how many lines are longer than they should be
    int longer_lines_count = 0;
    // check if line is longer than it should be
    bool longer_line = false;

    // reads from file or stdin
    while ((c = fgetc(fptr)) != EOF) {
    // while ((c = fgetc((filename != NULL && fptr != NULL) ? fptr : stdin)) != EOF) {
        
        // if currently read chars are longer than allocated buffer size
        if (buffer_pos > alloc_size) {
            // reallocates buffer and adds size of one line to it
            buffer = realloc(buffer, (alloc_size) + CHAR_PER_LINE);
            // allocation size is recalculated
            alloc_size += CHAR_PER_LINE;
            // checks if reallocation went through
            if (buffer == NULL) {
                fprintf(stderr, "ERROR! - buffer reallocation failed.\n");
                return 1;
            }
        }
    
        // if characters in line are longer, than allowed length 
        // (>=) char_per_line_counter goes from 0, so char_per_line_counter + 1 == CHAR_PER_LINE
        if (char_per_line_counter >= CHAR_PER_LINE) {
            longer_lines_count++;
            // sets longer_line to true, so the rest of characters on this line would not be copied 
            longer_line = true;

            // writes warning for longer lines only first time it occured
            if (longer_lines_count == 1) {
                fprintf(stderr, "WARNING! - line is too long, from now, lines longer than %d characters will be trimmed.\n", CHAR_PER_LINE);
            }

            // cuts current line by newline symbol
            buffer[buffer_pos] = '\n';
        }

        // copies the character one by one to buffer only, when their length in line is in allowed range
        if (!longer_line) {
            buffer[buffer_pos] = c;
            (buffer_pos)++;
        }

        char_per_line_counter++;

        // if new line is found
        if (c == '\n') {
            // character per line is resetted to 0 
            char_per_line_counter = 0;
            // line counter is increased
            (line_counter)++;
            // longer file resetted to false, so characters on next iteration (line) would be copied
            longer_line = false;
        }
    }

    // adds terminating symbol to the end of buffer
    buffer[buffer_pos] = '\0';

    // if number of lines user wants to print is bigger than number of lines in file, whole file is printed
    if (print_lines_num > line_counter) {
        printf("%s", buffer);
    } else {
        // initial value of number of lines in buffer 
        int buffer_line_counter = 0;

        // loops through buffer to find beginning position of nth line (nth = print_lines_num)
        while (buffer_line_counter <= print_lines_num) {
            // line counter increased
            if (buffer[buffer_pos] == '\n') {
                buffer_line_counter++;
            }
            // character position in buffer decreased to find beggining position
            buffer_pos--;
        }

        // buffer position increased by to 2
        // first increase = buffer_pos endid on last character of previous line
        // second increase = currently, buffer_pos is on \n of previous line. We increase it to get to the beginning of wanted line
        buffer_pos += 2;

        // loops through buffer and prints all characters 
        while (buffer[buffer_pos] != '\0') {
            printf("%c", buffer[buffer_pos]);
            buffer_pos++;
        }
    }

    // frees allocated memory and closes opened file
    if (buffer != NULL)
        free(buffer);
    if (filename != NULL)
        free(filename);
    if (fptr != stdin)
        fclose(fptr);

    return 0;
}