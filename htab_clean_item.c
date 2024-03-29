/**
 * htab_clean_item.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Clean allocated memory for an item.
 * @param item
 */
void htab_clean_item(htab_item_t *item) {
    free((void *) item->pair.key);
    item->pair.key = NULL;
    free(item);
    item = NULL;
}