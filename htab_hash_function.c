// htab_hash_function.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// hash function for hashtable

#include <stdint.h> // uint32_t
#include "htab.h"
#include "htab_private.h"

size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;     // must be 32 bits
    const unsigned char *p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}