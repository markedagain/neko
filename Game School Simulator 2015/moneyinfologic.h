/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MONEYINFOLOGIC__
#define __COMP_MONEYINFOLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_MONEYINFOLOGIC HASH("COMP_MONEYINFOLOGIC")

typedef struct cdata_moneyinfologic_t {
  ENTITY incomeText;
  ENTITY expensesText;
  ENTITY totalText;
} CDATA_MONEYINFOLOGIC;

void comp_moneyInfoLogic_initialize(COMPONENT *self, void *event);
void comp_moneyInfoLogic_logicUpdate(COMPONENT *self, void *event);
void comp_moneyInfoLogic(COMPONENT *self);

#endif
