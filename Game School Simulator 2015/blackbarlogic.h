/******************************************************************************
Filename: blackbarlogic.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_BLACKBARLOGIC_H__
#define __COMP_BLACKBARLOGIC_H__

#include "component.h"
#include "hash.h"

#define COMP_BLACKBARLOGIC HASH("COMP_BLACKBARLOGIC")

void comp_blackBarLogic_initialize(COMPONENT *self, void *event);
void comp_blackBarLogic_frameUpdate(COMPONENT *self, void *event);
void comp_blackBarLogic(COMPONENT *self);

typedef struct {
  int id;
} CDATA_BLACKBARLOGIC;

#endif