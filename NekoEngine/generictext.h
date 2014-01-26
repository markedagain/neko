/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ARCH_GENERICTEXT_H__
#define __ARCH_GENERICTEXT_H__

#include "neko.h"
#include "entity.h"
#include "hash.h"

#define ARCH_GENERICTEXT HASH("ARCH_GENERICTEXT")

NEKO_API void arch_genericText(ENTITY *);
NEKO_API ENTITY *genericText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color);

#endif