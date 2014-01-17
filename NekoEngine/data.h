/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "neko.h"
#include "util.h"
#include "dictionary.h"
#include "vector.h"
#include "../AlphaEngine/AEEngine.h"

#define TEXTFILE_LINELENGTH 80

typedef struct {
  DICT sprites;
  DICT sounds;
  DICT textures;
  DICT textfiles;
  char *root;
} DATACONTAINER;

/*typedef struct {
  char *data;
  size_t size;
} TEXTURE;*/

typedef struct AEGfxTexture TEXTURE;

typedef struct {
  VECTOR lines;
} TEXTFILE;

typedef struct {
  TEXTURE *texture;
  float u;
  float v;
  unsigned int width;
  unsigned int height;
} SPRITE;

void dataContainer_init(DATACONTAINER *dataContainer);
NEKO_API void data_loadTextfileFromDisk(DATACONTAINER *dataContainer, const char *filename);
NEKO_API void data_loadTextureFromDisk(DATACONTAINER *dataContainer, const char *filename);

void data_makeKey(DATACONTAINER *dataContainer, char *storeKey, const char *filename, const char *directory, const char *extension);

unsigned int file_readText(VECTOR *lines, const char *filename);
char *file_readBinary(const char *filename);

bool file_exists(char *);
NEKO_API void file_getCurrentDirectory(char *directory);
NEKO_API bool file_getAllByExtension(VECTOR *fileList, const char *directory, const char *extension);

NEKO_API void file_unixToWindows(char *string);
NEKO_API void file_windowsToUnix(char *string);

NEKO_API void data_loadAll(DATACONTAINER *dataContainer);

#endif