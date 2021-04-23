/**
 * io.c
 * Autor: Marián Ligocký xligoc04
 * Datum: 23.4.2020
 */

#include "io.h"

int read_word(char *s, int max, FILE *f) {
    int i = 0;
    int chr; // has to be int, not char
    bool word_detected = false;

    while ((chr = fgetc(f)) != EOF) {
        if (i >= (max - 1)) {
            // limit exceeded -> last character is null
            s[max-1] = '\0';

            if (isspace(chr) || chr == EOF) {
                return i;
            }
            // keep reading but not saving.

        } else {
            if (isspace(chr) || chr == EOF) {
                if (word_detected) {
                    s[i] = '\0';
                    return i;
                }
                // just a regular white space
                continue;
            } else {
                // is a letter -> save letter
                word_detected = true;
                s[i] = (char)chr;
            }
        }
        i++;
    }

    return EOF;
}