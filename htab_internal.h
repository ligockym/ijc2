/**
 * htab_internal.h
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include <stdlib.h>
#include "htab.h"

#ifndef __HTAB_STRUCTS__
#define __HTAB_STRUCTS__

struct htab_item {
    struct htab_item *next;
    htab_pair_t pair;
};
typedef struct htab_item htab_item_t;

struct htab {
    int size;
    int arr_size;
    htab_item_t * array[];
};

htab_item_t *htab_init_item(htab_key_t key, htab_value_t value);
void htab_clean_item(htab_item_t *item);

#endif