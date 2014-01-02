CC=gcc
CFLAGS=-I./src -Wall -ansi

NEKO_SOURCEDIR = src/neko
NEKO_SRCS = $(shell find $(NEKO_SOURCEDIR) -name '*.c')

neko: src/neko.c
	$(CC) $(CFLAGS) -o bin/neko src/neko/neko.c $(NEKO_SRCS)

sample: src/sample/main.c
	$(CC) $(CFLAGS) -o bin/sample src/sample/main.c $(NEKO_SRCS)
