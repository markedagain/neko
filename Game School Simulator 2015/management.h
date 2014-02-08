/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MANAGEMENT__
#define __COMP_MANAGEMENT__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_MANAGEMENT HASH("COMP_MANAGEMENT")

typedef struct{
  ENTITY *ent1;
  ENTITY *ent2;
  ENTITY *ent3;
} CDATA_MANAGEMENT;

void comp_managementUpdate(COMPONENT *self, void *event);
void comp_management(COMPONENT *self);

#endif
