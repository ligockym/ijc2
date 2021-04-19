#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Remove all items from table.
 * @param t
 */
void htab_clear(htab_t * t) {
    size_t buckets = htab_bucket_count(t);

    // loop through buckets
    for (int i = 0; i < buckets; ++i) {
        htab_item_t *item = t->array[i];

        // clean every item in the bucket
        while(item != NULL) {
            htab_item_t *to_delete = item;
            item = item->next;
            htab_erase(t, to_delete->pair.key);
        }
    }
}