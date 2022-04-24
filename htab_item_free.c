// htab_item_free.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// removes and frees individual item

#include "htab.h"
#include "htab_private.h"

void htab_item_free(htab_item_t *item)
{
    // frees key pointer
    free((char *)item->pair.key);
    // frees item
    free(item);
    // sets item back to NULL
    item = NULL;
}