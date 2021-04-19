#include "htab.h"
#include "htab_internal.h"

#include <stdlib.h>
#include <stdio.h>

void htab_free(htab_t * t) {
   htab_clear(t);
   free(t);
}