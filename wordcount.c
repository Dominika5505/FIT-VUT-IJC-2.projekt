// wordcount.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// counts number of occurences of words

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_print.h"
#include "io.h"

// there are about up to 30,000 different words used by each individual, I took last prime number before 30,000 for better hashtable optimalization
#define HTAB_SIZE 29989

// maximum length for read words
#define MAX_WORD_LENGTH 127

// prints final words with number of occurences
void print_words(htab_pair_t *data)
{
    printf("%s\t%d\n", data->key, data->value);
}

// increments value of data
void increment_value(htab_pair_t *data)
{
    data->value++;
}

int main(void)
{
    // initiates new hashtable
    htab_t *m = htab_init(HTAB_SIZE);
    // if something went wrong print error and end execution
    if (m == NULL) {
        fprintf(stderr, "ERROR: Initiation failed!\n");
        return 1;
    }

    // buffer for read words
    char word[MAX_WORD_LENGTH + 1];
    // pointer for returning value of adding items to hashtable
    htab_pair_t *ret_add;
    // pointer for returning value of finding items in hashtable
    htab_pair_t *ret_find;

    // reads from file/stdin until EOF occured
    while (read_word(word, MAX_WORD_LENGTH, stdin) != EOF) {
        // skips char/word if \0 is encountered
        if (word[0] == '\0')
            continue;

        // looks for a key or adds, if it wasn't found 
        ret_add = htab_lookup_add(m, word);

        // if something went wrong, prints error, frees table and ends execution
        if (ret_add == NULL) {
            fprintf(stderr, "ERROR: Could't insert item!\n");
            htab_free(m);
            return 1;
        }
        // finds item by key in hashtable
        ret_find = htab_find(m, word);
        // if item found, increments it't value
        if (ret_find != NULL) increment_value(ret_find); 
    }

    #ifdef MOVETEST

        htab_t *m2 = htab_move(HTAB_SIZE, m);
        if (m2 == NULL) {
            fprintf(stderr, "ERROR: Initiation failed!\n");
            return 1;
        }

        htab_free(m2);

    #endif

    // prints key and it's value, for each item
    htab_for_each(m, print_words);
    // frees table
    htab_free(m);

    return 0;
}