/******************************************************************************
Filename: homeworklogic.h

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_HOMEWORKLOGIC__
#define __COMP_HOMEWORKLOGIC__

#include "component.h"
#include "hash.h"

#define COMP_HOMEWORKLOGIC HASH("COMP_HOMEWORKLOGIC")

typedef struct cdata_homeworklogic_t{
  int clouds;
  int maxClouds;
  int frameCounter;
} CDATA_HOMEWORKLOGIC;

void comp_homeworkLogic(COMPONENT *self);
void comp_homeworkLogic_logicUpdate(COMPONENT *self, void *event);
void comp_homeworkLogic_initialize(COMPONENT *self, void *event);

#endif