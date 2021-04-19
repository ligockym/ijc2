CFLAGS = -g -std=c99 -pedantic -Wall -Wextra
LDFLAGS = -lm
CC = gcc
HTAB_LIBRARY = htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_hash_function.o htab_init_item.o htab_erase.o htab_clean_item.o htab_free.o htab_clear.o htab_for_each.o

all: tail wordcount wordcount-dynamic

tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


wordcount: wordcount.c io.c libhtab.a
	$(CC) $(CFLAGS) $^ -o $@

wordcount-dynamic: wordcount.c io.c libhtab.so
	$(CC) $(CFLAGS) $^ -o $@

libhtab.a: $(HTAB_LIBRARY)
	ar crs $@ $^

libhtab.so: $(HTAB_LIBRARY)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $^


.PHONY: clean
clean:
	rm -f *.o tail wordcount wordcount-dynamic libhtab.a libhtab.so