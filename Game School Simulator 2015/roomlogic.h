/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_ROOMLOGIC__
#define __COMP_ROOMLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_ROOMLOGIC HASH("COMP_ROOMLOGIC")

typedef enum {
  ROOMTYPE_LOBBY,
  ROOMTYPE_CLASS,
  ROOMTYPE_LIBRARY,
  ROOMTYPE_TEAMSPACE
} ROOM_TYPE;

typedef struct cdata_roomlogic_t {
  ROOM_TYPE type;
  int upkeep;
  int frameCounter;

} CDATA_ROOMLOGIC;

void comp_roomLogic_logicUpdate(COMPONENT *, void *);
void comp_roomLogic(COMPONENT *);

#endif