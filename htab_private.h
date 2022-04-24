// htab_private.h
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// header file for private structs, functions and macros

#ifndef __HTAB_PRIVATE_H__
#define __HTAB_PRIVATE_H__

#include "htab.h"
#include <stdlib.h> // malloc, free
#include <stdio.h> // printf

#define ul unsigned long

typedef struct htab_item // single item
{
    htab_pair_t pair; // pair (key, data)
    struct htab_item *next; // pointer to next item
} htab_item_t;

struct htab
{
    unsigned long size; // current number of items
    unsigned long arr_size; // size of next pointer array
    htab_item_t *item[]; // pointer array to items
};

// creates individual item
htab_item_t * htab_item_init(htab_key_t key);

// removes and frees individual item
void htab_item_free(htab_item_t *item);

#endif