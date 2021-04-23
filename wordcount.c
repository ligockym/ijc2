/**
 * wordcount.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "htab.h"
#include "htab_internal.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>

/* Vybral som si ukazkovy priklad naplnenia hash tabulky textami anglickych noviel.
    https://writing.stackexchange.com/questions/6988/how-many-different-words-are-in-the-average-novel
    Priemerny pocet unikátnych slov je okolo 5000, takze vyberam prvocislo 5101 (lepsia funkcnost
     hashovacej funkcie)
     */
#define TABLE_SIZE 5101

void print_item(htab_pair_t *data) {
    printf("%s\t%i\n", data->key, data->value);
}

int main() {

    htab_t *table = htab_init(TABLE_SIZE);
    // check if allocation has failed
    if (table == NULL) {
        fprintf(stderr, "Allocation of memory has failed.\n");
        exit(1);
    }

    char *buffer = malloc(WORD_MAX * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Allocation of memory has failed.\n");
        htab_free(table);
        exit(1);
    }

    int read_len;
    int error_len = 0;
    enum print_error_enum{NO_ERROR, SHOULD_PRINT, PRINTED} print_error;

    // read words
    while ((read_len = read_word(buffer, WORD_MAX, stdin)) != EOF) {
        if (print_error == SHOULD_PRINT) {
            fprintf(stderr, "Word with length of %i characters has been truncated to %i characters.\n",error_len, WORD_MAX-1);
            print_error = PRINTED;
        }

        if (read_len >= WORD_MAX && print_error == NO_ERROR) {
            print_error = SHOULD_PRINT;
            error_len = read_len;
        }

        htab_pair_t *pair = htab_lookup_add(table, buffer);
        // check if alloccation has failed
        if (pair == NULL) {
            fprintf(stderr, "Allocation of memory has failed.\n");
            exit(1);
        }
        pair->value++;
    }

    htab_for_each(table, print_item);


#ifdef HTAB_TEST_MOVE
    htab_t *newTable = htab_move(5000, table);
    htab_for_each(newTable, print_item);
    htab_free(newTable);
#endif

    htab_free(table);
    free(buffer);

    return 0;
}