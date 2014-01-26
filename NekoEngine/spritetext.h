/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SPRITETEXT_H__
#define __SPRITETEXT_H__

#include <string.h>
#include "neko.h"
#include "component.h"
#include "hash.h"
#include "../AlphaEngine/AEEngine.h"
#include "util.h"
#include "vectormath.h"

#define COMP_SPRITETEXT HASH("COMP_SPRITETEXT")

typedef struct {
  char *font;
  char text[255];
  VEC4 color;
} CDATA_SPRITETEXT;

void comp_spriteText_draw(COMPONENT *, void *);

NEKO_API void comp_spriteText(COMPONENT *);

#endif