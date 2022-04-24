// htab_size.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// returns number of items in hashtable

#include "htab.h"
#include "htab_private.h"

size_t htab_size(const htab_t * t)
{
    return t->size;
}