/**
 * htab_free.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

void htab_free(htab_t * t) {
   htab_clear(t);
   free(t);
}