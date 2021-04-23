/**
 * htab_bucket_count.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Returns size of array of pointers to items (.arr_size)
 * @param t
 * @return
 */
size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}