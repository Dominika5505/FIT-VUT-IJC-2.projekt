// htab_find.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// finds item by key in hashtable

#include "htab.h"
#include "htab_private.h"
#include <string.h> // strcmp
// #include <stdio.h> // printf

htab_pair_t * htab_find(htab_t * t, htab_key_t key) 
{
    // saves index returned from hash function of passed key
    ul index = htab_hash_function(key) % t->arr_size;

    // saves head of inked-list on index ascurrent
    htab_item_t *current = t->item[index];

    // loops while curretn item is not empty
    while (current != NULL) {
        // compares current item's key with passed key
        if (strcmp(current->pair.key, key) == 0) 
            return &(current->pair);
        // moves current item to next
        current = current->next;
    }
    // item wasn't found
    return NULL;
}