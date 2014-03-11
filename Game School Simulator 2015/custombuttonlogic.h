/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_CUSTOMBUTTONLOGIC__
#define __COMP_CUSTOMBUTTONLOGIC__

#include "entity.h"
#include "hash.h"
#include "generictext.h"
#include "actionlist.h"

#define COMP_CUSTOMBUTTONLOGIC HASH("COMP_CUSTOMBUTTONLOGIC")

typedef struct {
  void (*onOver)(COMPONENT *);
  void (*onExit)(COMPONENT *);
  void (*onEntered)(COMPONENT *);
  void (*onPressed)(COMPONENT *);
  void (*destroy)(COMPONENT *);
  void (*initialize)(COMPONENT *);
  struct {
    char source[30];
    char altSource[30];
  } sprite;
  ENTITY *text;
  ALIST actions;
} CDATA_CUSTOMBUTTON;

void comp_customButtonLogic_logicUpdate(COMPONENT *self, void *event);
void comp_customButtonLogic(COMPONENT *self);
void comp_customButtonLogic_destroy(COMPONENT *self, void *event);
void comp_customButtonLogic_initialize(COMPONENT *self, void *event);

#endif
