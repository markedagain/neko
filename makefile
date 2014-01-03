CC=gcc
CFLAGS=-I./src -Wall -ansi

NEKO_SOURCEDIR = src/neko
NEKO_SRCS = $(shell find $(NEKO_SOURCEDIR) -name '*.c')

SAMPLE_SOURCEDIR = src/sample
SAMPLE_SRCS = $(shell find $(SAMPLE_SOURCEDIR) -name '*.c')

neko: src/neko.c
	$(CC) $(CFLAGS) -o bin/neko src/neko/neko.c $(NEKO_SRCS)

sample: src/sample/main.c
	$(CC) $(CFLAGS) -o bin/sample $(NEKO_SRCS) $(SAMPLE_SRCS)
