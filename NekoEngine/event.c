/******************************************************************************
Filename: event.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include <stdlib.h>
#include "event.h"

void eventcontainer_initialize(EVENTCONTAINER *container) {
  int i;
  for (i = 0; i < EV_LAST; ++i)
    container->ids[i] = NULL;
}
