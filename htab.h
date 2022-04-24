// htab.h -- library interface htab (solution IJC-DU2)
// Licence: none (Public domain)

// the following lines prevent multiple insertions:
#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool

// Table:
struct htab;    // incomplete structure declaration - user does not see content
typedef struct htab htab_t;     // typedef according to the task

// Typy:
typedef const char * htab_key_t;        // key type
typedef int htab_value_t;               // value type

// Dvojice dat v tabulce:
typedef struct htab_pair {
    htab_key_t    key;          // key
    htab_value_t  value;        // asociated value
} htab_pair_t;                  // typedef according to the task

// Hash function (same for all tables in the program)
// If you define the same function in the program, yours will be used.
size_t htab_hash_function(htab_key_t str);

// Functions for working with a table:
htab_t *htab_init(size_t n);                    // table constructor
htab_t *htab_move(size_t n, htab_t *from);      // move data to a new table
size_t htab_size(const htab_t * t);             // number of records in the table
size_t htab_bucket_count(const htab_t * t);     // size of array

htab_pair_t * htab_find(htab_t * t, htab_key_t key);  // searching
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key);

bool htab_erase(htab_t * t, htab_key_t key);    // clears the entered record

// for_each: goes through all the records and calls the function f on them
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data));

void htab_clear(htab_t * t);    // clears all records
void htab_free(htab_t * t);     // table destructor

#endif // __HTAB_H__