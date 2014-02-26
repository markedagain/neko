/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ARCH_POPTEXT__
#define __ARCH_POPTEXT__

#include "entity.h"
#include "hash.h"

#define ARCH_POPTEXT HASH("ARCH_POPTEXT")
void arch_popText(ENTITY *entity);

ENTITY *popText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color);

#endif
