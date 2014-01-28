/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_PLAYERLOGIC_H__
#define __COMP_PLAYERLOGIC_H__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/vectormath.h"

#define COMP_PLAYERLOGIC HASH("COMP_PLAYERLOGIC")

typedef struct {
  bool dragging;
  POINT dragOrigin;
  float zoomVelocity;
} CDATA_PLAYERLOGIC;

void comp_playerLogic_initialize(COMPONENT *self, void *event);
void comp_playerLogic_logicUpdate(COMPONENT *, void *);
void comp_playerLogic_frameUpdate(COMPONENT *, void *);
void comp_playerLogic(COMPONENT *);

#endif