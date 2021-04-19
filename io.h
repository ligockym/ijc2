#ifndef IJC2_IO_H
#define IJC2_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define WORD_MAX 1000

int read_word(char *s, int max, FILE *f);
#endif //IJC2_IO_H
