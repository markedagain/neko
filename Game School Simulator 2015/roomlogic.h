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
  ROOMTYPE_TEAMSPACE,
  ROOMTYPE_CAFETERIA,
  ROOMTYPE_STORE
} ROOM_TYPE;

typedef struct cdata_roomlogic_t {
  ROOM_TYPE type;
  int cost;
  int upkeep;
  int size;
  int techBonus;
  int designBonus;
  int artBonus;
  int motivationBonus;
  int repBonus;
  int frameCounter;

} CDATA_ROOMLOGIC;

void comp_roomLogic_frameUpdate(COMPONENT *, void *);
void comp_roomLogic_logicUpdate(COMPONENT *, void *);
void comp_roomLogic(COMPONENT *);

#endif