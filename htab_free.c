// htab_free.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// clears and frees hashtable

#include "htab.h"
#include "htab_private.h"

void htab_free(htab_t * t)
{
    // clears hashtable
    htab_clear(t);
    // frees hashtable
    free(t);
}