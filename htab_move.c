// htab_move.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// moves all items to new created table from table that is cleared after

#include "htab.h"
#include "htab_private.h"

htab_t *htab_move(size_t n, htab_t *from)
{
    // creates and initiates new table
    htab_t *new_table = htab_init(n);
    // allocation went wrong
    if (new_table == NULL) return NULL;

    // loops through all headers on index in hashtable, that will be copied from
    for (ul i = 0; i < from->arr_size; i++) {
        // saves current item as header of linked-list
        htab_item_t *current = from->item[i];        

        // loops while current item is not empty
        while (current != NULL) {
            // adds cretes hard copy of current item and adds it to destination table
            htab_lookup_add(new_table, current->pair.key);
            
            // moves current item to next one
            current = current->next;
        }
    }

    // clears table from which was copied
    htab_clear(from);

    // returns pointer to new table
    return new_table;
}