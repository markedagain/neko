/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAK_FILENAME_MAXLENGTH 56

typedef struct pakHeader_t {
  char head[4];
  unsigned int offset;
  unsigned int size;
} PAK_HEADER;

typedef struct pakContent_t {
  char name[PAK_FILENAME_MAXLENGTH];
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
  PAKERROR_OPEN,
  PAKERROR_WRITE,
  PAKERROR_READ,
  PAKERROR_MALLOC,
  PAKERROR_FILENAME_LENGTH,
  PAKERROR_DUPLICATE_FILE,
  PAKERROR_NOT_IMPLEMENTED
} PAK_ERROR;

void pak_create(const char *);
PAK_ERROR pak_check(PAK_FILE *);
PAK_ERROR pak_insert(PAK_FILE *, char *, const char *);
PAK_ERROR pak_insertDirectory(PAK_FILE *, const char *);
PAK_ERROR pak_extract(PAK_FILE *, char *, char *);
PAK_FILE *pak_open(char *);
PAK_ERROR pak_close(PAK_FILE *);
PAK_SECTION *pak_getSection(PAK_FILE *, const char *);
char *pak_load(PAK_FILE *, const char *, size_t *);
void *pak_error(FILE *, PAK_ERROR);