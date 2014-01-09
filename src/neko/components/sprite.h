/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_SPRITE_H__
#define __COMP_SPRITE_H__

#include "../component.h"
#include "../hash.h"
#include "../../alpha/AEEngine.h"

#define COMP_SPRITE HASH("COMP_SPRITE")

typedef struct cdata_sprite_t {
  char *source;
  AEGfxVertexList *mesh;
  AEGfxTexture *texture;
} CDATA_SPRITE;

typedef struct edata_sprite_t {
  char *source;
} EDATA_SPRITE;

void comp_sprite_initialize(COMPONENT *self, void *data);
void comp_sprite_frameUpdate(COMPONENT *self, void *data);
void comp_sprite_destroy(COMPONENT *self, void *data);
void comp_sprite_draw(COMPONENT *self, void *data);

void comp_sprite(COMPONENT *);

#endif
