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

#define TEXTFILE_LINELENGTH 80

typedef struct {
  DICT sprites;
  DICT sounds;
  DICT textures;
  DICT textfiles;
  char *root;
} DATACONTAINER;

typedef struct {
  void *data;
  size_t size;
} TEXTURE;

typedef struct {
  VECTOR lines;
} TEXTFILE;

typedef struct {
  TEXTURE *texture;
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
} SPRITE;

void dataContainer_init(DATACONTAINER *dataContainer);
NEKO_API void data_loadTextfileFromDisk(DATACONTAINER *dataContainer, const char *filename);

bool file_exists(char *);
void *file_load(char *);

#endif