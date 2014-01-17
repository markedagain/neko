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

void sprite_init(SPRITE *sprite) {
  sprite->width = 32;
  sprite->height = 32;
  sprite->u = 0.5f;
  sprite->v = 0.5f;
  sprite->texture = NULL;
}



void data_loadTextfileFromDisk(DATACONTAINER *dataContainer, const char *filename) {
  TEXTFILE *textfile;
  char storeKey[80];

  textfile = (TEXTFILE *)malloc(sizeof(TEXTFILE));
  textfile_init(textfile);

  file_readText(&textfile->lines, filename);

  data_makeKey(dataContainer, storeKey, filename, "txt/", ".txt");
  dict_set(&dataContainer->textfiles, storeKey, textfile);
  printf("Loaded TXT %s from disk\n", storeKey);
}

void data_loadTextureFromDisk(DATACONTAINER *dataContainer, const char *filename) {
  TEXTURE *texture;
  char storeKey[80];
  //char *bytes;
  //bytes = file_readBinary(filename);
  //AEGfxTextureLoadFromMemory(
  texture = AEGfxTextureLoad(filename);
  AE_ASSERT_MESG(texture, "Failed to load texture!")

  data_makeKey(dataContainer, storeKey, filename, "tex/", ".png");
  dict_set(&dataContainer->textures, storeKey, texture);
  printf("Loaded TEX %s from disk\n", storeKey);
}

void data_loadQuickSpriteFromDisk(DATACONTAINER *dataContainer, const char *filename) {
  TEXTURE *texture;
  SPRITE *sprite;
  char storeKey[80];
  char storeKey2[80];
  //char *bytes;
  //bytes = file_readBinary(filename);
  //AEGfxTextureLoadFromMemory(
  texture = AEGfxTextureLoad(filename);
  AE_ASSERT_MESG(texture, "Failed to load texture!")
  sprite = (SPRITE *)malloc(sizeof(SPRITE));
  sprite_init(sprite);
  sprite->texture = texture;

  data_makeKey(dataContainer, storeKey, filename, "tex/", ".png");
  dict_set(&dataContainer->textures, storeKey, texture);
  printf("Loaded TEX %s from disk (QUICK)\n", storeKey);

  data_makeKey(dataContainer, storeKey2, filename, "spr/", ".png");
  dict_set(&dataContainer->sprites, storeKey2, sprite);
  printf("Loaded SPR %s from disk (QUICK)\n", storeKey2);
}

void data_makeKey(DATACONTAINER *dataContainer, char *storeKey, const char *filename, const char *directory, const char *extension) {
  // given the file /data/txt/subdir1/subdir2/file.txt,
  // reduce it to just subdir1/subdir2/file for key storage
  char currentDirectory[MAX_PATH];
  file_getCurrentDirectory(currentDirectory);
  strcpy(storeKey, filename + (strlen(currentDirectory) + 1 + strlen(dataContainer->root) + sizeof(directory)) * sizeof(char));
  storeKey[strlen(storeKey) - sizeof(extension)] = 0;
  file_windowsToUnix(storeKey);
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
  if (found)
    FindClose(handle);
  return found;
}

void file_getCurrentDirectory(char *directory) {
  TCHAR buffer[MAX_PATH];
  char *lastSlash;
  GetModuleFileName(NULL, buffer, MAX_PATH);
  wcstombs(directory, buffer, MAX_PATH);
  lastSlash = strrchr((char *)directory, '\\');
  if (lastSlash != NULL)
    *lastSlash = 0;
}

void file_unixToWindows(char *string) {
  char *slash = strrchr(string, '/');
  while (slash != NULL) {
    *slash = '\\';
    slash = strrchr(string, '/');
  }
}
void file_windowsToUnix(char *string) {
  char *slash = strrchr(string, '\\');
  while (slash != NULL) {
    *slash = '/';
    slash = strrchr(string, '\\');
  }
}

bool file_getAllByExtension(VECTOR *fileList, const char *directory, const char *extension) {
  WIN32_FIND_DATA findFile;
  HANDLE find = NULL;
  TCHAR widePath[MAX_PATH];
  char path[MAX_PATH];
  char file[MAX_PATH];
  sprintf(path, "%s\\*", directory);
  mbstowcs(widePath, path, MAX_PATH);
  if ((find = FindFirstFile(widePath, &findFile)) == INVALID_HANDLE_VALUE)
    return false;
  do {
    if (wcscmp(findFile.cFileName, __TEXT(".")) && wcscmp(findFile.cFileName, __TEXT(".."))) {
      wcstombs(file, findFile.cFileName, MAX_PATH);
      sprintf(path, "%s\\%s", directory, file);
      if (findFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        file_getAllByExtension(fileList, path, extension);
      }
      else {
        char *filename;
        if (strcmp(path + (strlen(path) - sizeof(extension)) * sizeof(char), extension))
          continue;
        filename = (char *)malloc(sizeof(char) * MAX_FILENAME);
        strcpy(filename, path);
        vector_append(fileList, filename);
      }
    }
  }
  while (FindNextFile(find, &findFile));
  if (find)
    FindClose(find);
  return true;
}

void data_loadAll(DATACONTAINER *dataContainer) {
  VECTOR files;
  size_t i;
  char subdir[MAX_PATH];
  char currentDirectory[MAX_PATH];
  vector_init(&files);
  file_getCurrentDirectory(currentDirectory);

  // LOAD TEXTURES
  sprintf(subdir, "%s/%s%s", currentDirectory, dataContainer->root, "tex");
  file_unixToWindows(subdir);
  file_getAllByExtension(&files, subdir, ".png");
  for (i = 0; i < vector_size(&files); ++i)
    data_loadTextureFromDisk(dataContainer, (char *)vector_get(&files, i));
  vector_clear(&files);

  // LOAD QUICK SPRITES/TEXTURES
  sprintf(subdir, "%s/%s%s", currentDirectory, dataContainer->root, "spr");
  file_unixToWindows(subdir);
  file_getAllByExtension(&files, subdir, ".png");
  for (i = 0; i < vector_size(&files); ++i)
    data_loadQuickSpriteFromDisk(dataContainer, (char *)vector_get(&files, i));
  vector_clear(&files);

  // LOAD TEXTFILES
  sprintf(subdir, "%s/%s%s", currentDirectory, dataContainer->root, "txt");
  file_unixToWindows(subdir);
  file_getAllByExtension(&files, subdir, ".txt");
  for (i = 0; i < vector_size(&files); ++i)
    data_loadTextfileFromDisk(dataContainer, (char *)vector_get(&files, i));
  vector_clear(&files);

  vector_free(&files);
}