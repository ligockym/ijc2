#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Find in a table t item by key and if
 * - it finds, returns pointer to item
 * - it does not find, add item and returns pointer to item
 * @param t
 * @param key
 * @return
 */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key) {
    htab_pair_t *pair = htab_find(t,key);

    if (pair) { // if found -> return pair
        return pair;
    } else {
        // did not find -> add key to table to appropriate index
        size_t index = htab_hash_function(key) % htab_bucket_count(t);
        htab_item_t *new_item = htab_init_item(key, 0);

        // find chain where item will be placed
        htab_item_t *item = t->array[index];

        if (item) {
            // loop through a chain until last item -> find last
            while(item->next != NULL) {
                item = item->next;
            }

            // append new item to the end of a chain
            item->next = new_item;
        } else {
            // set as head of a chain
            t->array[index] = new_item;

        }

        t->size++;
        return &new_item->pair;
    }
}