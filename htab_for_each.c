/**
 * htab_for_each.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Do a function for each item.
 * @param t
 * @param f
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    size_t buckets = htab_bucket_count(t);
    // Loop through each bucket
    for (int i = 0; i < buckets; i++) {
        htab_item_t *item = t->array[i];

        while(item != NULL) {
            // Call function for each pair.
            f(&item->pair);
            item = item->next;
        }
    }
}