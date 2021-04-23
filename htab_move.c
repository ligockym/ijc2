/**
 * htab_move.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "htab.h"
#include "htab_internal.h"

/**
 * Move data from one table to newly created. Content of old table is deleted.
 *
 * @param n number of items
 * @param from pointer to origin table
 * @return new table with data from first table
 */
htab_t *htab_move(size_t n, htab_t *from) {
    htab_t* table = htab_init(n);

    size_t from_size = htab_bucket_count(from);

    // loop through each of buckets
    for (int i = 0; i < from_size; i++ ) {
        htab_item_t *item = from->array[i];

        // loop through items until end
        while(item) {
            // copy item from old to new
            htab_pair_t *new_pair = htab_lookup_add(table, item->pair.key);
            new_pair->value = item->pair.value;

            // remove old table
            htab_item_t *to_remove = item;

            item = item->next;

            htab_erase(from, to_remove->pair.key);
        }
    }

    return table;
}
