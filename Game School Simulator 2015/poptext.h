/******************************************************************************
Filename: poptext.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __ARCH_POPTEXT__
#define __ARCH_POPTEXT__

#include "entity.h"
#include "hash.h"
#include "poptextlogic.h"

#define ARCH_POPTEXT HASH("ARCH_POPTEXT")
void arch_popText(ENTITY *entity);

ENTITY *popText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color, POPTYPE popType, float duration);

#endif
