/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neko.h"
#include "vector.h"

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

NEKO_API void pak_create(const char *);
NEKO_API PAK_ERROR pak_check(PAK_FILE *);
NEKO_API PAK_ERROR pak_insert(PAK_FILE *, char *, char *);
NEKO_API PAK_ERROR pak_insert_data(PAK_FILE *pak, char *filename, char *nameInPak, char *data, size_t dataSize);
NEKO_API PAK_ERROR pak_extract(PAK_FILE *, char *);
NEKO_API PAK_FILE *pak_open(char *);
NEKO_API PAK_ERROR pak_close(PAK_FILE *);
PAK_SECTION *pak_getSection(PAK_FILE *, const char *);
NEKO_API void *pak_load(PAK_FILE *, const char *, size_t *);
void *pak_error(FILE *, PAK_ERROR);
void pak_getFileList(PAK_FILE *pak, VECTOR *v);