/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_TIMEMANAGER__
#define __COMP_TIMEMANAGER__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_TIMEMANAGER HASH("COMP_TIMEMANAGER");

typedef struct cdata_timeManager_t {
  int months;
} CDATA_TIMEMANAGER;

void comp_timeManager_logicUpdate(COMPONENT *, void *);
void comp_timeManager(COMPONENT *);

#endif