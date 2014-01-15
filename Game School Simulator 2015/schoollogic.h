/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_SCHOOLLOGIC__
#define __COMP_SCHOOLLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/linkedlist.h"

#define COMP_SCHOOLLOGIC HASH("COMP_SCHOOLLOGIC")

typedef struct cdata_schoolLogic_t {
  int money;
  LIST *students;
} CDATA_SCHOOLLOGIC;

void comp_schoolLogic_logicUpdate(COMPONENT *, void *);
void comp_schoolLogic(COMPONENT *);

#endif