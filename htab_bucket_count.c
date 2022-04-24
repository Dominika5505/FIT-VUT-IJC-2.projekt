// htab_bucket_count.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// function that returns array size of hashtable

#include "htab.h"
#include "htab_private.h"

size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}