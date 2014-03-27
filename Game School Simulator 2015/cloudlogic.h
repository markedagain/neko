/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_CLOUDLOGIC__
#define __COMP_CLOUDLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_CLOUDLOGIC HASH("COMP_CLOUDLOGIC")

typedef struct {
  float speed;
} CDATA_CLOUDLOGIC;

void comp_cloudLogic_logicUpdate(COMPONENT *self, void*event);
void comp_cloudLogic(COMPONENT *self);

#endif