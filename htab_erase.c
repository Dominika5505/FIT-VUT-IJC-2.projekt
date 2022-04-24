// htab_erase.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// 

#include "htab.h"
#include "htab_private.h"

bool htab_erase(htab_t * t, htab_key_t key) 
{
    // saves index returned from hash function of passed key
    ul index = htab_hash_function(key) % t->arr_size;
    // saves head of linked-list on index in array of hashtable into current variable
    htab_item_t *current = t->item[index];    
    // create variable for previous item
    htab_item_t *prev = NULL;

    // loops through list while current item is not empty or if key isn't found
    while (current != NULL && strcmp(current->pair.key, key) != 0) {        
        // saves current item to previous
        prev = current;
        // current is moved to next item
        current = current->next;
    }

    // if current index is empty item with key wasn't found
    if (current == NULL) return false;

    // if prev is NULL, current is head of the list
    if (prev == NULL) {

        // saves second item as head of the list
        t->item[index] = current->next;
        // decrements size of hashtable
        t->size--;
        // frees item that is supposed to be erased
        htab_item_free(current);
        // deleted correctly
        return true;
        
    // current is not head of the list
    } else {

        // item after current is placed onto current's spot
        prev->next = current->next;
        // decrements size of hashtable
        t->size--;
        // frees item that is supposed to be erased
        htab_item_free(current);
        // deleted correctly
        return true;
        
    }

    // key wasn't erased
    return false;
}