// htab_init.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// initiates hashtable and sets all items to null

#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n)
{    
    // allocates space for table + number of items to be stored in hashtable as array
    htab_t *table = malloc(sizeof(htab_t) + n * sizeof(htab_item_t *));
    // allocation was not successful
    if (table == NULL) return NULL;

    // loops thorough each item and sets them to null
    for (ul i = 0; i < n; i++) {
        table->item[i] = NULL;
    }
    
    // saves size of array
    table->arr_size = n;
    // sets number of items to 0
    table->size = 0;

    return table;
}