/******************************************************************************
Filename: backgroundlogic.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_BACKGROUNDLOGIC__
#define __COMP_BACKGROUNDLOGIC__

#include "component.h"
#include "hash.h"

#define COMP_BACKGROUNDLOGIC HASH("COMP_BACKGROUNDLOGIC")

void comp_backgroundLogic(COMPONENT *self);
void comp_backgroundLogic_frameUpdate(COMPONENT *self, void *event);

#endif