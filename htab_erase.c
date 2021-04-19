#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Remove item from the table. Returns boolean value whether erase was successful.
 * @param t
 * @param key
 * @return
 */
bool htab_erase(htab_t * t, htab_key_t key){
    size_t index = htab_hash_function(key) % htab_bucket_count(t);

    htab_item_t *previous = NULL;
    htab_item_t *item = t->array[index];

    if (item) {
        // loop through the chain
        while (item) {
            if (strcmp(item->pair.key, key) == 0) { // check if item was found
                if (previous) {
                    // previous item exists -> change linking
                    previous->next = item->next;
                } else {
                    // first item of chain -> set pointer to next item
                    t->array[index] = item->next;
                }
                htab_clean_item(item);
                t->size--;
                return true;
            }

            previous = item;
            item = item->next;
        }
    }

    return false;
}