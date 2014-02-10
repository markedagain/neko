/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_GHOSTROOMLOGIC__
#define __COMP_GHOSTROOMLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "schoollogic.h"

#define COMP_GHOSTROOMLOGIC HASH("COMP_GHOSTROOMLOGIC")

void comp_ghostRoomLogic_logicUpdate(COMPONENT *self, void*event);
void comp_ghostRoomLogic(COMPONENT *self);
void comp_ghostRoomLogic_initialize(COMPONENT *self, void *event);

typedef struct {
  bool constructed;
  ROOM_TYPE roomType;
  int roomSize;
  POINT point;
} CDATA_GHOSTROOMLOGIC;

#endif