/******************************************************************************
Filename: namescreenlogic.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_NAMESCREENLOGIC__
#define __COMP_NAMESCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_NAMESCREENLOGIC HASH("COMP_NAMESCREENLOGIC")

typedef enum {
  ET_NAME,
  ET_SCHOOLNAME
} ENTER_TYPE;


typedef struct {
  char name[41];
  ENTITY *displayText;
  ENTER_TYPE type;
} CDATA_NAMESCREEN;

void comp_nameScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_nameScreenLogic(COMPONENT *self);
void comp_nameScreenLogic_initialize(COMPONENT *self, void *event);

#endif
