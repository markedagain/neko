CC=gcc
CFLAGS=-I./src -Wall -ansi
SRCS=src/actionlist.c src/component.c src/linkedlist.c src/vector.c src/vectormath.c

neko: src/neko.c
	$(CC) $(CFLAGS) -o bin/neko src/neko.c $(SRCS)
