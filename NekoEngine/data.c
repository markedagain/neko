/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "data.h"

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
  dict_init(&data->sounds);
  data->root = NEKO_DEFAULT_ROOT;
}

void textfile_init(TEXTFILE *textfile) {
  vector_init(&textfile->lines);
}

void sprite_init(SPRITE *sprite) {
  int i;
  sprite->width = 32;
  sprite->height = 32;
  sprite->u = 0.5f;
  sprite->v = 0.5f;
  sprite->texture = NULL;
  for (i = 0; i < PAK_FILENAME_MAXLENGTH; ++i)
    sprite->textureName[i] = 0;
}

void texture_init(TEXTURE *texture) {
  texture->data = NULL;
  texture->width = 32;
  texture->height = 32;
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
  
  texture = (TEXTURE *)malloc(sizeof(TEXTURE));
  texture_init(texture);
  texture->data = AEGfxTextureLoad(filename);
  AE_ASSERT_MESG(texture, "Failed to load texture!")

  data_makeKey(dataContainer, storeKey, filename, "tex/", ".png");
  dict_set(&dataContainer->textures, storeKey, texture);
  printf("Loaded TEX %s from disk\n", storeKey);
}

void data_loadQuickSpriteFromDisk(DATACONTAINER *dataContainer, const char *filename) {
  TEXTURE *texture;
  char storeKey[80];

  texture = (TEXTURE *)malloc(sizeof(TEXTURE));
  texture_init(texture);
  texture->data = AEGfxTextureLoad(filename);
  AE_ASSERT_MESG(texture, "Failed to load texture!")

  data_makeKey(dataContainer, storeKey, filename, "tex/", ".png");
  dict_set(&dataContainer->textures, storeKey, texture);
  printf("Loaded TEX %s from disk (QUICK)\n", storeKey);
}

void data_loadTextfileFromPak(DATACONTAINER *dataContainer, PAK_FILE *pak, const char *filename) {
  TEXTFILE *textfile;
  char storeKey[80];
  char *data = NULL;
  char *dataStart;
  size_t count, i, bufferPos = 0;
  char buffer[TEXTFILE_LINELENGTH] = { 0 };

  data_makeKey(dataContainer, storeKey, filename, "txt/", ".txt");
  if (dict_get(&dataContainer->textfiles, storeKey) != NULL) {
    printf("Found TXT %s in pak (HIDDEN)\n", storeKey);
    return;
  }

  textfile = (TEXTFILE *)malloc(sizeof(TEXTFILE));
  textfile_init(textfile);
  
  data = (char *)pak_load(pak, filename, &count);
  dataStart = data;
  while (data < dataStart + count) {
    if (*data == '\r')
      ++data;
    if (*data == '\n') {
      char *newLine;
      buffer[bufferPos++] = 0;
      newLine = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(newLine, buffer);
      vector_append(&textfile->lines, newLine);
      for (i = 0; i < TEXTFILE_LINELENGTH; ++i)
        buffer[i] = 0;
      bufferPos = 0;
      ++data;
    }
    else {
      buffer[bufferPos++] = *data++;
    }
  }
  if (bufferPos != 0) {
    char *newLine;
    buffer[bufferPos++] = 0;
    newLine = (char *)malloc((bufferPos) * sizeof(char));
    strcpy(newLine, buffer);
    vector_append(&textfile->lines, newLine);
  }

  printf("Loaded TXT %s from pak\n", storeKey);
  dict_set(&dataContainer->textfiles, storeKey, textfile);
}

void data_loadTextureFromPak(DATACONTAINER *dataContainer, PAK_FILE *pak, const char *filename) {
  TEXTURE *texture;
  char storeKey[80];
  char *pakData = NULL;
  size_t pakSize;
  unsigned char *texData = NULL;
  bool existing = false;

  data_makeKey(dataContainer, storeKey, filename, "tex/", ".tex");

  if (dict_get(&dataContainer->textures, storeKey) != NULL) {
    printf("Found TEX %s in pak (PROPERTIES ONLY)\n", storeKey);
    existing = true;
    texture = (TEXTURE *)dict_get(&dataContainer->textures, storeKey);
  }
  else {
    texture = (TEXTURE *)malloc(sizeof(TEXTURE));
    texture_init(texture);
  }

  pakData = (char *)pak_load(pak, filename, &pakSize);

  texture->width = *(uint32_t *)pakData;
  texture->height = *(uint32_t *)(pakData + 4);

  if (!existing) {
    texData = (unsigned char *)pakData + 8;
    texture->data = AEGfxTextureLoadFromMemory(texData, texture->width, texture->height);
  }

  free(pakData);

  if (!existing)
    dict_set(&dataContainer->textures, storeKey, texture);
  printf("Loaded TEX %s from pak\n", storeKey);
}

void data_loadSpriteFromPak(DATACONTAINER *dataContainer, PAK_FILE *pak, const char *filename) {
  SPRITE *sprite;
  char storeKey[80];
  char *data = NULL;
  char *dataStart;
  size_t count, i, bufferPos = 0;
  char buffer[TEXTFILE_LINELENGTH] = { 0 };
  VECTOR lines;
  bool existing = false;

  data_makeKey(dataContainer, storeKey, filename, "spr/", ".spr");

  if (dict_get(&dataContainer->sprites, storeKey) != NULL) {
    printf("Found SPR %s in pak (PROPERTIES ONLY)\n", storeKey);
    existing = true;
    sprite = (SPRITE *)dict_get(&dataContainer->sprites, storeKey);
  }
  else {
    sprite = (SPRITE *)malloc(sizeof(SPRITE));
    sprite_init(sprite);
  }

  vector_init(&lines);

  data = (char *)pak_load(pak, filename, &count);
  dataStart = data;
  while (data < dataStart + count) {
    if (*data == '\r')
      ++data;
    if (*data == '\n') {
      char *newLine;
      buffer[bufferPos++] = 0;
      newLine = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(newLine, buffer);
      vector_append(&lines, newLine);
      for (i = 0; i < TEXTFILE_LINELENGTH; ++i)
        buffer[i] = 0;
      bufferPos = 0;
      ++data;
    }
    else {
      buffer[bufferPos++] = *data++;
    }
  }
  if (bufferPos != 0)
    vector_append(&lines, (char *)malloc((strlen(buffer) + 1) * sizeof(char)));

  strcpy(sprite->textureName, (char *)vector_get(&lines, 0));
  sprite->u = (float)atof((char *)vector_get(&lines, 1));
  sprite->v = (float)atof((char *)vector_get(&lines, 2));
  sprite->width = (unsigned int)atoi((char *)vector_get(&lines, 3));
  sprite->height = (unsigned int)atoi((char *)vector_get(&lines, 4));

  vector_free(&lines);
  printf("Loaded SPR %s from pak\n", storeKey);
  if (!existing)
    dict_set(&dataContainer->sprites, storeKey, sprite);

}

void data_loadSoundFromPak(DATACONTAINER *dataContainer, PAK_FILE *pak, const char *filename, SOUNDSYSTEM *system) {
  char storeKey[80];
  char *pakData = NULL;
  size_t pakSize;
  unsigned char *soundData = NULL;

  data_makeKey(dataContainer, storeKey, filename, "sfx/", ".mp3");

  if (dict_get(&dataContainer->sounds, storeKey) != NULL) {
    printf("Found SFX %s in pak, SKIPPING\n", storeKey);
    return;
  }
  pakData = (char *)pak_load(pak, filename, &pakSize);

  sound_loadSoundFromMemory(system, storeKey, pakData, pakSize);

  free(pakData);

  printf("Loaded SFX %s from pak\n", storeKey);
}

void data_loadMusicFromPak(DATACONTAINER *dataContainer, PAK_FILE *pak, const char *filename, SOUNDSYSTEM *system) {
  char storeKey[80];
  char *pakData = NULL;
  size_t pakSize;
  unsigned char *soundData = NULL;

  data_makeKey(dataContainer, storeKey, filename, "bgm/", ".mp3");

  if (dict_get(&dataContainer->sounds, storeKey) != NULL) {
    printf("Found BGM %s in pak, SKIPPING\n", storeKey);
    return;
  }
  pakData = (char *)pak_load(pak, filename, &pakSize);

  sound_loadSoundFromMemory(system, storeKey, pakData, pakSize);

  free(pakData);

  printf("Loaded BGM %s from pak\n", storeKey);
}

void data_makeKey(DATACONTAINER *dataContainer, char *storeKey, const char *filename, const char *directory, const char *extension) {
  // given the file /data/txt/subdir1/subdir2/file.txt,
  // reduce it to just subdir1/subdir2/file for key storage
  char currentDirectory[MAX_PATH];
  file_getCurrentDirectory(currentDirectory);
  if (strstr(filename, currentDirectory) != NULL)
    strcpy(storeKey, filename + (strlen(currentDirectory) + 1 + strlen(dataContainer->root) + sizeof(directory)) * sizeof(char));
  else
    strcpy(storeKey, filename + sizeof(directory) * sizeof(char));
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
    if (c != EOF)
      buffer[pos - 1] = 0;
    else
      buffer[pos] = 0;
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
  printf("%s\n", filename);
  if (found)
    FindClose(handle);
  return found;
}

void file_getCurrentDirectory(char *directory) {
  TCHAR buffer[MAX_PATH];
  char *lastSlash;
  GetModuleFileName(NULL, buffer, MAX_PATH);
  //wcstombs(directory, buffer, MAX_PATH);
  strcpy(directory, buffer); 
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
  //mbstowcs(widePath, path, MAX_PATH);
  strcpy(widePath, path);
  if ((find = FindFirstFile(widePath, &findFile)) == INVALID_HANDLE_VALUE)
    return false;
  do {
    //if (wcscmp(findFile.cFileName, __TEXT(".")) && wcscmp(findFile.cFileName, __TEXT(".."))) {
    if (strcmp(findFile.cFileName, ".") && strcmp(findFile.cFileName, "..")) {
      //wcstombs(file, findFile.cFileName, MAX_PATH);
      strcpy(file, findFile.cFileName);
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

void data_loadAll(DATACONTAINER *dataContainer, SOUNDSYSTEM *soundSystem) {
  VECTOR files;
  PAK_FILE* pak;
  char pakDir[MAX_PATH];
  size_t i;
  char subdir[MAX_PATH];
  char currentDirectory[MAX_PATH];

  vector_init(&files);
  file_getCurrentDirectory(currentDirectory);


  // (DISK) LOAD TEXTURES
  sprintf(subdir, "%s/%s%s", currentDirectory, dataContainer->root, "tex");
  file_unixToWindows(subdir);
  file_getAllByExtension(&files, subdir, ".png");
  for (i = 0; i < vector_size(&files); ++i)
    data_loadTextureFromDisk(dataContainer, (char *)vector_get(&files, i));
  vector_clear(&files);

  // (DISK) LOAD QUICK SPRITES/TEXTURES
  sprintf(subdir, "%s/%s%s", currentDirectory, dataContainer->root, "spr");
  file_unixToWindows(subdir);
  file_getAllByExtension(&files, subdir, ".png");
  for (i = 0; i < vector_size(&files); ++i)
    data_loadQuickSpriteFromDisk(dataContainer, (char *)vector_get(&files, i));
  vector_clear(&files);

  // (DISK) LOAD TEXTFILES
  sprintf(subdir, "%s/%s%s", currentDirectory, dataContainer->root, "txt");
  file_unixToWindows(subdir);
  file_getAllByExtension(&files, subdir, ".txt");
  for (i = 0; i < vector_size(&files); ++i)
    data_loadTextfileFromDisk(dataContainer, (char *)vector_get(&files, i));
  vector_clear(&files);

  // (PAK) LOAD ALL
  file_getCurrentDirectory(pakDir);
  sprintf(pakDir, "%s\\data.pak", pakDir);
  pak = pak_open(pakDir);
  pak_getFileList(pak, &files);
  for (i = 0; i < vector_size(&files); ++i) {
    char *filename;
    char *extension;
    filename = (char *)vector_get(&files, i);
    extension = strrchr(filename, '.');
    if (strstr(filename, "spr/") == filename) {
      if (strcmp(extension, ".png") == 0) {
        printf(">> %s is a QUICK SPRITE (?)\n", filename);
        //data_loadQuickSpriteFromPak(dataContainer, pak, filename);
      }
      else if (strcmp(extension, ".spr") == 0) {
        //printf(">> %s is a SPRITE\n", filename);
        data_loadSpriteFromPak(dataContainer, pak, filename);
      }
      else {
        printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
    else if (strstr(filename, "tex/") == filename) {
      if (strcmp(extension, ".tex") == 0) {
        data_loadTextureFromPak(dataContainer, pak, filename);
      }
      else {
        printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
    else if (strstr(filename, "txt/") == filename) {
      if (strcmp(extension, ".txt") == 0) {
        //printf(">> %s is a TEXTFILE (?)\n", filename);
        data_loadTextfileFromPak(dataContainer, pak, filename);
      }
      else {
        printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
    else if (strstr(filename, "sfx/") == filename) {
      if (strcmp(extension, ".mp3") == 0) {
        data_loadSoundFromPak(dataContainer, pak, filename, soundSystem);
      }
      else {
        printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
    else if (strstr(filename, "bgm/") == filename) {
      if (strcmp(extension, ".mp3") == 0) {
        data_loadMusicFromPak(dataContainer, pak, filename, soundSystem);
      }
      else {
        printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
  }
  vector_clear(&files);
  pak_close(pak);

  vector_free(&files);
}