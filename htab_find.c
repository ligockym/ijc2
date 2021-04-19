#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Find an item with the key and if it exists, returns pointer to it.
 * Otherwise returns pointer to null.
 * @param t
 * @param key
 * @return
 */
htab_pair_t *htab_find(htab_t *t, htab_key_t key) {
    // find position where key can be (does not have to)
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    htab_item_t *item = t->array[index];

    // loop through all items in the chain (including header)
    while (item != NULL) {
        if (strcmp(key, item->pair.key) == 0) { // check if keys match
            return &item->pair; // found
        }
        item = item->next; // move next in the chain
    }

    return NULL; // corresponding key was not found in the table
}