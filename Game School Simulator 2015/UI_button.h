/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_UI_BUTTON__
#define __COMP_UI_BUTTON__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_UI_BUTTON HASH("COMP_UI_BUTTON")
typedef struct{
  ENTITY *ent1;
  ENTITY *ent2;
  ENTITY *ent3;
} CDATA_UI_BUTTON;

void UI_buttonUpdate(COMPONENT *self, void *event);
void comp_UI_button(COMPONENT *self);

#endif
