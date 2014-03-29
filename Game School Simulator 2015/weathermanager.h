/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_WEATHERMANAGER__
#define __COMP_WEATHERMANAGER__

#include "component.h"
#include "hash.h"

#define COMP_WEATHERMANGER HASH("COMP_WEATHERMANAGER")

typedef struct cdata_weathermananger_t{
  int clouds;
  int maxClouds;
} CDATA_WEATHERMANAGER;

void comp_weatherManager(COMPONENT *self);
void comp_weatherManager_logicUpdate(COMPONENT *self, void *event);

#endif