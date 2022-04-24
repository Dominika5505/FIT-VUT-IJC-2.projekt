// htab_item_init.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// creates individual item

#include "htab.h"
#include "htab_private.h"

htab_item_t * htab_item_init(htab_key_t key)
{
    // pointer to new item
    htab_item_t *new_item = malloc(sizeof(htab_item_t));
    if (new_item == NULL) return NULL;

    // allocate memory for key
    new_item->pair.key = malloc(strlen(key) + 1);

    // check allocation
    if (new_item->pair.key == NULL)
        return NULL;

    // copy key to new
    strcpy((char *)new_item->pair.key, key);
    new_item->next = NULL;
    new_item->pair.value = 0;

    return new_item;
}