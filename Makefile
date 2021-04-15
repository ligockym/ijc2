CFLAGS = -g -std=c99 -pedantic -Wall -Wextra
LDFLAGS = -lm
CC = gcc

tail: tail.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f tail