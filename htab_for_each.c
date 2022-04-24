// htab_for_each.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// executes function for each item in hashtable

#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    // loops through array in hashtable (heads of linked-lists)
    for (ul i = 0; i < t->arr_size; i++) {
        // saves current head as current item
        htab_item_t *current = t->item[i];

        // while current item is not empty
        while (current != NULL) {
            // executes function on current item
            f(&(current->pair));
            // moves current item to next one
            current = current->next;
        }
    }
}