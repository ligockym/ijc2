#include "htab.h"
#include "htab_internal.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>

/*
int main() {
    using namespace std;
    unordered_map<string,int> m;  // asociativní pole
    // mapuje klíč/string na hodnotu/int
    string word;
    while (cin >> word) // čtení slova (jako scanf "%s", ale bezpečné)
        m[word]++;      // počítání výskytů slova (zvýší hodnotu pro
    // zadaný klíč/slovo pokud záznam existuje,
    // jinak vytvoří nový záznam s hodnotou 0 a
    // tu operace ++ zvýší na 1)

    for (auto &mi: m)   // pro všechny prvky kontejneru m
    cout << mi.first << "\t" << mi.second << "\n";
    //      klíč/slovo          hodnota/počet
    // prvky kontejneru typu "map" jsou dvojice (klíč,hodnota)
}*/

void print_item(htab_pair_t *data) {
    printf("%s\t%i\n", data->key, data->value);
}

int main() {
    /* Vybral som si ukazkovy priklad naplnenia hash tabulky textami anglickych noviel.
    https://writing.stackexchange.com/questions/6988/how-many-different-words-are-in-the-average-novel
    Priemerny pocet unikátnych slov je okolo 5101, takze vyberam prvocislo okolo 5000 (lepsia funkcnost
     hashovacej funkcie)
     */
    htab_t *table = htab_init(2); // TODO: Change back to 5101
    // check if allocation has failed
    if (table == NULL) {
        fprintf(stderr, "Allocation of memory has failed.\n");
        exit(1);
    }

    char *buffer = malloc(WORD_MAX * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Allocation of memory has failed.\n");
        exit(1);
    }

    int read_len;

    // read words
    while ((read_len = read_word(buffer, WORD_MAX, stdin)) != EOF) {
        if (read_len > WORD_MAX) {
            fprintf(stderr, "Word with length of %i characters has been truncated to %i characters.\n",read_len, WORD_MAX-1);
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

    htab_free(table);
    free(buffer);

    return 0;
}