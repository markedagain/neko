/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_SPRITE_H__
#define __COMP_SPRITE_H__

#include "neko.h"
#include "component.h"
#include "hash.h"
#include "../AlphaEngine/AEEngine.h"
#include "vectormath.h"
#include "util.h"

#define COMP_SPRITE HASH("COMP_SPRITE")
#define CONNECT_SPRITE(entity, sprite) (sprite) = ((CDATA_SPRITE)*)entity_connect((entity), comp_sprite)

typedef struct cdata_sprite_t {
  char *source;
  AEGfxVertexList *mesh;
  AEGfxTexture *texture;
  VEC4 color;
  VEC2 offset;
  VEC2 size;
  bool visible;
} CDATA_SPRITE;

void comp_sprite_initialize(COMPONENT *, void *);
void comp_sprite_frameUpdate(COMPONENT *, void *);
void comp_sprite_destroy(COMPONENT *, void *);
void comp_sprite_draw(COMPONENT *, void *);

NEKO_API void comp_sprite(COMPONENT *);

#endif
