#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>


/**
 * Inits hash table
 * @param n
 * @return
 */
htab_t *htab_init(size_t n) {
    if (n == 0) {
        return NULL;
    }

    // Using flexible array member
    size_t size = n * sizeof(htab_item_t) + sizeof(htab_t);
    htab_t *table = malloc(size);

    // Check if malloc failed
    if (table == NULL) {
        return NULL;
    }

    table->size = 0;
    table->arr_size = n;
    // loop through all pointers and set NULL pointer
    for (int i = 0; i < n; ++i) {
        table->array[i] = NULL;
    }

    return table;
}