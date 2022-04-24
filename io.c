// io.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// function that reads word (or max characters from word)

#include "io.h"

int read_word(char *s, int max, FILE *f) 
{
    // variable for reading character
    int c;
    // declares statis variable, that counts how many words are longer than max
    static int is_longer_counter = 0;
    // declares statis variable, that shows if line is longer and should be skipped
    static bool is_longer = false;
    // position of current spot in buffer
    int s_position = 0;

    // reads char by char from file
    while ((c = fgetc(f))) {

        // if EOF found returns EOF
        if (c == EOF) {
            s[0] = '\0';
            return EOF;
        } 

        // space character found
        if (isspace(c)) {
            // is longer boolean is resseted to false, so reading would start again
            is_longer = false;
            break;
        }

        // if word is longer than allowed
        if (s_position > (max - 1)) {
            // increase counter of longer lines
            is_longer_counter++;

            // if longer line occured first time print warning on stderr
            if (is_longer_counter == 1) {
                fprintf(stderr, "WARNING! - line is too long, from now, lines longer than %d characters will be trimmed.\n", max);
            }
            // set is longer to true, so rest of the word would be skipped
            is_longer = true;

            break;
        }
        
        // read chars to array
        if (!is_longer) {
            s[s_position] = c;        
            s_position++;
        }
    }

    // sets closing string character
    s[s_position] = '\0';

    // returns length of word
    return s_position;
}