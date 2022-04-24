// io.h
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// header for io.c

#include "htab.h"
#include <stdio.h> // FILE, NULL
#include <ctype.h> //isspace

// read word (or max characters from word)
int read_word(char *s, int max, FILE *f);