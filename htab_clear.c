// htab_clear.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// function that removes all items from table

#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t * t)
{
    // loops through the table array
    for (ul i = 0; i < t->arr_size; i++) {
        // declares temporary variable for storing items
        htab_item_t *tmp;

        // loops while first item in array on index (head of linked-list) is not empty
        while (t->item[i] != NULL) {
            
            // saves pointer to next item in linked-list to tmp
            tmp = t->item[i]->next;
            // frees first item (head of linked-list)
            htab_item_free(t->item[i]);

            // sets head of list to tmp
            t->item[i] = tmp;
        }
    }

    // resets table's size to 0
    t->size = 0;
}