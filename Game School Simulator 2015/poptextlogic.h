/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_POPTEXTLOGIC__
#define __COMP_POPTEXTLOGIC__

#include "entity.h"
#include "hash.h"
#include "actionlist.h"

typedef enum {
  POPTYPE_DEFAULT,
  POPTYPE_STAY,
  POPTYPE_GROW
} POPTYPE;

typedef struct {
  POPTYPE type;
  ALIST actions;
  bool started;
  float startY;
} CDATA_POPTEXT;

#define COMP_POPTEXTLOGIC HASH("COMP_POPTEXTLOGIC")
void comp_popTextLogic_logicUpdate(COMPONENT *self, void *event);
void comp_popTextLogic_destroy(COMPONENT *self, void *event);
void comp_popTextLogic(COMPONENT *self);

#endif
