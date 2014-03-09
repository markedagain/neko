/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_NEWSFEEDLOGIC__
#define __COMP_NEWSFEEDLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "newsfeed.h"

#define COMP_NEWSFEEDLOGIC HASH("COMP_NEWSFEEDLOGIC")

typedef struct cdata_newsfeedlogic_t {
  char textBuffer[80];
  ENTITY *textSprite;

} CDATA_NEWSFEEDLOGIC;

void comp_newsfeedlogic_initialize(COMPONENT *, void *);
void comp_newsfeedlogic_logicUpdate(COMPONENT *, void *);
void comp_newsfeedlogic(COMPONENT *);

#endif
