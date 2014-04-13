/******************************************************************************
Filename: splashlogic.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_SPLASHLOGIC__
#define __COMP_SPLASHLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "transform.h"
#include "sprite.h"

#define COMP_SPLASHLOGIC HASH("COMP_CURSORLOGIC")

typedef struct {
  float timer;
  bool fadeBackground;
  bool secondLogo;
} CDATA_SPLASHLOGIC;

void comp_splashLogic_logicUpdate(COMPONENT *, void *);
void comp_splashLogic(COMPONENT *);


#endif