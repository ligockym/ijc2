#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Init item. Dynamic memory is used for item and key.
 * @param key
 * @param value
 * @return
 */
htab_item_t *htab_init_item(htab_key_t key, htab_value_t value) {

    // Alloc item
    htab_item_t *item = malloc(sizeof(htab_item_t));

    // if allocation failed
    if (item == NULL) {
        return NULL;
    }

    // key length with zero ending - space needed
    size_t key_len = strlen(key) + 1;

    // allocate space for key (string)
    char *key_str = malloc(key_len * sizeof(char));

    // if allocation failed
    if (key_str == NULL) {
        free(item); // free previously allocated item
        return NULL;
    }

    // copy key from parameter to newly allocated key_str
    strcpy(key_str, key);

    item->pair.key = key_str;
    item->pair.value = value;
    item->next = NULL;

    return item;
}