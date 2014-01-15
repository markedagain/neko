/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "neko.h"
#include "util.h"
#include "dictionary.h"

typedef struct dataContainer_t {
  DICT sprites;
  DICT sounds;
  DICT textures;
} DATACONTAINER;

typedef void *TEXTURE;

typedef struct sprite_t {
  TEXTURE *texture;
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
} SPRITE;
  

NEKO_API void *data_load(char *, int *);
bool file_exists(char *);
void *file_load(char *);