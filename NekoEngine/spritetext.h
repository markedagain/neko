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
#include "multisprite.h"
#include "genericsprite.h"

#define COMP_SPRITETEXT HASH("COMP_SPRITETEXT")
#define SPRITETEXT_MAXLENGTH 128

typedef struct {
  char *font;
  char text[SPRITETEXT_MAXLENGTH];
  VEC4 color;
} CDATA_SPRITETEXT;

NEKO_API void comp_spriteText_setText(COMPONENT *self, char *text);

NEKO_API void comp_spriteText_initialize(COMPONENT *self, void *event);

NEKO_API void comp_spriteText(COMPONENT *self);

#endif
