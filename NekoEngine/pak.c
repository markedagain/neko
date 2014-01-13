/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "pak.h"

void *pak_error(FILE *fp, PAK_ERROR error) {
  if (fp != NULL)
    fclose(fp);
  printf("*** PAK ERROR: %i ***\n", error);
  return NULL;
}

void pak_create(const char *filename) {
  PAK_FILE pak;
  pak.header.head[0] = 'P';
  pak.header.head[1] = 'A';
  pak.header.head[2] = 'C';
  pak.header.head[3] = 'K';
  pak.header.offset = sizeof(pak.header.head) + 1;
  pak.header.size = 1;
  pak.handle = fopen(filename, "wb");
  if (!pak.handle) {
    pak_error(NULL, PAKERROR_OPEN_FAIL);
    return;
  }

  if (!fwrite(&pak.header, sizeof(pak.header), 1, pak.handle)) {
    pak_error(pak.handle, PAKERROR_WRITE_FAIL);
    return;
  }

  fclose(pak.handle);
}

PAK_ERROR pak_check(const PAK_FILE *pak) {
  if (pak->header.head[0] != 'P' || pak->header.head[1] != 'A' || pak->header.head[2] != 'C' || pak->header.head[3] != 'K')
    return PAKERROR_IDENT_CORRUPT;
  if (pak->header.offset < sizeof(pak->header.head) + 1 || pak->header.size < 1)
    return PAKERROR_HEADER_CORRUPT;
  return PAKERROR_NONE;
}

