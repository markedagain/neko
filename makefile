CC=gcc
CFLAGS=-I./src -Wall
SRCS=actionlist.c

neko: src/neko.c
	$(CC) $(CFLAGS) -o bin/neko src/neko.c
