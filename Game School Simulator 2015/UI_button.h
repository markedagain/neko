/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_UI_BUTTON__
#define __COMP_UI_BUTTON__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "roomlogic.h"

#define COMP_UI_BUTTON HASH("COMP_UI_BUTTON")

typedef enum {
  BUTTON_DEFAULT,
  BUTTON_BUILD,
  BUTTON_BUILDLOBBY,
  BUTTON_BUILDCLASS,
  BUTTON_BUILDLIBRARY,
  BUTTON_BUILDTEAMSPACE,
  BUTTON_CANCEL
} BUTTON_TYPE;

typedef struct{
  ENTITY *ent1;
  ENTITY *ent2;
  ENTITY *ent3;
  BUTTON_TYPE type;

} CDATA_UI_BUTTON;

void UI_buttonUpdate(COMPONENT *self, void *event);
void comp_UI_button(COMPONENT *self);
void comp_UI_button_cancelBuildMode(COMPONENT *self);
void UI_button_createGhostRooms(COMPONENT *self, ROOM_TYPE toBuild);
void UI_button_deleteList(LIST *buildSpaces);

#endif
