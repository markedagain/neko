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
    pak_error(NULL, PAKERROR_OPEN);
    return;
  }

  if (!fwrite(&pak.header, sizeof(pak.header), 1, pak.handle)) {
    pak_error(pak.handle, PAKERROR_WRITE);
    return;
  }

  fclose(pak.handle);
}

PAK_ERROR pak_check(PAK_FILE *pak) {
  if (pak->header.head[0] != 'P' || pak->header.head[1] != 'A' || pak->header.head[2] != 'C' || pak->header.head[3] != 'K')
    return PAKERROR_IDENT_CORRUPT;
  if (pak->header.offset < sizeof(pak->header.head) + 1 || pak->header.size < 1)
    return PAKERROR_HEADER_CORRUPT;
  return PAKERROR_NONE;
}

PAK_FILE *pak_open(char *filename) {
  PAK_FILE *pak;
  FILE *fp;

  fp = fopen(filename, "r+");
  if (!fp)
    return (PAK_FILE *)pak_error(NULL, PAKERROR_OPEN);

  pak = (PAK_FILE *)malloc(sizeof(PAK_FILE));
  if (!pak)
    return (PAK_FILE *)pak_error(fp, PAKERROR_MALLOC);
  pak->handle = fp;

  if (!fread(&pak->header, sizeof(PAK_HEADER), 1, pak->handle))
    return (PAK_FILE *)pak_error(fp, PAKERROR_READ);

  return pak;
}

PAK_ERROR pak_close(PAK_FILE *pak) {
  fclose(pak->handle);
  free(pak);
  return PAKERROR_NONE;
}

PAK_ERROR pak_insert(PAK_FILE *pak, char *filename, const char *nameInPak) {
  unsigned int count = 0;
  PAK_SECTION section;
  PAK_SECTION *files;
  int x = 0;
  char *buffer;
  FILE *fp;
  char c;
  int b;

  // Error if requested filename is too long
  if (sizeof(nameInPak) > PAK_FILENAME_MAXLENGTH)
    return PAKERROR_FILENAME_LENGTH;

  // Read the file to pack into memory
  fp = fopen(filename, "r");
  if (!fp)
    return PAKERROR_OPEN;
  while(fread(&c, sizeof(c), 1, fp) > 0)
    ++count;
  buffer = (char *)malloc(sizeof(char) * count);
  if (!buffer) {
    fclose(fp);
    return PAKERROR_MALLOC;
  }
  rewind(fp);
  count = 0;
  while ((b = fgetc(fp)) != EOF)
    buffer[count++] = b;
  fclose(fp);

  if (pak->header.size == 1) {
    if (!fseek(pak->handle, 4, SEEK_SET))
      return PAKERROR_READ;
    pak->header.offset = sizeof(pak->header) + sizeof(char) * count;
    pak->header.size = sizeof(PAK_SECTION);
    fwrite(&pak->header.offset, sizeof(pak->header.offset), 1, pak->handle);
    fwrite(&pak->header.size, sizeof(pak->header.size), 1, pak->handle);
    fwrite(buffer, sizeof(char), count, pak->handle);
    strcpy(section.name, nameInPak);
    section.offset = 12;
    section.size = sizeof(char) * count;
    fwrite(&section, sizeof(section), 1, pak->handle);
  }
  else {
    int i;
    if (pak->header.size % 64 != 0)
      return PAKERROR_HEADER_CORRUPT;
    x = pak->header.size / 64;
    files = (PAK_SECTION *)malloc((x + 1) * sizeof(PAK_SECTION));
    fseek(pak->handle, pak->header.offset, SEEK_SET);
    fread(files, sizeof(PAK_SECTION), x, pak->handle);
    for (i = 0; i < x; ++i) {
      if (strcmp(files[i].name, nameInPak) == 0)
        return PAKERROR_DUPLICATE_FILE;
    }
    fseek(pak->handle, 4, SEEK_SET);
    pak->header.offset += count;
    pak->header.size += sizeof(PAK_SECTION);
    fwrite(&pak->header.offset, sizeof(pak->header.offset), 1, pak->handle);
    fwrite(&pak->header.size, sizeof(pak->header.size), 1, pak->handle);
    fseek(pak->handle, pak->header.offset - count, SEEK_SET);
    fwrite(buffer, sizeof(char), count, pak->handle);
    strcpy(files[x].name, nameInPak);
    files[x].offset = pak->header.offset - count;
    files[x].size = sizeof(char) * count;
    fwrite(files, sizeof(PAK_SECTION), x + 1, pak->handle);
  }
  free(buffer);
  return PAKERROR_NONE;
}

PAK_ERROR pak_insertDirectory(PAK_FILE *pak, const char *directory) {
  return PAKERROR_NONE;
}

PAK_SECTION *pak_loadAllFiles(PAK_FILE *pak, int *count) {
  PAK_SECTION *files;
  *count = pak->header.size / 64;
  files = (PAK_SECTION *)malloc(sizeof(PAK_SECTION) * *count);
  fseek(pak->handle, pak->header.offset, SEEK_SET);
  fread(files, sizeof(PAK_SECTION), *count, pak->handle);
  return files;
}

PAK_SECTION *pak_getSection(PAK_FILE *pak, const char *filename) {
  PAK_SECTION *section;
  int count = 0;
  PAK_SECTION *files;
  int i;
  
  section = (PAK_SECTION *)malloc(sizeof(PAK_SECTION));
  if (!section)
    return NULL;
  files = pak_loadAllFiles(pak, &count);

  for (i = 0; i < count; ++i) {
    if (strcmp(files[i].name, filename) == 0) {
      strcpy(section->name, files[i].name);
      section->offset = files[i].offset;
      section->size = files[i].size;
      free(files);
      return section;
    }
  }
  free(files);
  return NULL;
}

PAK_ERROR pak_extract(PAK_FILE *pak, char *outputDirectory) {
  return PAKERROR_NOT_IMPLEMENTED;
}

void *pak_load(PAK_FILE *pak, const char *filename, size_t *size) {
  PAK_SECTION *section;
  void *buffer;
  if (pak == NULL)
    return NULL;
  section = pak_getSection(pak, filename);
  if (!section)
    return NULL;
  fseek(pak->handle, section->offset, SEEK_SET);
  buffer = malloc(section->size);
  *size = section->size;
  fread(buffer, sizeof(char), section->size, pak->handle);
  return buffer;
}