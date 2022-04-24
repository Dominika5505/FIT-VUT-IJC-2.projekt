// htab_lookup_add.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// looks for item in hashtable by passed key and returns pointer to it if found, or creates new one if not found

#include "htab.h"
#include "htab_private.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) 
{   
    // find index of key in table
    ul index = htab_hash_function(key) % t->arr_size;

    // current set to head on index
    htab_item_t *current = t->item[index];
    // pointer to previous item on index
    htab_item_t *prev = NULL;
    
    while (current != NULL) {
        // if item is found return pointer to it
        if (strcmp(current->pair.key, key) == 0) {
            return &(current->pair);
        }
        // previous moved to current item
        prev = current;
        // current moved to next item
        current = current->next;
    }

    // creates new item
    htab_item_t *new = htab_item_init(key);
    // allocation went wrong
    if (new == NULL) return NULL;

    // increments number of items in hashtable
    t->size++;

    // if previous is NULL, sets new item as header of linked-list
    if (prev == NULL) {
        t->item[index] = new;
    // sets after last item on sam index
    } else {
        prev->next = new;
    }
    // returns pointer to new item address
    return &(new->pair);
}