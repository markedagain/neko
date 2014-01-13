/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pakHeader_t {
  char head[4];
  unsigned int offset;
  unsigned int size;
} PAK_HEADER;

typedef struct pakContent_t {
  char name[56];
  unsigned int offset;
  unsigned int size;
} PAK_SECTION;

typedef struct pakFile_t {
  FILE *handle;
  PAK_HEADER header;
} PAK_FILE;

typedef enum {
  PAKERROR_NONE = 0,
  PAKERROR_IDENT_CORRUPT,
  PAKERROR_HEADER_CORRUPT,
  PAKERROR_OPEN_FAIL,
  PAKERROR_WRITE_FAIL
} PAK_ERROR;

void pak_create(const char *);
PAK_ERROR pak_check(const PAK_FILE *);
int pak_extract(const PAK_FILE *, char *, char *);
int pak_insert(PAK_FILE *, char *, char *);
PAK_FILE *pak_open(char *);
int pak_close(PAK_FILE *);
char *file_read(char *, unsigned int *size);
PAK_SECTION *pak_contains(const PAK_FILE *, char *);
void *pak_load(const PAK_FILE *, const char *, int *);
void *pak_error(FILE *, PAK_ERROR);