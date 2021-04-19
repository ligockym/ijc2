#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Return number of entries in the table (.size)
 * @param t
 * @return
 */
size_t htab_size(const htab_t * t) {
    return t->size;
}