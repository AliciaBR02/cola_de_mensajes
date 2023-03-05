CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
BIN_FILES = servidor cliente

all:
.PHONY: all

servidor: servidor.c
	$(CC) $(CFLAGS) $^ -o $@

cliente: cliente.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(BIN_FILES) *.o

.SUFFIXES:
.PHONY: clean

