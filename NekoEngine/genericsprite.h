/******************************************************************************
Filename: genericsprite.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __ARCH_GENERICSPRITE_H__
#define __ARCH_GENERICSPRITE_H__

#include "neko.h"
#include "entity.h"
#include "hash.h"

#define ARCH_GENERICSPRITE HASH("ARCH_GENERICSPRITE")

NEKO_API void arch_genericSprite(ENTITY *);
NEKO_API ENTITY *genericSprite_create(SPACE *space, VEC3 *position, char *name, char *source);
NEKO_API ENTITY *genericSprite_createBlank(SPACE *space, VEC3 *position, VEC2 *dimensions, VEC4 *color, char *name);

#endif
