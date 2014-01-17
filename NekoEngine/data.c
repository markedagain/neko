/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "data.h"
#include "pak.h"

/*
      (P)reload
data/    root data folder/.pak file
  cfg/   config files
  mus/   music
  sav/   save files (only in data/, not in .pak)
  sfx/ X sound effects
  spr/ X .spr sprite definitions in .pak, quick-load .png sprite textures in data/
  tex/ X textures (atlases)
  txt/ X text files

*/

void dataContainer_init(DATACONTAINER *data) {
  dict_init(&data->sprites);
  dict_init(&data->textures);
  dict_init(&data->sounds);
  dict_init(&data->textfiles);
  data->root = NEKO_DEFAULT_ROOT;
}

void textfile_init(TEXTFILE *textfile) {
  vector_init(&textfile->lines);
}


void data_loadTextfileFromDisk(DATACONTAINER *dataContainer, const char *filename) {
  TEXTFILE *textfile;
  char storeKey[80];

  textfile = (TEXTFILE *)malloc(sizeof(TEXTFILE));
  textfile_init(textfile);

  file_readText(&textfile->lines, filename);

  data_makeKey(dataContainer, storeKey, filename, "txt/", ".txt");
  dict_set(&dataContainer->textfiles, storeKey, textfile);
}

void data_loadTextureFromDisk(DATACONTAINER *dataContainer, const char *filename) {
  TEXTURE *texture;
  char storeKey[80];
  //char *bytes;
  //bytes = file_readBinary(filename);
  //AEGfxTextureLoadFromMemory(
  texture = AEGfxTextureLoad(filename);

  data_makeKey(dataContainer, storeKey, filename, "tex/", ".png");
  dict_set(&dataContainer->textures, storeKey, texture);
}

void data_makeKey(DATACONTAINER *dataContainer, char *storeKey, const char *filename, const char *directory, const char *extension) {
  // given the file /data/txt/subdir1/subdir2/file.txt,
  // reduce it to just subdir1/subdir2/file for key storage
  strcpy(storeKey, filename + (strlen(dataContainer->root) + sizeof(directory)) * sizeof(char));
  storeKey[strlen(storeKey) - sizeof(extension)] = 0;
}

unsigned int file_readText(VECTOR *lines, const char *filename) {
  int c;
  unsigned int lineCount = 0;
  unsigned int size = TEXTFILE_LINELENGTH;
  char *buffer = (char *)malloc(sizeof(char) * size);
  FILE *f = fopen(filename, "rt");
  if (!f) {
    free(buffer);
    return 0;
  }
  do {
    char *line;
    unsigned int pos = 0;
    do {
      c = fgetc(f);
      if (c != EOF)
        buffer[pos++] = (char)c;
      if (pos >= size - 1) {
        size *= 2;
        buffer = (char *)realloc(buffer, size);
      }
    }
    while (c != EOF && c != '\n');
    buffer[pos - 1] = 0;
    line = (char *)malloc(sizeof(char) * pos);
    strcpy(line, buffer);
    vector_append(lines, line);
    ++lineCount;
  }
  while (c != EOF);
  fclose(f);
  free(buffer);
  return lineCount;
}

char *file_readBinary(const char *filename) {
  unsigned long length;
  char *bytes;
  FILE *f;
  f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  length = ftell(f);
  bytes = (char *)malloc(length * sizeof(char));
  fseek(f, 0, SEEK_SET);
  fread(bytes, 1, length, f);
  fclose(f);
  return bytes;
}

bool file_exists(char *filename) {
  TCHAR *file = (TCHAR *)filename;
  WIN32_FIND_DATA FindFileData;
  HANDLE handle = FindFirstFile(file, &FindFileData);
  int found = handle != INVALID_HANDLE_VALUE;
  if (found) {
    //FindClose(&handle); this will crash
    FindClose(handle);
  }
  return found;
}

void *file_load(char *filename) {
  return NULL;
}