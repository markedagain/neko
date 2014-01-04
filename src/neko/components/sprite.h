/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_SPRITE_H__
#define __COMP_SPRITE_H__

#include "../component.h"

extern int COMP_SPRITE;

typedef struct cdata_sprite_t {
  char *source;
} CDATA_SPRITE;

void comp_sprite(COMPONENT *);

#endif
