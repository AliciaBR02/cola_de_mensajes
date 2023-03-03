CC = gcc
CFLAGS = -g -Wall -Wextra -Werror


all:
.PHONY: all

servidor: servidor.c
	$(CC) $(CFLAGS) $^ -o $@

cliente: cliente.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f servidor cliente servidor/data.txt
.PHONY: clean

