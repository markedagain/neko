/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_CURSORLOGIC__
#define __COMP_CURSORLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "schoollogic.h"
#include "playerlogic.h"

#define COMP_CURSORLOGIC HASH("COMP_CURSORLOGIC")

void comp_cursorLogic_logicUpdate(COMPONENT *, void *);
void comp_cursorLogic(COMPONENT *);
void createGhostRooms(COMPONENT *self, LIST *spots, int roomSize, ROOM_TYPE roomType);

typedef struct {
  GMODE gameMode;
} CDATA_CURSORLOGIC;

#endif
