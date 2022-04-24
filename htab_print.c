// htab_print.c
// Solution IJC-DU2, example b), 13.4.2021
// Author: Dominika Sedileková, FIT
// Translated: gcc version 8.2.0 (GCC)
// prints content of hashtable

#include "htab_print.h"

void htab_print(htab_t *t) 
{
    // prints start mark
    printf("\n----START----\n\n");

    // loops through table 
    for (ul i = 0; i < t->arr_size; i++) {
        // if linked-list on index is empty prints index and  ---
        if (t->item[i] == NULL) {

            printf("  %ld\t----\n", i);
        // if not empty
        } else {
            // prints index
            printf("  %ld\t", i);
            // saves head of linked-list as current item 
            htab_item_t *current = t->item[i];

            // loops while current item is not empty
            while (current != NULL) {
                // prints key of current item
                printf("%s", current->pair.key);

                // next item is not empty
                if (current->next != NULL) {
                    printf(" --> ");
                }
                
                // moves current to next item
                current = current->next;
            }
            
            printf("\n");   
        }
    }

    // prints number of items in hashtable, size of array and end mark
    printf("\n  size: %ld\n", htab_size(t));
    printf("  arr_size: %ld\n", htab_bucket_count(t));
    printf("\n-----END-----\n\n");
}