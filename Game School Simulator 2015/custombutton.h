/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ARCH_CUSTOMBUTTON__
#define __ARCH_CUSTOMBUTTON__

#include "entity.h"
#include "hash.h"
#include "generictext.h"

#define ARCH_CUSTOMBUTTON HASH("ARCH_CUSTOMBUTTON")

void arch_customButton(ENTITY *entity);
ENTITY *createCustomButton(void (*onEntered)(COMPONENT *), 
                           void (*onOver)(COMPONENT *), 
                           void (*onPressed)(COMPONENT *),
                           void (*onExit)(COMPONENT *), 
                           void (*destroy)(COMPONENT *),
                           SPACE *space, VEC3 *position, char *name,
                           float sizeX, float sizeY,
                           bool customSprite, char *spriteSource, VEC4 *color,
                           bool hasText, char *text, char *font, 
                           VEC4 *textColor, TEXTALIGN xAlign, TEXTALIGN yAlign);

#endif
