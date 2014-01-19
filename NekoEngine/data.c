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

void data_loadTextfileFromPak(DATACONTAINER *dataContainer, PAK_FILE *pak, const char *filename) {
  TEXTFILE *textfile;
  char storeKey[80];
  char *data = NULL;
  char *dataStart;
  size_t count, i, bufferPos = 0;
  char buffer[TEXTFILE_LINELENGTH] = { 0 };

  data_makeKey(dataContainer, storeKey, filename, "txt/", ".txt");
  if (dict_get(&dataContainer->textfiles, storeKey) != NULL) {
    printf("Loaded TXT %s from pak (HIDDEN)\n", storeKey);
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
      char *newLine = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
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
  if (bufferPos != 0)
    vector_append(&textfile->lines, (char *)malloc((strlen(buffer) + 1) * sizeof(char)));

  
  dict_set(&dataContainer->textfiles, storeKey, textfile);
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
  printf("%s\n", filename);
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

void data_test(DATACONTAINER *dataContainer) {
  PAK_FILE* pakFile;
  size_t sprSize;
  void *sprData;
  char pakDir[MAX_PATH];
  unsigned char *texData = NULL;
  POINT texDimensions;
  AEGfxTexture *texture;
  SPRITE *sprite;

  sprite = (SPRITE *)malloc(sizeof(SPRITE));
  sprite_init(sprite);

  file_getCurrentDirectory(pakDir);
  sprintf(pakDir, "%s\\data.pak", pakDir);
  pakFile = pak_open(pakDir);
  sprData = pak_load(pakFile, "spr/colortest.png", &sprSize);
  data_convertPNGToTexture(sprData, sprSize, texData, &texDimensions);
  texture = AEGfxTextureLoadFromMemory(texData, texDimensions.x, texDimensions.y);
  AE_ASSERT_MESG(texture, "Failed to load texture!")
  dict_set(&dataContainer->textures, "TEST", texture);
  sprite->texture = texture;
  dict_set(&dataContainer->sprites, "TEST", sprite);
  //free(sprData);
}

void data_loadAll(DATACONTAINER *dataContainer) {
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
        //printf(">> %s is a QUICK SPRITE (?)\n", filename);
      }
      else if (strcmp(extension, ".spr") == 0) {
        //printf(">> %s is a SPRITE\n", filename);
      }
      else {
        //printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
    else if (strstr(filename, "txt/") == filename) {
      if (strcmp(extension, ".txt") == 0) {
        //printf(">> %s is a TEXTFILE (?)\n", filename);
        data_loadTextfileFromPak(dataContainer, pak, filename);
      }
      else {
        //printf(">> %s is an UNKNOWN FILE\n", filename);
      }
    }
    //free(filename);
  }
  vector_clear(&files);
  pak_close(pak);

  printf("REZICH: %s\n", (char *)vector_get(&((TEXTFILE *)dict_get(&dataContainer->textfiles, "names/last"))->lines, 0));

  vector_free(&files);
}

typedef struct {
  png_bytep p;
  png_uint_32 len;
} PNGDATA, *PNGDATAPTR;

void data_loadPNGFromMemory(png_structp png_ptr, png_bytep data, png_size_t length) {
  PNGDATAPTR dataPtr = (PNGDATAPTR)png_get_io_ptr(png_ptr);
  png_uint_32 i;

  if (length > dataPtr->len) {
    png_error(png_ptr, "EOF");
    return;
  }
  for (i = 0; i < length; ++i)
    data[i] = dataPtr->p[i];
  dataPtr->p += length;
  dataPtr->len -= length;
}

void data_convertPNGToTexture(void *data, size_t length, unsigned char *outData, POINT *outDimensions) {
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  png_uint_32 width, height;
  int colorType, interlaceType, bitDepth;
  unsigned int sig_read = 0;
  PNGDATA pngData;
  png_bytepp rowPointers;
  unsigned int rowBytes;
  int i;

  pngData.p = (png_bytep)data;
  pngData.len = length;

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return;
  }
  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return;
  }
  png_set_read_fn(png_ptr, (void *)&pngData, data_loadPNGFromMemory);
  png_init_io(png_ptr, (FILE *)&pngData);
  png_set_sig_bytes(png_ptr, sig_read);
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_SWAP_ALPHA, NULL);
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType, &interlaceType, NULL, NULL);
  outDimensions->x = width;
  outDimensions->y = height;

  rowPointers = png_get_rows(png_ptr, info_ptr);
  rowBytes = png_get_rowbytes(png_ptr, info_ptr);
  outData = (unsigned char*)malloc(rowBytes * height);
  for (i = 0; i < height; ++i) {
    memcpy(outData + (rowBytes * (height - 1 - i)), rowPointers[i], rowBytes);
  }

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
}