/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_UI_LOGIC__
#define __COMP_UI_LOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_UI_LOGIC HASH("COMP_UI_LOGIC")
typedef struct{
  ENTITY *ent1;
  ENTITY *ent2;
  ENTITY *ent3;
} CDATA_UI_LOGIC;

void UI_logicUpdate(COMPONENT *self, void *event);
void comp_UI_logic(COMPONENT *self);

#endif
